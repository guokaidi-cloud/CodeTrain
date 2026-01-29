class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   *
   * @param nums int整型vector
   * @return int整型
   */
  int minNumberInRotateArray(vector<int> &nums) {
    // method: 二分查找
    // complexity: 时间 O(log n) 空间 O(1)
    int n = nums.size();
    if (n < 2)
      return nums[0];

    int left = 0, right = nums.size() - 1;

    while (left < right) {
      int mid = left + (right - left) / 2;

      if (nums[mid] == nums[right]) {
        // 这种情况不好判断，直接right = right -1 再判断
        right = right - 1;
      } else if (nums[mid] > nums[right]) {
        // 中间比右边高，那肯定在右边
        left = mid + 1;
      } else {
        // 中间比右边低，肯定在左边
        right = mid;
      }
    }
    return nums[left];
  }
};