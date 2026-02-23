#include <algorithm>
class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   *
   * @param mat int整型vector<vector<>>
   * @param n int整型
   * @return int整型vector<vector<>>
   */
  vector<vector<int>> rotateMatrix(vector<vector<int>> &mat, int n) {
    // write code here

    /* method:
    对角线互换 (i,j) -> (j,i)
    左右互换 (j,i) -> (j, n - i - 1)
    比如(0,1) -> (1,2)
    这个就是顺时针旋转90度
    */

    for (int i = 0; i < mat.size(); ++i) {
      for (int j = 0; j < i; ++j) {
        swap(mat[i][j], mat[j][i]);
      }
    }

    for (int i = 0; i < mat.size(); ++i) {
      reverse(mat[i].begin(), mat[i].end());
    }

    return mat;
  }
};