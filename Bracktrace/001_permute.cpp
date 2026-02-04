class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   *
   * @param num int整型vector
   * @return int整型vector<vector<>>
   */
  vector<vector<int>> permute(vector<int> &num) {
    // write code here
    // method: 递归、回溯
    // complexity: 时间 O(n × n!), 空间 O(n)
    vector<vector<int>> ret;
    vector<int> path;
    vector<int> used(num.size(), false);
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
      if (used[i])
        continue;

      used[i] = true;
      path.emplace_back(num[i]);
      backtrace(ret, path, used, num);
      path.pop_back();
      used[i] = false;
    }
  }
};

/* 递归/回溯经典写法
1. 递归终止条件
2. 遍历所有数字，选择 “未被使用” 的数字
3. 标记数字为true、递归深入
4. 回溯,并将标记重新置为false
*/