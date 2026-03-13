class Solution {
public:
  int singleNumber(vector<int> &nums) {
    int ret = 0;

    for (int i = 0; i < 32; ++i) {
      int total = 0;
      for (auto num : nums) {
        // 加上最后一位, 要不是0，要不是1
        total += ((num >> i) & 1);
      }

      if ((total % 3)) {
        // 答案数字是 32 位二进制组成的，不能直接return
        ret |= (1 << i);
      }
    }
    return ret;
  }
};