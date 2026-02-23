class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   *
   * @param prices int整型vector
   * @return int整型
   */
  int maxProfit(vector<int> &prices) {
    // write code here
    int n = prices.size();

    if (n == 0 || n == 1) {
      return 0;
    }

    int min_value = prices[0];
    int profit = 0;

    for (int i = 1; i < n; ++i) {
      if (prices[i] > min_value) {
        profit = max(prices[i] - min_value, profit);
      }

      if (prices[i] < min_value) {
        min_value = prices[i];
      }
    }

    return profit;
  }
};