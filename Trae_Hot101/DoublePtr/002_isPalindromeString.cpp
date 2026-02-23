class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   *
   * @param str string字符串 待判断的字符串
   * @return bool布尔型
   */
  bool judge(string str) {
    // write code here

    if (str.size() == 0)
      return true;

    int l = 0, r = str.size() - 1;
    while (l < r) {
      if (str[l] != str[r]) {
        return false;
      }
      ++l, --r;
    }
    return true;
  }
};