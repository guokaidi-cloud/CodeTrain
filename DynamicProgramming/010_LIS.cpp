class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   * 给定数组的最长严格上升子序列的长度。
   * @param arr int整型vector 给定的数组
   * @return int整型
   */
  int LIS(vector<int> &arr) {
    // write code here

    // method: dp, dp[i] 表示以i为结尾的字符串最长的严格上升子序列长度

    int n = arr.size();
    if (n == 0)
      return 0;
    vector<int> dp(n, 1); // 初始化为1，每个字符都是1

    int ret = 1;
    for (int i = 1; i < n; ++i) {
      for (int j = 0; j < i; ++j) {
        if (arr[i] > arr[j]) {
          dp[i] = max(dp[i], dp[j] + 1);
        }
      }
      ret = max(ret, dp[i]);
    }
    return ret;
  }
};