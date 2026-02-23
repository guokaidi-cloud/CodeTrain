class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   *
   * @param s string字符串
   * @return string字符串vector
   */
  vector<string> restoreIpAddresses(string s) {
    // write code here
    // method: 回溯
    // complexity: 时间 O(n^2)

    std::vector<string> ret; // 结果
    if (s.size() < 4 || s.size() > 12)
      return ret;
    backtrace(s, 0, 0, "", ret);
    return ret;
  }

  void backtrace(string &s, int start, int segcount, string path,
                 std::vector<string> &ret) {
    // 递归终止条件

    if (segcount == 4) {
      if (start == s.size()) {
        path.pop_back(); // 去除最后一个.
        ret.push_back(path);
      }
      return;
    }

    for (int i = start; i < s.size() && i < start + 3; ++i) {
      if (isvalid(s, start, i)) {
        backtrace(s, i + 1, segcount + 1,
                  path + s.substr(start, i - start + 1) + ".", ret);
      }
    }
  }

  bool isvalid(const string &s, int start, int end) {
    // 子串长度超过3 → 非法
    if (end - start + 1 > 3)
      return false;
    // 长度>1且以0开头 → 非法
    if (end > start && s[start] == '0')
      return false;
    // 转换为数字，判断是否在0~255之间
    int num = 0;
    for (int i = start; i <= end; ++i) {
      num = num * 10 + (s[i] - '0');
      // 提前终止：超过255直接返回false
      if (num > 255)
        return false;
    }
    return true;
  }
};