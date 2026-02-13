class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   * 计算最大收益
   * @param prices int整型vector 股票每一天的价格
   * @return int整型
   */
  int maxProfit(vector<int> &prices) {
    // write code here
    // method: 只要有上涨的都抓住机会

    int profit = 0;
    for (int i = 0; i < prices.size() - 1; ++i) {
      if (prices[i + 1] > prices[i]) {
        profit += prices[i + 1] - prices[i];
      }
    }
    return profit;
  }
};