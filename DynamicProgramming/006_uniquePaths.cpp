class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   *
   * @param m int整型
   * @param n int整型
   * @return int整型
   */
  int uniquePaths(int m, int n) {
    // write code here

    if (m == 1 || n == 1)
      return 1;
    std::vector<std::vector<int>> dp(m, std::vector<int>(n, 0));

    for (int i = 0; i < m; ++i) {
      dp[i][0] = 1;
    }

    for (int j = 0; j < n; ++j) {
      dp[0][j] = 1;
    }

    for (int i = 1; i < m; ++i) {
      for (int j = 1; j < n; ++j) {
        dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
      }
    }

    return dp[m - 1][n - 1];
  }
};