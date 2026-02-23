#include <numeric>

class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   * pick candy
   * @param arr int整型vector the array
   * @return int整型
   */
  int candy(vector<int> &arr) {
    // write code here
    // method: 贪心,左往右遍历和右往左遍历

    std::vector<int> candies(arr.size(), 1);
    for (int i = 0; i < arr.size() - 1; ++i) {
      if (arr[i + 1] > arr[i]) {
        candies[i + 1] = candies[i] + 1;
      }
    }

    for (int i = arr.size() - 1; i > 0; --i) {
      if (arr[i - 1] > arr[i]) {
        candies[i - 1] = max(candies[i] + 1, candies[i - 1]); // 这里要取最大值
      }
    }

    return std::accumulate(candies.begin(), candies.end(), 0);
  }
};