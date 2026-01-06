/**
 * 环形缓冲区 RingBuffer
 *
 * 特性：
 * - 固定大小的循环缓冲区
 * - 支持线程安全版本
 * - 无锁版本用于单生产者单消费者场景 (SPSC)
 * - 支持覆盖模式和阻塞模式
 */

#pragma once

#include <atomic>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <optional>
#include <stdexcept>
#include <vector>

// ==================== 非线程安全版本 ====================
template <typename T> class RingBuffer {
protected:
  std::vector<T> m_buffer;
  size_t m_head;     // 读取位置
  size_t m_tail;     // 写入位置
  size_t m_size;     // 当前元素数量
  size_t m_capacity; // 容量

public:
  explicit RingBuffer(size_t capacity)
      : m_buffer(capacity), m_head(0), m_tail(0), m_size(0),
        m_capacity(capacity) {
    if (capacity == 0) {
      throw std::invalid_argument("RingBuffer capacity must be > 0");
    }
  }

  // ==================== 写入操作 ====================

  // 写入元素（满时返回false）
  bool push(const T &value) {
    if (full()) {
      return false;
    }
    m_buffer[m_tail] = value;
    m_tail = (m_tail + 1) % m_capacity;
    ++m_size;
    return true;
  }

  bool push(T &&value) {
    if (full()) {
      return false;
    }
    m_buffer[m_tail] = std::move(value);
    m_tail = (m_tail + 1) % m_capacity;
    ++m_size;
    return true;
  }

  // 强制写入（满时覆盖最老的元素）
  void push_overwrite(const T &value) {
    if (full()) {
      m_head = (m_head + 1) % m_capacity; // 丢弃最老的
      --m_size;
    }
    m_buffer[m_tail] = value;
    m_tail = (m_tail + 1) % m_capacity;
    ++m_size;
  }

  void push_overwrite(T &&value) {
    if (full()) {
      m_head = (m_head + 1) % m_capacity;
      --m_size;
    }
    m_buffer[m_tail] = std::move(value);
    m_tail = (m_tail + 1) % m_capacity;
    ++m_size;
  }

  // ==================== 读取操作 ====================

  // 读取并移除元素
  std::optional<T> pop() {
    if (empty()) {
      return std::nullopt;
    }
    T value = std::move(m_buffer[m_head]);
    m_head = (m_head + 1) % m_capacity;
    --m_size;
    return value;
  }

  bool pop(T &value) {
    if (empty()) {
      return false;
    }
    value = std::move(m_buffer[m_head]);
    m_head = (m_head + 1) % m_capacity;
    --m_size;
    return true;
  }

  // 查看队首元素（不移除）
  std::optional<T> front() const {
    if (empty()) {
      return std::nullopt;
    }
    return m_buffer[m_head];
  }

  // 查看队尾元素（不移除）
  std::optional<T> back() const {
    if (empty()) {
      return std::nullopt;
    }
    size_t idx = (m_tail + m_capacity - 1) % m_capacity;
    return m_buffer[idx];
  }

  // ==================== 状态查询 ====================

  bool empty() const { return m_size == 0; }
  bool full() const { return m_size == m_capacity; }
  size_t size() const { return m_size; }
  size_t capacity() const { return m_capacity; }

  void clear() {
    m_head = 0;
    m_tail = 0;
    m_size = 0;
  }

  // ==================== 调试输出 ====================

  friend std::ostream &operator<<(std::ostream &os, const RingBuffer &rb) {
    os << "RingBuffer[";
    size_t idx = rb.m_head;
    for (size_t i = 0; i < rb.m_size; ++i) {
      os << rb.m_buffer[idx];
      if (i < rb.m_size - 1)
        os << ", ";
      idx = (idx + 1) % rb.m_capacity;
    }
    os << "] (size=" << rb.m_size << ", cap=" << rb.m_capacity << ")";
    return os;
  }
};

// ==================== 线程安全版本 ====================
template <typename T> class ThreadSafeRingBuffer {
private:
  std::vector<T> m_buffer;
  size_t m_head;
  size_t m_tail;
  size_t m_size;
  size_t m_capacity;

  mutable std::mutex m_mutex;
  std::condition_variable m_cond_not_empty;
  std::condition_variable m_cond_not_full;

public:
  explicit ThreadSafeRingBuffer(size_t capacity)
      : m_buffer(capacity), m_head(0), m_tail(0), m_size(0),
        m_capacity(capacity) {
    if (capacity == 0) {
      throw std::invalid_argument("ThreadSafeRingBuffer capacity must be > 0");
    }
  }

  // 禁止拷贝
  ThreadSafeRingBuffer(const ThreadSafeRingBuffer &) = delete;
  ThreadSafeRingBuffer &operator=(const ThreadSafeRingBuffer &) = delete;

  // ==================== 写入操作 ====================

  // 阻塞式写入（满时等待）
  void push(const T &value) {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_cond_not_full.wait(lock, [this] { return m_size < m_capacity; });
    m_buffer[m_tail] = value;
    m_tail = (m_tail + 1) % m_capacity;
    ++m_size;
    lock.unlock();
    m_cond_not_empty.notify_one();
  }

  void push(T &&value) {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_cond_not_full.wait(lock, [this] { return m_size < m_capacity; });
    m_buffer[m_tail] = std::move(value);
    m_tail = (m_tail + 1) % m_capacity;
    ++m_size;
    lock.unlock();
    m_cond_not_empty.notify_one();
  }

  // 非阻塞式写入
  bool try_push(const T &value) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_size >= m_capacity) {
      return false;
    }
    m_buffer[m_tail] = value;
    m_tail = (m_tail + 1) % m_capacity;
    ++m_size;
    m_cond_not_empty.notify_one();
    return true;
  }

  bool try_push(T &&value) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_size >= m_capacity) {
      return false;
    }
    m_buffer[m_tail] = std::move(value);
    m_tail = (m_tail + 1) % m_capacity;
    ++m_size;
    m_cond_not_empty.notify_one();
    return true;
  }

  // 覆盖式写入（满时覆盖最老的）
  void push_overwrite(const T &value) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_size >= m_capacity) {
      m_head = (m_head + 1) % m_capacity;
      --m_size;
    }
    m_buffer[m_tail] = value;
    m_tail = (m_tail + 1) % m_capacity;
    ++m_size;
    m_cond_not_empty.notify_one();
  }

  // ==================== 读取操作 ====================

  // 阻塞式读取（空时等待）
  T pop() {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_cond_not_empty.wait(lock, [this] { return m_size > 0; });
    T value = std::move(m_buffer[m_head]);
    m_head = (m_head + 1) % m_capacity;
    --m_size;
    lock.unlock();
    m_cond_not_full.notify_one();
    return value;
  }

  void pop(T &value) {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_cond_not_empty.wait(lock, [this] { return m_size > 0; });
    value = std::move(m_buffer[m_head]);
    m_head = (m_head + 1) % m_capacity;
    --m_size;
    lock.unlock();
    m_cond_not_full.notify_one();
  }

  // 非阻塞式读取
  std::optional<T> try_pop() {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_size == 0) {
      return std::nullopt;
    }
    T value = std::move(m_buffer[m_head]);
    m_head = (m_head + 1) % m_capacity;
    --m_size;
    m_cond_not_full.notify_one();
    return value;
  }

  bool try_pop(T &value) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_size == 0) {
      return false;
    }
    value = std::move(m_buffer[m_head]);
    m_head = (m_head + 1) % m_capacity;
    --m_size;
    m_cond_not_full.notify_one();
    return true;
  }

  // 带超时的读取
  template <typename Rep, typename Period>
  std::optional<T> pop_for(const std::chrono::duration<Rep, Period> &timeout) {
    std::unique_lock<std::mutex> lock(m_mutex);
    if (!m_cond_not_empty.wait_for(lock, timeout,
                                   [this] { return m_size > 0; })) {
      return std::nullopt;
    }
    T value = std::move(m_buffer[m_head]);
    m_head = (m_head + 1) % m_capacity;
    --m_size;
    m_cond_not_full.notify_one();
    return value;
  }

  // ==================== 状态查询 ====================

  bool empty() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_size == 0;
  }

  bool full() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_size == m_capacity;
  }

  size_t size() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_size;
  }

  size_t capacity() const { return m_capacity; }

  void clear() {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_head = 0;
    m_tail = 0;
    m_size = 0;
    m_cond_not_full.notify_all();
  }
};

// ==================== 无锁版本 (SPSC - 单生产者单消费者) ====================
template <typename T> class LockFreeRingBuffer {
private:
  std::vector<T> m_buffer;
  std::atomic<size_t> m_head; // 读取位置
  std::atomic<size_t> m_tail; // 写入位置
  size_t m_capacity;

public:
  explicit LockFreeRingBuffer(size_t capacity)
      : m_buffer(capacity + 1), m_head(0), m_tail(0), m_capacity(capacity + 1) {
    // 使用 capacity + 1 来区分空和满的状态
    if (capacity == 0) {
      throw std::invalid_argument("LockFreeRingBuffer capacity must be > 0");
    }
  }

  // 禁止拷贝和移动
  LockFreeRingBuffer(const LockFreeRingBuffer &) = delete;
  LockFreeRingBuffer &operator=(const LockFreeRingBuffer &) = delete;

  // 写入（仅供生产者调用）
  bool push(const T &value) {
    size_t tail = m_tail.load(std::memory_order_relaxed);
    size_t next_tail = (tail + 1) % m_capacity;

    if (next_tail == m_head.load(std::memory_order_acquire)) {
      return false; // 满
    }

    m_buffer[tail] = value;
    m_tail.store(next_tail, std::memory_order_release);
    return true;
  }

  bool push(T &&value) {
    size_t tail = m_tail.load(std::memory_order_relaxed);
    size_t next_tail = (tail + 1) % m_capacity;

    if (next_tail == m_head.load(std::memory_order_acquire)) {
      return false;
    }

    m_buffer[tail] = std::move(value);
    m_tail.store(next_tail, std::memory_order_release);
    return true;
  }

  // 读取（仅供消费者调用）
  std::optional<T> pop() {
    size_t head = m_head.load(std::memory_order_relaxed);

    if (head == m_tail.load(std::memory_order_acquire)) {
      return std::nullopt; // 空
    }

    T value = std::move(m_buffer[head]);
    m_head.store((head + 1) % m_capacity, std::memory_order_release);
    return value;
  }

  bool pop(T &value) {
    size_t head = m_head.load(std::memory_order_relaxed);

    if (head == m_tail.load(std::memory_order_acquire)) {
      return false;
    }

    value = std::move(m_buffer[head]);
    m_head.store((head + 1) % m_capacity, std::memory_order_release);
    return true;
  }

  // 状态查询
  bool empty() const {
    return m_head.load(std::memory_order_acquire) ==
           m_tail.load(std::memory_order_acquire);
  }

  bool full() const {
    size_t next_tail =
        (m_tail.load(std::memory_order_acquire) + 1) % m_capacity;
    return next_tail == m_head.load(std::memory_order_acquire);
  }

  size_t size() const {
    size_t head = m_head.load(std::memory_order_acquire);
    size_t tail = m_tail.load(std::memory_order_acquire);
    return (tail + m_capacity - head) % m_capacity;
  }

  size_t capacity() const {
    return m_capacity - 1; // 实际可用容量
  }
};
