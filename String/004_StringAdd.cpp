#include <string>
class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   * 计算两个数之和
   * @param s string字符串 表示第一个整数
   * @param t string字符串 表示第二个整数
   * @return string字符串
   */
  string solve(string s, string t) {
    // write code here

    int i = s.size() - 1;
    int j = t.size() - 1;
    string ret;

    int sum = 0, count = 0;
    while (i >= 0 && j >= 0) {
      sum = (s[i] - '0' + t[j] - '0' + count) % 10;
      count = (s[i] - '0' + t[j] - '0' + count) / 10;
      ret.push_back(sum + '0');
      --i;
      --j;
    }

    while (i >= 0) {
      sum = (s[i] - '0' + count) % 10;
      count = (s[i] - '0' + count) / 10;
      ret.push_back(sum + '0');
      --i;
    }

    while (j >= 0) {
      sum = (t[j] - '0' + count) % 10;
      count = (t[j] - '0' + count) / 10;
      ret.push_back(sum + '0');
      --j;
    }

    if (count)
      ret.push_back('1');

    reverse(ret.begin(), ret.end());
    return ret;
  }
};