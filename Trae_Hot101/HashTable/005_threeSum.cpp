class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   *
   * @param num int整型vector
   * @return int整型vector<vector<>>
   */
  vector<vector<int>> threeSum(vector<int> &num) {
    // write code here
    // method: 先排序，再快慢指针
    // complexity: 时间 O(nlogn) + O(n^2), 空间 O(1)
    vector<vector<int>> ret;
    if (num.empty())
      return ret;
    std::sort(num.begin(), num.end());
    for (int i = 0; i < num.size() - 2; ++i) {
      if (num[i] > 0)
        break;

      // 当num[i]和num[i-1]相同时候，因为num[i]已经把所有可能给遍历了
      // num[i-1]作为第一个时候，也只是num[i]作为第一个的子集
      if (i > 0 && num[i] == num[i - 1])
        continue;
      // 快慢指针
      int l = i + 1;
      int r = num.size() - 1;
      while (l < r) {
        if (num[l] + num[r] == -num[i]) {
          ret.emplace_back(std::vector<int>{num[i], num[l], num[r]});
          // 去除相同的解
          while (l < r && num[l] == num[l + 1])
            ++l;
          while (l < r && num[r] == num[r - 1])
            --r;
          ++l;
          --r;
        } else if (num[l] + num[r] < -num[i]) {
          ++l;
        } else {
          --r;
        }
      }
    }

    return ret;
  }
};