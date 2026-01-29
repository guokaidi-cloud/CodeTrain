// 这个题目有问题，如果全是相等的边界情况不对？

class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   *
   * @param nums int整型vector
   * @return int整型
   */
  int findPeakElement(vector<int> &nums) {
    // method: 二分查找，压缩分段区间
    // complexity: 时间 O(log n), 空间 O(1)
    if (nums.size() == 1)
      return 0; // 要求返回的是索引
    int n = nums.size();
    int left = 0, right = n - 1;
    while (left < right) {
      int mid = left + (right - left) / 2;
      nums[mid] < nums[mid + 1] ? left = mid + 1 : right = mid;
    }
    return left;
  }
};