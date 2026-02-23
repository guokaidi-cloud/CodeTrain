class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   * 旋转数组
   * @param n int整型 数组长度
   * @param m int整型 右移距离
   * @param a int整型vector 给定数组
   * @return int整型vector
   */
  vector<int> solve(int n, int m, vector<int> &a) {
    // write code here
    // method: 三次翻转

    int k = m % n;

    reverse(a.begin(), a.end());
    reverse(a.begin(), a.begin() + k);
    reverse(a.begin() + k, a.end());

    return a;
  }
};