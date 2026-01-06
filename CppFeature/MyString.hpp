/**
 * 手写 MyString 类
 * 实现基本的字符串功能，展示 C++ 核心概念：
 * - 构造/析构函数
 * - 拷贝语义 (Copy Semantics)
 * - 移动语义 (Move Semantics)
 * - 运算符重载
 * - 内存管理
 */

#pragma once

#include <cstring>
#include <iostream>
#include <stdexcept>

class MyString {
private:
  char *m_data;      // 字符串数据
  size_t m_size;     // 字符串长度（不含'\0'）
  size_t m_capacity; // 分配的容量

public:
  // ==================== 构造函数 ====================

  // 默认构造函数
  MyString() : m_data(nullptr), m_size(0), m_capacity(0) {
    m_data = new char[1];
    m_data[0] = '\0';
    m_capacity = 1;
  }

  // C风格字符串构造
  MyString(const char *str) : m_data(nullptr), m_size(0), m_capacity(0) {
    if (str) {
      m_size = strlen(str);
      m_capacity = m_size + 1;
      m_data = new char[m_capacity];
      strcpy(m_data, str);
    } else {
      m_data = new char[1];
      m_data[0] = '\0';
      m_capacity = 1;
    }
  }

  // 填充构造函数
  MyString(size_t count, char ch)
      : m_data(nullptr), m_size(count), m_capacity(count + 1) {
    m_data = new char[m_capacity];
    for (size_t i = 0; i < count; ++i) {
      m_data[i] = ch;
    }
    m_data[count] = '\0';
  }

  // ==================== 拷贝语义 ====================

  // 拷贝构造函数
  MyString(const MyString &other)
      : m_data(nullptr), m_size(other.m_size), m_capacity(other.m_capacity) {
    m_data = new char[m_capacity];
    strcpy(m_data, other.m_data);
    std::cout << "[MyString] 拷贝构造: \"" << m_data << "\"" << std::endl;
  }

  // 拷贝赋值运算符
  MyString &operator=(const MyString &other) {
    if (this != &other) {
      delete[] m_data;
      m_size = other.m_size;
      m_capacity = other.m_capacity;
      m_data = new char[m_capacity];
      strcpy(m_data, other.m_data);
      std::cout << "[MyString] 拷贝赋值: \"" << m_data << "\"" << std::endl;
    }
    return *this;
  }

  // ==================== 移动语义 ====================

  // 移动构造函数
  MyString(MyString &&other) noexcept
      : m_data(other.m_data), m_size(other.m_size),
        m_capacity(other.m_capacity) {
    other.m_data = nullptr;
    other.m_size = 0;
    other.m_capacity = 0;
    std::cout << "[MyString] 移动构造: \"" << m_data << "\"" << std::endl;
  }

  // 移动赋值运算符
  MyString &operator=(MyString &&other) noexcept {
    if (this != &other) {
      delete[] m_data;
      m_data = other.m_data;
      m_size = other.m_size;
      m_capacity = other.m_capacity;
      other.m_data = nullptr;
      other.m_size = 0;
      other.m_capacity = 0;
      std::cout << "[MyString] 移动赋值: \"" << m_data << "\"" << std::endl;
    }
    return *this;
  }

  // ==================== 析构函数 ====================

  ~MyString() { delete[] m_data; }

  // ==================== 容量相关 ====================

  size_t size() const { return m_size; }
  size_t length() const { return m_size; }
  size_t capacity() const { return m_capacity; }
  bool empty() const { return m_size == 0; }

  void reserve(size_t new_cap) {
    if (new_cap > m_capacity) {
      char *new_data = new char[new_cap];
      strcpy(new_data, m_data);
      delete[] m_data;
      m_data = new_data;
      m_capacity = new_cap;
    }
  }

  void clear() {
    m_size = 0;
    m_data[0] = '\0';
  }

  // ==================== 元素访问 ====================

  char &operator[](size_t index) { return m_data[index]; }

  const char &operator[](size_t index) const { return m_data[index]; }

  char &at(size_t index) {
    if (index >= m_size) {
      throw std::out_of_range("MyString::at: index out of range");
    }
    return m_data[index];
  }

  const char &at(size_t index) const {
    if (index >= m_size) {
      throw std::out_of_range("MyString::at: index out of range");
    }
    return m_data[index];
  }

  char &front() { return m_data[0]; }
  const char &front() const { return m_data[0]; }
  char &back() { return m_data[m_size - 1]; }
  const char &back() const { return m_data[m_size - 1]; }

  const char *c_str() const { return m_data; }
  const char *data() const { return m_data; }

  // ==================== 修改操作 ====================

  void push_back(char ch) {
    if (m_size + 1 >= m_capacity) {
      reserve(m_capacity == 0 ? 2 : m_capacity * 2);
    }
    m_data[m_size++] = ch;
    m_data[m_size] = '\0';
  }

  void pop_back() {
    if (m_size > 0) {
      m_data[--m_size] = '\0';
    }
  }

  MyString &append(const MyString &str) { return append(str.c_str()); }

  MyString &append(const char *str) {
    if (str) {
      size_t len = strlen(str);
      if (m_size + len + 1 > m_capacity) {
        reserve((m_size + len + 1) * 2);
      }
      strcpy(m_data + m_size, str);
      m_size += len;
    }
    return *this;
  }

  // ==================== 运算符重载 ====================

  MyString &operator+=(const MyString &other) { return append(other); }

  MyString &operator+=(const char *str) { return append(str); }

  MyString &operator+=(char ch) {
    push_back(ch);
    return *this;
  }

  // 字符串拼接
  friend MyString operator+(const MyString &lhs, const MyString &rhs) {
    MyString result;
    result.reserve(lhs.m_size + rhs.m_size + 1);
    result.append(lhs);
    result.append(rhs);
    return result;
  }

  // 比较运算符
  friend bool operator==(const MyString &lhs, const MyString &rhs) {
    return strcmp(lhs.m_data, rhs.m_data) == 0;
  }

  friend bool operator!=(const MyString &lhs, const MyString &rhs) {
    return !(lhs == rhs);
  }

  friend bool operator<(const MyString &lhs, const MyString &rhs) {
    return strcmp(lhs.m_data, rhs.m_data) < 0;
  }

  friend bool operator>(const MyString &lhs, const MyString &rhs) {
    return rhs < lhs;
  }

  friend bool operator<=(const MyString &lhs, const MyString &rhs) {
    return !(rhs < lhs);
  }

  friend bool operator>=(const MyString &lhs, const MyString &rhs) {
    return !(lhs < rhs);
  }

  // 流运算符
  friend std::ostream &operator<<(std::ostream &os, const MyString &str) {
    return os << str.m_data;
  }

  friend std::istream &operator>>(std::istream &is, MyString &str) {
    char buffer[1024];
    if (is >> buffer) {
      str = MyString(buffer);
    }
    return is;
  }

  // ==================== 查找操作 ====================

  size_t find(char ch, size_t pos = 0) const {
    for (size_t i = pos; i < m_size; ++i) {
      if (m_data[i] == ch)
        return i;
    }
    return npos;
  }

  size_t find(const char *str, size_t pos = 0) const {
    if (!str || pos >= m_size)
      return npos;
    const char *found = strstr(m_data + pos, str);
    return found ? (found - m_data) : npos;
  }

  // ==================== 子串操作 ====================

  MyString substr(size_t pos = 0, size_t len = npos) const {
    if (pos >= m_size) {
      throw std::out_of_range("MyString::substr: pos out of range");
    }
    size_t actual_len =
        (len == npos || pos + len > m_size) ? (m_size - pos) : len;
    MyString result;
    result.reserve(actual_len + 1);
    for (size_t i = 0; i < actual_len; ++i) {
      result.push_back(m_data[pos + i]);
    }
    return result;
  }

  // ==================== 迭代器 ====================

  char *begin() { return m_data; }
  const char *begin() const { return m_data; }
  char *end() { return m_data + m_size; }
  const char *end() const { return m_data + m_size; }

  // npos 常量
  static constexpr size_t npos = static_cast<size_t>(-1);
};
