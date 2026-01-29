class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   *
   * @param nums int整型vector
   * @param target int整型
   * @return int整型
   */
  int search(vector<int> &nums, int target) {
    // write code here

    int left = 0, right = nums.size() - 1;

    while (left <= right) { // 这边需要注意的是，如果left <=
                            // right，下面的都是mid + 1，或者mid - 1
      int mid = left + (right - left) / 2;
      if (nums[mid] < target) { // 说明target在右边
        left = mid + 1;
      } else if (nums[mid] > target) { // 说明target在左边
        right = mid - 1;
      } else {
        return mid;
      }
    }
    return -1;
  }
};