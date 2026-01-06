/**
 * 手写 MyVector 类
 * 实现基本的动态数组功能，展示 C++ 核心概念：
 * - 模板编程
 * - 构造/析构函数
 * - 拷贝语义 (Copy Semantics)
 * - 移动语义 (Move Semantics)
 * - 运算符重载
 * - 迭代器
 * - 内存管理与扩容策略
 */

#pragma once

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <utility>

template <typename T> class MyVector {
private:
  T *m_data;         // 数据指针
  size_t m_size;     // 当前元素数量
  size_t m_capacity; // 分配的容量

public:
  // ==================== 类型别名 ====================
  using value_type = T;
  using size_type = size_t;
  using reference = T &;
  using const_reference = const T &;
  using pointer = T *;
  using const_pointer = const T *;
  using iterator = T *;
  using const_iterator = const T *;

  // ==================== 构造函数 ====================

  // 默认构造函数
  MyVector() : m_data(nullptr), m_size(0), m_capacity(0) {}

  // 指定大小构造
  explicit MyVector(size_t count)
      : m_data(nullptr), m_size(count), m_capacity(count) {
    if (count > 0) {
      m_data = new T[count](); // 值初始化
    }
  }

  // 指定大小和值构造
  MyVector(size_t count, const T &value)
      : m_data(nullptr), m_size(count), m_capacity(count) {
    if (count > 0) {
      m_data = new T[count];
      for (size_t i = 0; i < count; ++i) {
        m_data[i] = value;
      }
    }
  }

  // 初始化列表构造
  MyVector(std::initializer_list<T> init)
      : m_data(nullptr), m_size(init.size()), m_capacity(init.size()) {
    if (m_size > 0) {
      m_data = new T[m_size];
      size_t i = 0;
      for (const auto &elem : init) {
        m_data[i++] = elem;
      }
    }
  }

  // ==================== 拷贝语义 ====================

  // 拷贝构造函数
  MyVector(const MyVector &other)
      : m_data(nullptr), m_size(other.m_size), m_capacity(other.m_capacity) {
    if (m_capacity > 0) {
      m_data = new T[m_capacity];
      for (size_t i = 0; i < m_size; ++i) {
        m_data[i] = other.m_data[i];
      }
    }
    std::cout << "[MyVector] 拷贝构造, size=" << m_size << std::endl;
  }

  // 拷贝赋值运算符
  MyVector &operator=(const MyVector &other) {
    if (this != &other) {
      delete[] m_data;
      m_size = other.m_size;
      m_capacity = other.m_capacity;
      m_data = nullptr;
      if (m_capacity > 0) {
        m_data = new T[m_capacity];
        for (size_t i = 0; i < m_size; ++i) {
          m_data[i] = other.m_data[i];
        }
      }
      std::cout << "[MyVector] 拷贝赋值, size=" << m_size << std::endl;
    }
    return *this;
  }

  // ==================== 移动语义 ====================

  // 移动构造函数
  MyVector(MyVector &&other) noexcept
      : m_data(other.m_data), m_size(other.m_size),
        m_capacity(other.m_capacity) {
    other.m_data = nullptr;
    other.m_size = 0;
    other.m_capacity = 0;
    std::cout << "[MyVector] 移动构造, size=" << m_size << std::endl;
  }

  // 移动赋值运算符
  MyVector &operator=(MyVector &&other) noexcept {
    if (this != &other) {
      delete[] m_data;
      m_data = other.m_data;
      m_size = other.m_size;
      m_capacity = other.m_capacity;
      other.m_data = nullptr;
      other.m_size = 0;
      other.m_capacity = 0;
      std::cout << "[MyVector] 移动赋值, size=" << m_size << std::endl;
    }
    return *this;
  }

  // ==================== 析构函数 ====================

  ~MyVector() { delete[] m_data; }

  // ==================== 容量相关 ====================

  size_t size() const { return m_size; }
  size_t capacity() const { return m_capacity; }
  bool empty() const { return m_size == 0; }

  void reserve(size_t new_cap) {
    if (new_cap > m_capacity) {
      T *new_data = new T[new_cap];
      for (size_t i = 0; i < m_size; ++i) {
        new_data[i] = std::move(m_data[i]);
      }
      delete[] m_data;
      m_data = new_data;
      m_capacity = new_cap;
    }
  }

  void resize(size_t new_size) {
    if (new_size > m_capacity) {
      reserve(new_size);
    }
    if (new_size > m_size) {
      for (size_t i = m_size; i < new_size; ++i) {
        m_data[i] = T();
      }
    }
    m_size = new_size;
  }

  void resize(size_t new_size, const T &value) {
    if (new_size > m_capacity) {
      reserve(new_size);
    }
    if (new_size > m_size) {
      for (size_t i = m_size; i < new_size; ++i) {
        m_data[i] = value;
      }
    }
    m_size = new_size;
  }

  void shrink_to_fit() {
    if (m_size < m_capacity) {
      if (m_size == 0) {
        delete[] m_data;
        m_data = nullptr;
        m_capacity = 0;
      } else {
        T *new_data = new T[m_size];
        for (size_t i = 0; i < m_size; ++i) {
          new_data[i] = std::move(m_data[i]);
        }
        delete[] m_data;
        m_data = new_data;
        m_capacity = m_size;
      }
    }
  }

  void clear() { m_size = 0; }

  // ==================== 元素访问 ====================

  T &operator[](size_t index) { return m_data[index]; }

  const T &operator[](size_t index) const { return m_data[index]; }

  T &at(size_t index) {
    if (index >= m_size) {
      throw std::out_of_range("MyVector::at: index out of range");
    }
    return m_data[index];
  }

  const T &at(size_t index) const {
    if (index >= m_size) {
      throw std::out_of_range("MyVector::at: index out of range");
    }
    return m_data[index];
  }

  T &front() { return m_data[0]; }
  const T &front() const { return m_data[0]; }
  T &back() { return m_data[m_size - 1]; }
  const T &back() const { return m_data[m_size - 1]; }
  T *data() { return m_data; }
  const T *data() const { return m_data; }

  // ==================== 修改操作 ====================

  void push_back(const T &value) {
    if (m_size >= m_capacity) {
      reserve(m_capacity == 0 ? 1 : m_capacity * 2);
    }
    m_data[m_size++] = value;
  }

  void push_back(T &&value) {
    if (m_size >= m_capacity) {
      reserve(m_capacity == 0 ? 1 : m_capacity * 2);
    }
    m_data[m_size++] = std::move(value);
  }

  // 原地构造 (emplace_back)
  template <typename... Args> T &emplace_back(Args &&... args) {
    if (m_size >= m_capacity) {
      reserve(m_capacity == 0 ? 1 : m_capacity * 2);
    }
    // 使用 placement new 原地构造
    new (&m_data[m_size]) T(std::forward<Args>(args)...);
    return m_data[m_size++];
  }

  void pop_back() {
    if (m_size > 0) {
      --m_size;
    }
  }

  // 插入元素
  iterator insert(const_iterator pos, const T &value) {
    size_t index = pos - m_data;
    if (m_size >= m_capacity) {
      reserve(m_capacity == 0 ? 1 : m_capacity * 2);
    }
    // 后移元素
    for (size_t i = m_size; i > index; --i) {
      m_data[i] = std::move(m_data[i - 1]);
    }
    m_data[index] = value;
    ++m_size;
    return m_data + index;
  }

  // 删除元素
  iterator erase(const_iterator pos) {
    size_t index = pos - m_data;
    // 前移元素
    for (size_t i = index; i < m_size - 1; ++i) {
      m_data[i] = std::move(m_data[i + 1]);
    }
    --m_size;
    return m_data + index;
  }

  // 删除范围
  iterator erase(const_iterator first, const_iterator last) {
    size_t start_index = first - m_data;
    size_t end_index = last - m_data;
    size_t count = end_index - start_index;

    // 前移元素
    for (size_t i = start_index; i < m_size - count; ++i) {
      m_data[i] = std::move(m_data[i + count]);
    }
    m_size -= count;
    return m_data + start_index;
  }

  // 交换
  void swap(MyVector &other) noexcept {
    std::swap(m_data, other.m_data);
    std::swap(m_size, other.m_size);
    std::swap(m_capacity, other.m_capacity);
  }

  // ==================== 迭代器 ====================

  iterator begin() { return m_data; }
  const_iterator begin() const { return m_data; }
  const_iterator cbegin() const { return m_data; }

  iterator end() { return m_data + m_size; }
  const_iterator end() const { return m_data + m_size; }
  const_iterator cend() const { return m_data + m_size; }

  // ==================== 比较运算符 ====================

  friend bool operator==(const MyVector &lhs, const MyVector &rhs) {
    if (lhs.m_size != rhs.m_size)
      return false;
    for (size_t i = 0; i < lhs.m_size; ++i) {
      if (!(lhs.m_data[i] == rhs.m_data[i]))
        return false;
    }
    return true;
  }

  friend bool operator!=(const MyVector &lhs, const MyVector &rhs) {
    return !(lhs == rhs);
  }

  // ==================== 输出运算符 ====================

  friend std::ostream &operator<<(std::ostream &os, const MyVector &vec) {
    os << "[";
    for (size_t i = 0; i < vec.m_size; ++i) {
      os << vec.m_data[i];
      if (i < vec.m_size - 1)
        os << ", ";
    }
    os << "]";
    return os;
  }
};
