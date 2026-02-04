class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   *
   * @param n int整型
   * @return string字符串vector
   */
  vector<string> generateParenthesis(int n) {
    // write code here
    vector<string> ret;
    string path;
    int left = 0;
    int right = 0;
    backtrace(ret, path, left, right, n);
    return ret;
  }

  void backtrace(vector<string> &ret, std::string &path, int left, int right,
                 int n) {
    if (left == n && right == n) {
      ret.emplace_back(path);
      return;
    }
    // 分支1:左括号数量小于n，可添加左括号
    if (left < n) {
      ++left;
      path.push_back('(');
      backtrace(ret, path, left, right, n);
      path.pop_back();
      --left;
    }
    // 分支2:右括号数目少于左括号时候
    if (right < left) {
      ++right;
      path.push_back(')');
      backtrace(ret, path, left, right, n);
      path.pop_back();
      --right;
    }
  }
};