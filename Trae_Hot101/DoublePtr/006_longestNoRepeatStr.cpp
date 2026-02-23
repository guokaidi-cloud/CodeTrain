#include <unordered_map>
class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   *
   * @param arr int整型vector the array
   * @return int整型
   */
  int maxLength(vector<int> &arr) {
    // write code here

    std::unordered_map<int, int> hash;

    int left = 0, right = 0;
    int max_len = 0;

    while (right < arr.size()) {
      // 右指针右移
      hash[arr[right]]++;
      while (hash[arr[right]] > 1) {
        // 左指针右移
        hash[arr[left]]--;
        left++;
      }
      max_len = max(max_len, right - left + 1);
      right++;
    }
    return max_len;
  }
};