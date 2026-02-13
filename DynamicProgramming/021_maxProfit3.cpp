class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   * 两次交易所能获得的最大收益
   * @param prices int整型vector 股票每一天的价格
   * @return int整型
   */
  int maxProfit(vector<int> &prices) {
    // write code here

    // method: 动态规划

    int dp0 = 0;          // 从0到i都没有交易
    int dp1 = -prices[0]; // 第一次买入
    int dp2 = 0;          // 第一次卖出
    int dp3 = INT_MIN;    // 第二次买入
    int dp4 = 0;          // 第二次卖出

    for (int i = 1; i < prices.size(); ++i) {
      // int new_dp1 = max(dp1, dp0 - prices[i]);
      // int new_dp2 = max(dp2, dp1 + prices[i]);
      // int new_dp3 = max(dp3, dp2 - prices[i]);
      // int new_dp4 = max(dp4, dp3 + prices[i]);

      // dp1= new_dp1;
      // dp2 = new_dp2;
      // dp3 = new_dp3;
      // dp4 = new_dp4;

      // 倒序更新
      dp4 = max(dp4, dp3 + prices[i]);
      dp3 = max(dp3, dp2 - prices[i]);
      dp2 = max(dp2, dp1 + prices[i]);
      dp1 = max(dp1, dp0 - prices[i]);
    }

    int max_profit = max({dp0, dp2, dp4});
    return max_profit ? max_profit : 0;
  }
};