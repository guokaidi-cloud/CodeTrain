class Solution {
public:
  int arrayPairSum(vector<int> &nums) {
    // nums[n-1] 和 nums[n-2] 组合最好，然后划分子区间
    sort(nums.begin(), nums.end());
    int sum = 0;
    for (int i = 0; i < nums.size(); i += 2) {
      sum += nums[i];
    }
    return sum;
  }
};