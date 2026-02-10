class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   *
   * @param str string字符串
   * @param pattern string字符串
   * @return bool布尔型
   */
  bool match(string str, string pattern) {
    // 获取字符串和模式串的长度
    int m = str.size(), n = pattern.size();
    // 初始化DP数组：dp[i][j] 表示str前i个字符和pattern前j个字符是否匹配
    vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
    // 边界条件：空字符串匹配空模式串
    dp[0][0] = true;

    // 处理「空字符串 + 非空模式串」的情况（如pattern="a*"匹配空串）
    for (int j = 1; j <= n; ++j) {
      if (pattern[j - 1] == '*') {
        // *匹配0个前置字符，继承dp[0][j-2]的状态（需j>=2，否则j-2越界，保持false）
        if (j >= 2) {
          dp[0][j] = dp[0][j - 2];
        }
      }
    }

    // 填充DP数组
    for (int i = 1; i <= m; ++i) {
      for (int j = 1; j <= n; ++j) {
        // 场景1：模式串当前字符是普通字符 或 .
        if (pattern[j - 1] == str[i - 1] || pattern[j - 1] == '.') {
          dp[i][j] = dp[i - 1][j - 1];
        }
        // 场景2：模式串当前字符是*
        else if (pattern[j - 1] == '*') {
          // 确保j>=2（*必须有前置字符），否则直接false
          if (j >= 2) {
            // 情况1：*匹配0个前置字符，继承dp[i][j-2]的状态
            dp[i][j] = dp[i][j - 2];
            // 情况2：*匹配至少1个前置字符（需前置字符匹配）
            if (pattern[j - 2] == str[i - 1] || pattern[j - 2] == '.') {
              dp[i][j] = dp[i][j] || dp[i - 1][j];
            }
          }
        }
      }
    }

    // 返回str全部字符和pattern全部字符是否匹配
    return dp[m][n];
  }
};