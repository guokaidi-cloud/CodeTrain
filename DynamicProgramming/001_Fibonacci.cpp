class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   *
   * @param n int整型
   * @return int整型
   */
  int Fibonacci(int n) {
    // write code here
    if (n == 1 || n == 2)
      return 1;
    int l1 = 1, l2 = 1;
    for (int i = 3; i < n; ++i) {
      int tmp = l1 + l2;
      l1 = l2;
      l2 = tmp;
    }
    return l1 + l2;
  }
};