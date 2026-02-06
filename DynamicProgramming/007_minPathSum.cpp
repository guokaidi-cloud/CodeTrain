class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   *
   * @param matrix int整型vector<vector<>> the matrix
   * @return int整型
   */
  int minPathSum(vector<vector<int>> &matrix) {
    // write code here
    int n = matrix.size();
    int m = matrix[0].size();
    for (int i = 1; i < n; ++i) {
      matrix[i][0] += matrix[i - 1][0];
    }

    for (int j = 1; j < m; ++j) {
      matrix[0][j] += matrix[0][j - 1];
    }

    for (int i = 1; i < n; ++i) {
      for (int j = 1; j < m; ++j) {
        matrix[i][j] += min(matrix[i - 1][j], matrix[i][j - 1]);
      }
    }

    return matrix[n - 1][m - 1];
  }
};