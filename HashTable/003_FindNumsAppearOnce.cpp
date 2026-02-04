class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   *
   * @param nums int整型vector
   * @return int整型vector
   */
  vector<int> FindNumsAppearOnce(vector<int> &nums) {
    // write code here

    // method: 位运算法
    // complexity: 时间 O(n), 空间 O(1)

    int ret = 0;
    for (auto num : nums) {
      ret ^= num;
    }

    int diff_count =
        ret & (-ret); // 机组:一个数和它的负数进行与操作，得到最后一位不为0的数

    int ret1 = 0, ret2 = 0;
    for (auto num : nums) {
      if (num & diff_count) {
        ret1 ^= num;
      } else {
        ret2 ^= num;
      }
    }

    return (ret1 > ret2) ? vector<int>{ret2, ret1} : vector<int>{ret1, ret2};
  }
};