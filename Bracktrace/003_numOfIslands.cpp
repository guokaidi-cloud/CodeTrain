class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   * 判断岛屿数量
   * @param grid char字符型vector<vector<>>
   * @return int整型
   */
  int solve(vector<vector<char>> &grid) {
    // write code here
    // method: 找到一个1，就dfs把所有相互连接的给置为0
    if (grid.empty() || grid[0].empty())
      return 0;

    int n = grid.size(), m = grid[0].size();
    int ret = 0;

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (grid[i][j] == '1') {
          ++ret;
          dfs_zero(grid, i, j);
        }
      }
    }
    return ret;
  }

  void dfs_zero(vector<vector<char>> &grid, int i, int j) {
    grid[i][j] = '0';
    // 上下左右
    for (int k = 0; k < 4; ++k) {
      int y = i + y_diff[k];
      int x = j + x_diff[k];
      // 这里的边界条件需要小心
      if (y >= 0 && y < grid.size() && x >= 0 && x < grid[0].size()) {
        if (grid[y][x] == '1') {
          grid[y][x] = '0';
          dfs_zero(grid, y, x);
        }
      }
    }
  }

private:
  std::vector<int> y_diff = {1, 0, -1, 0};
  std::vector<int> x_diff = {0, 1, 0, -1};
};