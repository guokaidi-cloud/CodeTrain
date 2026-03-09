class Solution {
public:
  int wiggleMaxLength(vector<int> &nums) {
    int n = nums.size();
    if (n <= 1)
      return n; // 边界：空/单元素直接返回

    int res = 1;      // 基础长度：至少1个元素
    int pre_diff = 0; // 前一次的差值（初始为0）

    for (int i = 1; i < n; ++i) {
      int cur_diff = nums[i] - nums[i - 1];
      // 核心条件：当前差值非0，且与前差值符号相反
      if ((cur_diff > 0 && pre_diff <= 0) || (cur_diff < 0 && pre_diff >= 0)) {
        res++;
        pre_diff = cur_diff; // 仅当摆动有效时，更新前差值
      }
    }

    return res;
  }
};