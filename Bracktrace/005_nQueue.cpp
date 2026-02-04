class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   *
   * @param n int整型 the n
   * @return int整型
   */
  int Nqueen(int n) {
    // write code here
    // method: 递归/回溯，斜线可以使用 row - col 正斜线和row + col 副斜线

    std::vector<std::vector<char>> grid(n, std::vector<char>(n, '0'));
    std::vector<bool> col_used(n, false);
    std::vector<bool> main_used(2 * n - 1, false); // 主斜线
    std::vector<bool> sub_used(2 * n - 1, false);  // 副斜线,不需要减少
    int ret = 0;
    backtrace(ret, 0, col_used, main_used, sub_used, grid);
    return ret;
  }

  void backtrace(int &ret, int row, std::vector<bool> &col_used,
                 std::vector<bool> &main_used, std::vector<bool> &sub_used,
                 std::vector<std::vector<char>> &grid) {
    int n = grid.size();
    // 如果达到了最后一行
    if (row == n) {
      ++ret;
      return;
    }
    for (int j = 0; j < n; ++j) {
      // 如果已经被标记了，就跳过
      if (col_used[j] || main_used[row - j + (n - 1)] || sub_used[row + j]) {
        continue;
      }
      col_used[j] = true;
      main_used[row - j + (n - 1)] = true;
      sub_used[row + j] = true;
      backtrace(ret, row + 1, col_used, main_used, sub_used, grid);
      col_used[j] = false;
      main_used[row - j + (n - 1)] = false;
      sub_used[row + j] = false;
    }
  }
};