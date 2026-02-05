class Solution {
public:
  int solve(vector<vector<int>> &matrix) {
    if (matrix.empty() || matrix[0].empty())
      return 0;
    int m = matrix.size(), n = matrix[0].size();
    int maxLen = 0;

    // memo[i][j] 记录从(i,j)出发的最长递增路径长度
    vector<vector<int>> memo(m, vector<int>(n, 0));

    // 方向数组
    vector<int> dirs = {0, 1, 0, -1, 0}; // 技巧：这样写便于循环

    // DFS函数：返回从(i,j)出发的最长递增路径长度
    function<int(int, int)> dfs = [&](int i, int j) -> int {
      if (memo[i][j] != 0)
        return memo[i][j]; // 已经计算过

      int maxPath = 1; // 至少包含自己

      // 尝试四个方向
      for (int k = 0; k < 4; k++) {
        int ni = i + dirs[k];
        int nj = j + dirs[k + 1];

        if (ni >= 0 && ni < m && nj >= 0 && nj < n &&
            matrix[ni][nj] > matrix[i][j]) {
          maxPath = max(maxPath, 1 + dfs(ni, nj));
        }
      }

      memo[i][j] = maxPath; // 记忆化
      return maxPath;
    };

    // 对每个点作为起点进行DFS
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        maxLen = max(maxLen, dfs(i, j));
      }
    }

    return maxLen;
  }
};