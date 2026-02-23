#include <algorithm>
#include <cctype>
class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   *
   * @param s string字符串
   * @param n int整型
   * @return string字符串
   */
  string trans(string s, int n) {
    // write code here
    // method: 双反转
    // complexity: 时间 O(n), 空间 O(n)
    if (n == 0)
      return "";

    // 步骤1: 遍历整个字符串，切换大小写
    for (char &c : s) {
      c = islower(c) ? toupper(c) : tolower(c);
    }

    // 步骤2: 反转字符串
    reverse(s.begin(), s.end());

    // 步骤3: 反转每个单词
    int start = 0;
    for (int i = 0; i < n; ++i) {
      if (s[i] == ' ') { // 遇到空格反转
        reverse(s.begin() + start, s.begin() + i);
        start = i + 1;
      } else if (i == n - 1) { // 最后一个反转
        reverse(s.begin() + start, s.end());
      }
    }
    return s;
  }
};