class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   *
   * @param s string字符串
   * @return bool布尔型
   */
  bool isValid(string s) {
    // write code here
    stack<char> stack;
    for (const auto &ch : s) {
      if (ch == '[' || ch == '(' || ch == '{') {
        stack.push(ch);
      }

      if (ch == ']') {
        if (stack.empty() || stack.top() != '[') {
          return false;
        } else {
          stack.pop();
        }
      }

      if (ch == ')') {
        if (stack.empty() || stack.top() != '(') {
          return false;
        } else {
          stack.pop();
        }
      }

      if (ch == '}') {
        if (stack.empty() || stack.top() != '{') {
          return false;
        } else {
          stack.pop();
        }
      }
    }

    return stack.empty();
  }
};