class Solution {
public:
  int twoCitySchedCost(vector<vector<int>> &costs) {
    std::sort(costs.begin(), costs.end(),
              [](const vector<int> &a, const vector<int> &b) {
                return abs(a[0] - a[1]) > abs(b[0] - b[1]);
              });
    int n = costs.size() / 2;
    int a = 0, b = 0;
    int ret = 0;
    for (int i = 0; i < costs.size(); ++i) {
      if ((costs[i][0] < costs[i][1] && a < n) || b == n) { // 这里为什么需要判断b，因为非对称，也需要约束一下，考虑如果一直costs[i][0]
                                                            // > costs[i][1]
        ret += costs[i][0];
        ++a;
      } else {
        ret += costs[i][1];
        ++b;
      }
    }

    return ret;
  }
};