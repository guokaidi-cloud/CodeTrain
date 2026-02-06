class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   *
   * @param cost int整型vector
   * @return int整型
   */
  int minCostClimbingStairs(vector<int> &cost) {
    // write code here
    // method: dp

    if (cost.size() == 1) {
      return cost[0];
    }
    if (cost.size() == 2) {
      return min(cost[0], cost[1]);
    }

    for (int i = 2; i < cost.size(); ++i) {
      cost[i] = min(cost[i - 1], cost[i - 2]) + cost[i];
    }

    return min(cost[cost.size() - 1], cost[cost.size() - 2]);
  }
};