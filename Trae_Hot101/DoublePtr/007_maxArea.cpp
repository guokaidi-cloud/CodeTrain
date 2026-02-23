class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   *
   * @param height int整型vector
   * @return int整型
   */
  int maxArea(vector<int> &height) {
    // write code here
    int max_val = 0;
    if (height.size() < 2)
      return max_val;
    int left = 0, right = height.size() - 1;

    while (left < right) {
      int water_height = min(height[left], height[right]);
      int water = water_height * (right - left);
      if (water > max_val) {
        max_val = water;
      }
      if (height[left] > height[right]) {
        --right;
      } else {
        ++left;
      }
    }
    return max_val;
  }
};