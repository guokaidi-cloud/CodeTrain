class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   *
   * @param s string字符串
   * @return int整型
   */
  int longestValidParentheses(string s) {
    // write code here
    int n = s.size();
    if (n < 2)
      return 0;

    vector<int> dp(n, 0);
    int max_len = 0;

    for (int i = 1; i < n; ++i) {
      // 核心前提: 只有当字符是')'时，才可能形成有效括号
      if (s[i] == ')') {
        // 情况1：当前')'与前一个'('直接配对
        if (s[i - 1] == '(') {
          dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
        } else { // 情况2：当前')'前一个也是')'，需找更前面的'('匹配
          int match_left_idx = i - dp[i - 1] - 1;
          if (match_left_idx >= 0 && s[match_left_idx] == '(') {
            dp[i] = dp[i - 1] + 2 +
                    (match_left_idx - 1 >= 0 ? dp[match_left_idx - 1] : 0);
          }
        }
      }
      max_len = max(max_len, dp[i]);
    }
    return max_len;
  }
};