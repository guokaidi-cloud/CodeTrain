// 有两种方法，第一种是两层遍历，时间复杂度是O(mn); 第二种是排序后比较
// 字段序最前面和最后面的字符，时间复杂度耕地，O(nlogn)

class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   *
   * @param strs string字符串vector
   * @return string字符串
   */
  string longestCommonPrefix(vector<string> &strs) {
    // write code here
    if (strs.size() == 0)
      return "";
    std::sort(strs.begin(), strs.end());
    string ret;

    int n = strs.size();
    for (int i = 0; i < strs[0].size() && i < strs[n - 1].size(); ++i) {
      auto b_c = strs[0][i];
      auto e_c = strs[n - 1][i];

      if (b_c == e_c) {
        ret.push_back(b_c);
      } else {
        break;
      }
    }
    return ret;
  }
};