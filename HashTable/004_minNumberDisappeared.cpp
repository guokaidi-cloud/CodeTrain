#include <unordered_map>
class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   *
   * @param nums int整型vector
   * @return int整型
   */
  // int minNumberDisappeared(vector<int>& nums) {
  //     // write code here
  //     // method: explicit hash
  //     // complexity: 时间 O(n), 空间O(n)

  //     std::unordered_map<int, int> hash;

  //     for(auto num : nums){
  //         hash[num]++;
  //     }
  //     int res = 1;
  //     while(hash.find(res) != hash.end()){
  //         ++res;
  //     }
  //     return res;
  // }

  int minNumberDisappeared(vector<int> &nums) {
    // write code here
    // method: implicit hash, 使用vector的空间作为hash表
    // complexity: 时间 O(n), 空间O(1)

    int n = nums.size();
    // 如果是负数，就设置为n，这样后面就不会
    for (int i = 0; i < n; ++i) {
      if (nums[i] <= 0) {
        nums[i] = n + 1;
      }
    }

    // 如果出现了正数，小于n，就把值对应的index设置为负数
    for (int i = 0; i < n; ++i) {
      int num = abs(nums[i]);
      if (num <= n) { // 无重复数字, 如果数值大于n
        nums[num - 1] = -nums[num - 1];
      }
    }

    // 第一个非负数
    for (int i = 0; i < n; ++i) {
      if (nums[i] > 0) {
        return i + 1;
      }
    }

    return n + 1;
  }
};
