class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   * 返回表达式的值
   * @param s string字符串 待计算的表达式
   * @return int整型
   */
  // 数字栈：存放操作数
  // 运算符栈：存放运算符和括号
  // 关键思想：遇到运算符时，判断优先级，决定是否进行前面的计算

  int solve(string s) {
    // write code here
    // 数字栈和操作符号栈
    std::stack<int> nums;
    std::stack<char> ops;

    int n = s.size();
    for (int i = 0; i < n; ++i) {
      if (std::isdigit(s[i])) {
        int num = (s[i] - '0');
        while (i + 1 < n && std::isdigit(s[i + 1])) {
          num = num * 10 + (s[++i] - '0');
        }
        nums.emplace(num);
      } else if (s[i] == '(') {
        // 左括号直接入栈
        ops.emplace(s[i]);
      } else if (s[i] == ')') {
        // 右括号：计算括号内的表达式
        while (!ops.empty() && ops.top() != '(') {
          calculate(nums, ops);
        }
        // 弹出左括号
        ops.pop();
      } else {
        // 三个运算符: +-*
        // 当前运算符优先级 <= 栈顶运算符优先级时，先计算栈顶的
        while (!ops.empty() && priority(s[i]) <= priority(ops.top())) {
          calculate(nums, ops);
        }
        ops.emplace(s[i]);
      }
    }

    // 计算剩余的ops
    while (!ops.empty()) {
      calculate(nums, ops);
    }
    return nums.top();
  }

private:
  int priority(char op) {
    if (op == '+' || op == '-')
      return 1;
    if (op == '*')
      return 2;
    return 0;
  }

  void calculate(std::stack<int> &nums, std::stack<char> &ops) {
    if (nums.size() < 2)
      return;

    int b = nums.top();
    nums.pop();
    int a = nums.top();
    nums.pop();

    char op = ops.top();
    ops.pop();

    int ret = 0;
    if (op == '+')
      ret = a + b;
    if (op == '-')
      ret = a - b;
    if (op == '*')
      ret = a * b;

    nums.emplace(ret);
    return;
  }
};