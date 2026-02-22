class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   * max water
   * @param arr int整型vector the array
   * @return long长整型
   */
  long long maxWater(vector<int> &arr) {
    // write code here
    // method: 双指针, 哪边低就先积累哪边的
    // complexity: 时间 O(n), 空间 O(1)
    if (arr.size() <= 2)
      return 0;
    int left = 0, right = arr.size() - 1;
    int left_max = left, right_max = right;
    long long water = 0;
    while (left < right) {
      if (arr[left] < arr[right]) { // 左边低, 积累左边的
        if (arr[left] < arr[left_max]) {
          water += arr[left_max] - arr[left];
        } else {
          left_max = left;
        }
        ++left;
      } else {
        if (arr[right] < arr[right_max]) {
          water += arr[right_max] - arr[right];
        } else {
          right_max = right;
        }
        --right;
      }
    }
    return water;
  }
};