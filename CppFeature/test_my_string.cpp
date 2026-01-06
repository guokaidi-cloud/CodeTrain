/**
 * MyString 测试程序
 */

#include "MyString.hpp"
#include <iostream>
#include <string>

int main() {
  std::cout << "========================================" << std::endl;
  std::cout << "         MyString 测试" << std::endl;
  std::cout << "========================================\n" << std::endl;

  // 1. 构造函数测试
  std::cout << "--- 1. 构造函数测试 ---" << std::endl;
  MyString s1;          // 默认构造
  MyString s2("Hello"); // C风格字符串构造
  MyString s3(5, 'A');  // 填充构造
  std::cout << "s1 (默认): \"" << s1 << "\", size=" << s1.size() << std::endl;
  std::cout << "s2 (C-str): \"" << s2 << "\", size=" << s2.size() << std::endl;
  std::cout << "s3 (填充): \"" << s3 << "\", size=" << s3.size() << std::endl;

  // 2. 拷贝语义测试
  std::cout << "\n--- 2. 拷贝语义测试 ---" << std::endl;
  MyString s4 = s2; // 拷贝构造
  MyString s5;
  s5 = s2; // 拷贝赋值
  std::cout << "s4: \"" << s4 << "\"" << std::endl;
  std::cout << "s5: \"" << s5 << "\"" << std::endl;

  // 3. 移动语义测试
  std::cout << "\n--- 3. 移动语义测试 ---" << std::endl;
  MyString s6 = std::move(MyString("World")); // 移动构造
  MyString s7;
  s7 = std::move(MyString("C++")); // 移动赋值
  std::cout << "s6: \"" << s6 << "\"" << std::endl;
  std::cout << "s7: \"" << s7 << "\"" << std::endl;

  // 4. 运算符测试
  std::cout << "\n--- 4. 运算符测试 ---" << std::endl;
  MyString s8 = s2 + " " + s6; // 拼接
  std::cout << "s2 + \" \" + s6 = \"" << s8 << "\"" << std::endl;
  s8 += "!";
  std::cout << "s8 += \"!\" = \"" << s8 << "\"" << std::endl;

  // 5. 比较运算符
  std::cout << "\n--- 5. 比较运算符测试 ---" << std::endl;
  MyString sa("abc"), sb("abc"), sc("abd");
  std::cout << "\"abc\" == \"abc\": " << (sa == sb ? "true" : "false")
            << std::endl;
  std::cout << "\"abc\" < \"abd\": " << (sa < sc ? "true" : "false")
            << std::endl;

  // 6. 元素访问
  std::cout << "\n--- 6. 元素访问测试 ---" << std::endl;
  std::cout << "s2[0] = '" << s2[0] << "'" << std::endl;
  std::cout << "s2.at(1) = '" << s2.at(1) << "'" << std::endl;
  std::cout << "s2.front() = '" << s2.front() << "'" << std::endl;
  std::cout << "s2.back() = '" << s2.back() << "'" << std::endl;

  // 7. 查找和子串
  std::cout << "\n--- 7. 查找和子串测试 ---" << std::endl;
  MyString text("Hello World Hello");
  std::cout << "text = \"" << text << "\"" << std::endl;
  std::cout << "find('o') = " << text.find('o') << std::endl;
  std::cout << "find(\"World\") = " << text.find("World") << std::endl;
  std::cout << "substr(6, 5) = \"" << text.substr(6, 5) << "\"" << std::endl;

  // 8. 迭代器
  std::cout << "\n--- 8. 迭代器测试 ---" << std::endl;
  std::cout << "遍历 s2: ";
  for (char ch : s2) {
    std::cout << ch << " ";
  }
  std::cout << std::endl;

  std::cout << "\n========================================" << std::endl;
  std::cout << "         测试完成" << std::endl;
  std::cout << "========================================" << std::endl;

  return 0;
}
