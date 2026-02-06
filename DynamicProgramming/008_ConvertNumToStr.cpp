class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   * 解码
   * @param nums string字符串 数字串
   * @return int整型
   */
  int solve(string nums) {
    // write code here
    if (nums.size() == 0)
      return 0;
    if (nums[0] == '0')
      return 0;
    if (nums.size() == 1)
      return 1;

    int n = nums.size();
    int prev = 1; // dp[n-2]
    int cur = 1;  // dp[n-1]
    for (int i = 1; i < n; ++i) {
      int tmp = 0;
      if (nums[i] != '0') {
        tmp += cur;
      }
      if ((nums[i - 1] == '1' || nums[i - 1] == '2') &&
          check(nums[i - 1], nums[i])) {
        tmp += prev;
      }

      if (tmp == 0)
        return 0;

      prev = cur;
      cur = tmp;
    }
    return cur;
  }

  bool check(char ch1, char ch2) {
    int num = (ch1 - '0') * 10 + (ch2 - '0');
    if (num >= 10 && num < 27) {
      return true;
    }
    return false;
  }
};