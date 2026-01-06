/**
 * 线程安全队列 ThreadSafeQueue
 *
 * 特性：
 * - 基于 std::queue 实现
 * - 使用 mutex + condition_variable 保证线程安全
 * - 支持阻塞式和非阻塞式操作
 * - 支持超时等待
 */

#pragma once

#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <optional>
#include <queue>

template <typename T> class ThreadSafeQueue {
private:
  std::queue<T> m_queue;
  mutable std::mutex m_mutex;
  std::condition_variable m_cond_not_empty;
  std::condition_variable m_cond_not_full;
  size_t m_max_size; // 0 表示无限制

public:
  // ==================== 构造函数 ====================

  // 默认构造（无容量限制）
  explicit ThreadSafeQueue(size_t max_size = 0) : m_max_size(max_size) {}

  // 禁止拷贝
  ThreadSafeQueue(const ThreadSafeQueue &) = delete;
  ThreadSafeQueue &operator=(const ThreadSafeQueue &) = delete;

  // 允许移动
  ThreadSafeQueue(ThreadSafeQueue &&other) noexcept {
    std::lock_guard<std::mutex> lock(other.m_mutex);
    m_queue = std::move(other.m_queue);
    m_max_size = other.m_max_size;
  }

  // ==================== 入队操作 ====================

  // 阻塞式入队（如果有容量限制，满时阻塞）
  void push(const T &value) {
    std::unique_lock<std::mutex> lock(m_mutex);
    if (m_max_size > 0) {
      m_cond_not_full.wait(lock,
                           [this] { return m_queue.size() < m_max_size; });
    }
    m_queue.push(value);
    lock.unlock();
    m_cond_not_empty.notify_one();
  }

  // 移动语义入队
  void push(T &&value) {
    std::unique_lock<std::mutex> lock(m_mutex);
    if (m_max_size > 0) {
      m_cond_not_full.wait(lock,
                           [this] { return m_queue.size() < m_max_size; });
    }
    m_queue.push(std::move(value));
    lock.unlock();
    m_cond_not_empty.notify_one();
  }

  // 原地构造入队
  template <typename... Args> void emplace(Args &&... args) {
    std::unique_lock<std::mutex> lock(m_mutex);
    if (m_max_size > 0) {
      m_cond_not_full.wait(lock,
                           [this] { return m_queue.size() < m_max_size; });
    }
    m_queue.emplace(std::forward<Args>(args)...);
    lock.unlock();
    m_cond_not_empty.notify_one();
  }

  // 非阻塞式入队（满时返回false）
  bool try_push(const T &value) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_max_size > 0 && m_queue.size() >= m_max_size) {
      return false;
    }
    m_queue.push(value);
    m_cond_not_empty.notify_one();
    return true;
  }

  bool try_push(T &&value) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_max_size > 0 && m_queue.size() >= m_max_size) {
      return false;
    }
    m_queue.push(std::move(value));
    m_cond_not_empty.notify_one();
    return true;
  }

  // ==================== 出队操作 ====================

  // 阻塞式出队（空时阻塞）
  T pop() {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_cond_not_empty.wait(lock, [this] { return !m_queue.empty(); });
    T value = std::move(m_queue.front());
    m_queue.pop();
    lock.unlock();
    if (m_max_size > 0) {
      m_cond_not_full.notify_one();
    }
    return value;
  }

  // 阻塞式出队（通过引用返回）
  void pop(T &value) {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_cond_not_empty.wait(lock, [this] { return !m_queue.empty(); });
    value = std::move(m_queue.front());
    m_queue.pop();
    lock.unlock();
    if (m_max_size > 0) {
      m_cond_not_full.notify_one();
    }
  }

  // 非阻塞式出队（空时返回 nullopt）
  std::optional<T> try_pop() {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_queue.empty()) {
      return std::nullopt;
    }
    T value = std::move(m_queue.front());
    m_queue.pop();
    if (m_max_size > 0) {
      m_cond_not_full.notify_one();
    }
    return value;
  }

  // 非阻塞式出队（通过引用返回，返回是否成功）
  bool try_pop(T &value) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_queue.empty()) {
      return false;
    }
    value = std::move(m_queue.front());
    m_queue.pop();
    if (m_max_size > 0) {
      m_cond_not_full.notify_one();
    }
    return true;
  }

  // 带超时的出队
  template <typename Rep, typename Period>
  std::optional<T> pop_for(const std::chrono::duration<Rep, Period> &timeout) {
    std::unique_lock<std::mutex> lock(m_mutex);
    if (!m_cond_not_empty.wait_for(lock, timeout,
                                   [this] { return !m_queue.empty(); })) {
      return std::nullopt; // 超时
    }
    T value = std::move(m_queue.front());
    m_queue.pop();
    if (m_max_size > 0) {
      m_cond_not_full.notify_one();
    }
    return value;
  }

  // ==================== 查询操作 ====================

  bool empty() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_queue.empty();
  }

  size_t size() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_queue.size();
  }

  size_t max_size() const { return m_max_size; }

  // 清空队列
  void clear() {
    std::lock_guard<std::mutex> lock(m_mutex);
    std::queue<T> empty;
    std::swap(m_queue, empty);
    if (m_max_size > 0) {
      m_cond_not_full.notify_all();
    }
  }
};
