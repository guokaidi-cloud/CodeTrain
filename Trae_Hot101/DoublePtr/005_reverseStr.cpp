class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   * 反转字符串
   * @param str string字符串
   * @return string字符串
   */
  string solve(string str) {
    // write code here
    if (str.size() < 2)
      return str;
    int left = 0, right = str.size() - 1;
    while (left < right) {
      swap(str[left], str[right]);
      ++left;
      --right;
    }
    return str;
  }
};