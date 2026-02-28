class Solution {
public:
  int jump(vector<int> &nums) {
    // method: 贪心

    int maxpos = 0;
    int end = 0;
    int step = 0;

    // 不需要遍历最后一个了，因为遍历到最后倒数第一个的时候一定+1跳能跳到
    for (int i = 0; i < nums.size() - 1; ++i) {
      if (maxpos >= i) {
        maxpos = max(maxpos, nums[i] + i);
        if (i == end) {
          end = maxpos;
          ++step;
        }
      }
    }
    return step;
  }
};