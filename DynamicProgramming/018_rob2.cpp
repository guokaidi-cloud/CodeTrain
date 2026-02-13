#include <vector>
class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   *
   * @param nums int整型vector
   * @return int整型
   */
  int rob(vector<int> &nums) {
    // write code here
    int n = nums.size();
    if (n == 1)
      return nums[0];
    if (n == 2)
      return max(nums[0], nums[1]);
    int ret1 = rob_sub(nums, 0, n - 2);
    int ret2 = rob_sub(nums, 1, n - 1);
    return max(ret1, ret2);
  }

  int rob_sub(vector<int> &nums, int begin, int end) {
    int left = nums[begin];
    int right = max(nums[begin], nums[begin + 1]);
    for (int i = begin + 2; i <= end; ++i) {
      int tmp = max(nums[i] + left, right);
      left = right;
      right = tmp;
    }
    return right;
  }
};