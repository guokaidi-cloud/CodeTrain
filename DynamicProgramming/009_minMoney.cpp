class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   * 最少货币数
   * @param arr int整型vector the array
   * @param aim int整型 the target
   * @return int整型
   */
  int minMoney(vector<int> &arr, int aim) {
    // write code here
    // method: 完全背包
    if (aim == 0)
      return 0;
    if (arr.empty() || aim < 0)
      return -1;

    int max_val = aim + 1;                 // 最多需要aim张
    std::vector<int> dp(aim + 1, max_val); // 组合dp[i]元所需的最小张数
    dp[0] = 0;                             // 这一步非常重要

    for (int i = 1; i <= aim; ++i) {
      for (int coin : arr) {
        if (coin <= i) {
          dp[i] = min(dp[i], dp[i - coin] + 1);
        }
      }
    }

    return (dp[aim] == max_val) ? -1 : dp[aim];
  }
};