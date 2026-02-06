class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   * longest common substring
   * @param str1 string字符串 the string
   * @param str2 string字符串 the string
   * @return string字符串
   */
  string LCS(string str1, string str2) {
    // write code here

    // method: dp
    // if str1[i] == str[j], dp[i][j] = dp[i-1][j-1]
    // else dp[i][j] = 0;

    int n = str1.size(), m = str2.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));

    int end = 0;
    int max_len = 0;
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= m; ++j) {
        if (str1[i - 1] == str2[j - 1]) {
          dp[i][j] = dp[i - 1][j - 1] + 1;
          if (dp[i][j] > max_len) {
            // 这里要小心索引
            end = i;
            max_len = dp[i][j];
          }
        } else {
          dp[i][j] = 0;
        }
      }
    }

    return str1.substr(end - max_len, max_len);
  }
};