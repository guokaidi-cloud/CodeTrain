class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   *
   * @param num int整型vector
   * @return int整型vector<vector<>>
   */
  vector<vector<int>> permuteUnique(vector<int> &num) {
    vector<vector<int>> ret;
    vector<int> path;
    vector<int> used(num.size(), false);
    std::sort(num.begin(), num.end());
    backtrace(ret, path, used, num);
    return ret;
  }

  void backtrace(vector<vector<int>> &ret, vector<int> &path, vector<int> &used,
                 vector<int> &num) {
    if (path.size() == num.size()) {
      ret.emplace_back(path);
      return;
    }

    for (int i = 0; i < num.size(); ++i) {
      // 这个条件避免了出现重复序列：i > 0 && num[i] == num[i-1] && !used[i-1]
      // 保证都是按顺序进行的
      if (used[i] || (i > 0 && num[i] == num[i - 1] && !used[i - 1]))
        continue;

      used[i] = true;
      path.emplace_back(num[i]);
      backtrace(ret, path, used, num);
      path.pop_back();
      used[i] = false;
    }
  }
};
