class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   *
   * @param str string字符串
   * @return string字符串vector
   */
  vector<string> Permutation(string str) {
    // write code here
    // method: 先排序，再递归回溯
    std::sort(str.begin(), str.end());
    vector<string> ret;
    string path;
    vector<bool> used(str.size(), false);
    backtrace(ret, path, used, str);
    return ret;
  }

  void backtrace(vector<string> &ret, string &path, vector<bool> &used,
                 string &str) {
    if (path.size() == str.size()) {
      ret.emplace_back(path);
      return;
    }

    for (int i = 0; i < str.size(); ++i) {
      if (used[i] || (i > 0 && str[i] == str[i - 1] && !used[i - 1])) {
        continue;
      }

      used[i] = true;
      path.push_back(str[i]);
      backtrace(ret, path, used, str);
      path.pop_back();
      used[i] = false;
    }
  }
};