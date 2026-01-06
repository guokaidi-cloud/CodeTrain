/**
 * MyVector 测试程序
 */

#include "MyString.hpp"
#include "MyVector.hpp"
#include <iostream>

int main() {
  std::cout << "========================================" << std::endl;
  std::cout << "         MyVector 测试" << std::endl;
  std::cout << "========================================\n" << std::endl;

  // 1. 构造函数测试
  std::cout << "--- 1. 构造函数测试 ---" << std::endl;
  MyVector<int> v1;                   // 默认构造
  MyVector<int> v2(5);                // 指定大小
  MyVector<int> v3(5, 42);            // 指定大小和值
  MyVector<int> v4 = {1, 2, 3, 4, 5}; // 初始化列表
  std::cout << "v1 (默认): " << v1 << ", size=" << v1.size() << std::endl;
  std::cout << "v2 (size=5): " << v2 << ", size=" << v2.size() << std::endl;
  std::cout << "v3 (5个42): " << v3 << ", size=" << v3.size() << std::endl;
  std::cout << "v4 (init_list): " << v4 << ", size=" << v4.size() << std::endl;

  // 2. 拷贝语义测试
  std::cout << "\n--- 2. 拷贝语义测试 ---" << std::endl;
  MyVector<int> v5 = v4; // 拷贝构造
  MyVector<int> v6;
  v6 = v4; // 拷贝赋值
  std::cout << "v5: " << v5 << std::endl;
  std::cout << "v6: " << v6 << std::endl;

  // 3. 移动语义测试
  std::cout << "\n--- 3. 移动语义测试 ---" << std::endl;
  MyVector<int> v7 = std::move(MyVector<int>{10, 20, 30}); // 移动构造
  MyVector<int> v8;
  v8 = std::move(MyVector<int>{100, 200}); // 移动赋值
  std::cout << "v7: " << v7 << std::endl;
  std::cout << "v8: " << v8 << std::endl;

  // 4. push_back 和 emplace_back
  std::cout << "\n--- 4. push_back 和 emplace_back 测试 ---" << std::endl;
  MyVector<int> v9;
  for (int i = 1; i <= 5; ++i) {
    v9.push_back(i * 10);
  }
  std::cout << "push_back后 v9: " << v9 << ", capacity=" << v9.capacity()
            << std::endl;

  // 5. 元素访问
  std::cout << "\n--- 5. 元素访问测试 ---" << std::endl;
  std::cout << "v4[0] = " << v4[0] << std::endl;
  std::cout << "v4.at(2) = " << v4.at(2) << std::endl;
  std::cout << "v4.front() = " << v4.front() << std::endl;
  std::cout << "v4.back() = " << v4.back() << std::endl;

  // 6. 插入和删除
  std::cout << "\n--- 6. 插入和删除测试 ---" << std::endl;
  MyVector<int> v10 = {1, 2, 3, 4, 5};
  std::cout << "原始 v10: " << v10 << std::endl;
  v10.insert(v10.begin() + 2, 100);
  std::cout << "insert(begin+2, 100): " << v10 << std::endl;
  v10.erase(v10.begin() + 3);
  std::cout << "erase(begin+3): " << v10 << std::endl;
  v10.pop_back();
  std::cout << "pop_back(): " << v10 << std::endl;

  // 7. resize 和 reserve
  std::cout << "\n--- 7. resize 和 reserve 测试 ---" << std::endl;
  MyVector<int> v11 = {1, 2, 3};
  std::cout << "原始 v11: " << v11 << ", capacity=" << v11.capacity()
            << std::endl;
  v11.reserve(10);
  std::cout << "reserve(10): " << v11 << ", capacity=" << v11.capacity()
            << std::endl;
  v11.resize(6, 99);
  std::cout << "resize(6, 99): " << v11 << ", size=" << v11.size() << std::endl;

  // 8. 迭代器
  std::cout << "\n--- 8. 迭代器测试 ---" << std::endl;
  std::cout << "range-for遍历 v4: ";
  for (const auto &elem : v4) {
    std::cout << elem << " ";
  }
  std::cout << std::endl;

  // 9. 使用自定义类型
  std::cout << "\n--- 9. 自定义类型测试 ---" << std::endl;
  MyVector<MyString> vs;
  vs.push_back(MyString("Hello"));
  vs.push_back(MyString("World"));
  vs.push_back(MyString("C++"));
  std::cout << "MyVector<MyString>: ";
  for (const auto &s : vs) {
    std::cout << "\"" << s << "\" ";
  }
  std::cout << std::endl;

  std::cout << "\n========================================" << std::endl;
  std::cout << "         测试完成" << std::endl;
  std::cout << "========================================" << std::endl;

  return 0;
}
