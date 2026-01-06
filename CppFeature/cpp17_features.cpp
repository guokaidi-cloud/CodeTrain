/**
 * C++17 新特性示例
 * 编译需要: -std=c++17
 */

#include <algorithm>
#include <any>
#include <filesystem>
#include <iostream>
#include <map>
#include <optional>
#include <string>
#include <string_view>
#include <tuple>
#include <variant>
#include <vector>

// ==================== 1. 结构化绑定 (Structured Bindings) ====================
void demo_structured_bindings() {
  std::cout << "\n=== 1. 结构化绑定 (Structured Bindings) ===" << std::endl;

  // 绑定数组
  int arr[] = {1, 2, 3};
  auto [a, b, c] = arr;
  std::cout << "数组绑定: a=" << a << ", b=" << b << ", c=" << c << std::endl;

  // 绑定pair
  std::pair<std::string, int> person = {"张三", 25};
  auto [name, age] = person;
  std::cout << "Pair绑定: name=" << name << ", age=" << age << std::endl;

  // 绑定map遍历
  std::map<std::string, int> scores = {
      {"语文", 90}, {"数学", 95}, {"英语", 88}};
  std::cout << "Map遍历: ";
  for (const auto &[subject, score] : scores) {
    std::cout << subject << ":" << score << " ";
  }
  std::cout << std::endl;
}

// ==================== 2. if/switch 初始化语句 ====================
void demo_init_statements() {
  std::cout << "\n=== 2. if/switch 初始化语句 ===" << std::endl;

  std::map<std::string, int> data = {{"key1", 100}, {"key2", 200}};

  // if with initializer
  if (auto it = data.find("key1"); it != data.end()) {
    std::cout << "找到 key1, 值为: " << it->second << std::endl;
  }

  // switch with initializer
  switch (int value = 42; value % 3) {
  case 0:
    std::cout << value << " 能被3整除" << std::endl;
    break;
  case 1:
    std::cout << value << " 除以3余1" << std::endl;
    break;
  case 2:
    std::cout << value << " 除以3余2" << std::endl;
    break;
  }
}

// ==================== 3. std::optional ====================
std::optional<int> safe_divide(int a, int b) {
  if (b == 0)
    return std::nullopt;
  return a / b;
}

void demo_optional() {
  std::cout << "\n=== 3. std::optional ===" << std::endl;

  auto result1 = safe_divide(10, 2);
  auto result2 = safe_divide(10, 0);

  if (result1) {
    std::cout << "10 / 2 = " << *result1 << std::endl;
  }

  std::cout << "10 / 0 = " << result2.value_or(-1) << " (使用默认值-1)"
            << std::endl;
}

// ==================== 4. std::variant ====================
void demo_variant() {
  std::cout << "\n=== 4. std::variant ===" << std::endl;

  std::variant<int, double, std::string> var;

  var = 42;
  std::cout << "int值: " << std::get<int>(var) << std::endl;

  var = 3.14;
  std::cout << "double值: " << std::get<double>(var) << std::endl;

  var = "Hello C++17";
  std::cout << "string值: " << std::get<std::string>(var) << std::endl;

  // 使用std::visit
  var = 100;
  std::visit([](auto &&arg) { std::cout << "visit结果: " << arg << std::endl; },
             var);
}

// ==================== 5. std::any ====================
void demo_any() {
  std::cout << "\n=== 5. std::any ===" << std::endl;

  std::any container;

  container = 42;
  std::cout << "存储int: " << std::any_cast<int>(container) << std::endl;

  container = std::string("C++17 any");
  std::cout << "存储string: " << std::any_cast<std::string>(container)
            << std::endl;

  container = 3.14159;
  std::cout << "存储double: " << std::any_cast<double>(container) << std::endl;
}

// ==================== 6. std::string_view ====================
void print_view(std::string_view sv) {
  std::cout << "string_view内容: " << sv << ", 长度: " << sv.size()
            << std::endl;
}

void demo_string_view() {
  std::cout << "\n=== 6. std::string_view ===" << std::endl;

  std::string str = "Hello, C++17 World!";
  const char *cstr = "C-style string";

  // 不会复制字符串，只是视图
  print_view(str);
  print_view(cstr);
  print_view("字面量字符串");

  // 子串视图（无拷贝）
  std::string_view sv = str;
  std::cout << "子串: " << sv.substr(7, 5) << std::endl;
}

// ==================== 7. 折叠表达式 (Fold Expressions) ====================
template <typename... Args> auto sum(Args... args) {
  return (args + ...); // 一元右折叠
}

template <typename... Args> void print_all(Args... args) {
  (std::cout << ... << args) << std::endl; // 二元左折叠
}

void demo_fold_expressions() {
  std::cout << "\n=== 7. 折叠表达式 (Fold Expressions) ===" << std::endl;

  std::cout << "sum(1,2,3,4,5) = " << sum(1, 2, 3, 4, 5) << std::endl;
  std::cout << "sum(1.5, 2.5, 3.0) = " << sum(1.5, 2.5, 3.0) << std::endl;

  std::cout << "print_all: ";
  print_all("A", "-", "B", "-", "C");
}

// ==================== 8. constexpr if ====================
template <typename T> auto process(T value) {
  if constexpr (std::is_integral_v<T>) {
    return value * 2; // 整数类型
  } else if constexpr (std::is_floating_point_v<T>) {
    return value * 1.5; // 浮点类型
  } else {
    return value; // 其他类型
  }
}

void demo_constexpr_if() {
  std::cout << "\n=== 8. constexpr if ===" << std::endl;

  std::cout << "process(10) = " << process(10) << " (整数*2)" << std::endl;
  std::cout << "process(10.0) = " << process(10.0) << " (浮点*1.5)"
            << std::endl;
}

// ==================== 9. 内联变量 (Inline Variables) ====================
struct Config {
  inline static const int MAX_SIZE = 1024;
  inline static const std::string VERSION = "1.0.0";
};

void demo_inline_variables() {
  std::cout << "\n=== 9. 内联变量 (Inline Variables) ===" << std::endl;

  std::cout << "Config::MAX_SIZE = " << Config::MAX_SIZE << std::endl;
  std::cout << "Config::VERSION = " << Config::VERSION << std::endl;
}

// ==================== 10. std::filesystem ====================
void demo_filesystem() {
  std::cout << "\n=== 10. std::filesystem ===" << std::endl;

  namespace fs = std::filesystem;

  // 当前路径
  fs::path current = fs::current_path();
  std::cout << "当前路径: " << current << std::endl;

  // 路径操作
  fs::path file_path = current / "test" / "file.txt";
  std::cout << "拼接路径: " << file_path << std::endl;
  std::cout << "文件名: " << file_path.filename() << std::endl;
  std::cout << "扩展名: " << file_path.extension() << std::endl;
  std::cout << "父目录: " << file_path.parent_path() << std::endl;
}

// ==================== 11. 类模板参数推导 (CTAD) ====================
void demo_ctad() {
  std::cout << "\n=== 11. 类模板参数推导 (CTAD) ===" << std::endl;

  // C++17之前需要: std::pair<int, double> p(1, 2.5);
  std::pair p(1, 2.5); // 自动推导为 std::pair<int, double>
  std::cout << "pair: (" << p.first << ", " << p.second << ")" << std::endl;

  std::vector v = {1, 2, 3, 4, 5}; // 自动推导为 std::vector<int>
  std::cout << "vector size: " << v.size() << std::endl;

  std::tuple t(1, "hello", 3.14); // 自动推导类型
  std::cout << "tuple: (" << std::get<0>(t) << ", " << std::get<1>(t) << ", "
            << std::get<2>(t) << ")" << std::endl;
}

// ==================== 12. [[nodiscard]] 属性 ====================
[[nodiscard]] int compute_important_value() { return 42; }

void demo_attributes() {
  std::cout << "\n=== 12. [[nodiscard]] 属性 ===" << std::endl;

  // 如果不使用返回值，编译器会警告
  int result = compute_important_value();
  std::cout << "重要的计算结果: " << result << std::endl;
}

// ==================== Main ====================
int main() {
  std::cout << "========================================" << std::endl;
  std::cout << "       C++17 新特性演示程序" << std::endl;
  std::cout << "========================================" << std::endl;

  demo_structured_bindings();
  demo_init_statements();
  demo_optional();
  demo_variant();
  demo_any();
  demo_string_view();
  demo_fold_expressions();
  demo_constexpr_if();
  demo_inline_variables();
  demo_filesystem();
  demo_ctad();
  demo_attributes();

  std::cout << "\n========================================" << std::endl;
  std::cout << "       演示结束" << std::endl;
  std::cout << "========================================" << std::endl;

  return 0;
}
