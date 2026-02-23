class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   *
   * @param matrix int整型vector<vector<>>
   * @return int整型vector
   */
  vector<int> spiralOrder(vector<vector<int>> &matrix) {
    // write code here

    vector<int> ret;
    // 边界条件: 矩阵为空
    if (matrix.empty() || matrix[0].empty()) {
      return ret;
    }

    // 1. 初始化四个边界
    int m = matrix.size();
    int n = matrix[0].size();

    int top = 0;
    int bottom = m - 1;
    int left = 0;
    int right = n - 1;

    while (left <= right && top <= bottom) {
      // 从左到右
      for (int i = left; i <= right; ++i) {
        ret.push_back(matrix[top][i]);
      }
      ++top;

      // 从上到下
      for (int i = top; i <= bottom; ++i) {
        ret.push_back(matrix[i][right]);
      }
      --right;

      // 从右到左
      if (top <= bottom) {
        for (int i = right; i >= left; --i) {
          ret.push_back(matrix[bottom][i]);
        }
        --bottom;
      }

      // 从下到上
      if (left <= right) {
        for (int i = bottom; i >= top; --i) {
          ret.push_back(matrix[i][left]);
        }
        ++left;
      }
    }
    return ret;
  }
};