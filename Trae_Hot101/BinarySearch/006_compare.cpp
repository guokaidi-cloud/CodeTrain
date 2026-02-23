// 实际上这是一题字符串的题目

#include <sstream>
class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   * 比较版本号
   * @param version1 string字符串
   * @param version2 string字符串
   * @return int整型
   */
  int compare(string version1, string version2) {
    // method: 流式输入

    vector<string> nums1;
    vector<string> nums2;

    istringstream sin1(version1);
    istringstream sin2(version2);

    string tmp;
    while (getline(sin1, tmp, '.')) {
      nums1.push_back(tmp);
    }

    while (getline(sin2, tmp, '.')) {
      nums2.push_back(tmp);
    }

    for (int i = 0; i < max(nums1.size(), nums2.size()); ++i) {
      // 短的直接赋值为0
      string s1 = i < nums1.size() ? nums1[i] : "0";
      string s2 = i < nums2.size() ? nums2[i] : "0";

      long long num1 = 0;
      for (int j = 0; j < s1.size(); ++j) {
        num1 = num1 * 10 + (s1[j] - '0');
      }

      long long num2 = 0;
      for (int k = 0; k < s2.size(); ++k) {
        num2 = num2 * 10 + (s2[k] - '0');
      }

      if (num1 > num2)
        return 1;
      if (num1 < num2)
        return -1;
    }
    return 0;
  }
};