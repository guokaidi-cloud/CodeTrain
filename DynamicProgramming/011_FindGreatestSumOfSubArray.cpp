class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   *
   * @param array int整型vector
   * @return int整型
   */
  int FindGreatestSumOfSubArray(vector<int> &array) {
    // write code here

    // method: dp, dp[i] 表示当前节点往前的最大子数组，原地进行吧
    // complexity: 时间 O(n)， 空间O(1)

    if (array.size() == 1)
      return array[0];
    int ret = INT_MIN;
    for (int i = 1; i < array.size(); ++i) {
      if (array[i - 1] > 0) {
        array[i] += array[i - 1];
      }
      ret = max(ret, array[i]);
    }
    return ret;
  }
};