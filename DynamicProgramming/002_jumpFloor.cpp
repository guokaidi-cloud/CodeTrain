class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   *
   * @param number int整型
   * @return int整型
   */
  int jumpFloor(int number) {
    // write code here
    // method: 动态规划
    // complexity: 时间 O(n)
    if (number == 1)
      return 1;
    if (number == 2)
      return 2;
    int l = 1, r = 2;
    for (int i = 3; i <= number; ++i) {
      int tmp = l + r;
      l = r;
      r = tmp;
    }
    return r;
  }
};