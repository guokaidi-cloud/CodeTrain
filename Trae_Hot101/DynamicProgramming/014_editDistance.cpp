class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   *
   * @param str1 string字符串
   * @param str2 string字符串
   * @return int整型
   */
  int editDistance(string str1, string str2) {
    // write code here
    // method: 动态规划
    // complexity: 时间 O(n^2), 空间 O(n^2)

    int m = str1.size();
    int n = str2.size();

    std::vector<std::vector<int>> dp(
        m + 1, std::vector<int>(n + 1, 0)); // 需要处理空字符串

    // 初始化边界
    for (int i = 0; i <= m; ++i) {
      dp[i][0] = i;
    }
    for (int j = 0; j <= n; ++j) {
      dp[0][j] = j;
    }

    for (int i = 1; i <= m; ++i) {
      for (int j = 1; j <= n; ++j) {
        if (str1[i - 1] == str2[j - 1]) {
          dp[i][j] = dp[i - 1][j - 1];
        } else {
          dp[i][j] = min(min(dp[i - 1][j - 1], dp[i - 1][j]), dp[i][j - 1]) +
                     1; // 关键是这一步，取三者最小+1
        }
      }
    }
    return dp[m][n];
  }
};