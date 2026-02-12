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

    if (nums.size() == 1)
      return nums[0];
    if (nums.size() == 2)
      return max(nums[0], nums[1]);

    int left = nums[0], right = max(nums[0], nums[1]);

    for (int i = 2; i < nums.size(); ++i) {
      int tmp = max(left + nums[i], right);
      left = right;
      right = tmp;
    }
    return right;
  }
};