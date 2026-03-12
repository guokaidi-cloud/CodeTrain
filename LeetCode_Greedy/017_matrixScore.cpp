class Solution {
public:
  int matrixScore(vector<vector<int>> &grid) {
    int m = grid.size(), n = grid[0].size();

    // 第一列全是1
    int ret = m * (1 << (n - 1));

    for (int j = 1; j < n; ++j) {
      int nOnes = 0;
      for (int i = 0; i < m; ++i) {
        if (grid[i][0] == 1) {
          nOnes += grid[i][j];
        } else {
          nOnes += 1 - grid[i][j];
        }
      }

      int k = max(nOnes, m - nOnes);
      // 这一步要注意是k，然后 n - j - 1，可以想一下0的位置
      ret += k * (1 << (n - j - 1));
    }
    return ret;
  }
};