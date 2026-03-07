class Solution {
public:
  vector<vector<int>> restoreMatrix(vector<int> &rowSum, vector<int> &colSum) {
    // 贪心：填一个行和列最小的
    int n = rowSum.size();
    int m = colSum.size();
    vector<vector<int>> ret(n, vector<int>(m));

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        auto val = std::min(rowSum[i], colSum[j]);
        ret[i][j] = val;
        rowSum[i] -= val;
        colSum[j] -= val;
      }
    }
    return ret;
  }
};