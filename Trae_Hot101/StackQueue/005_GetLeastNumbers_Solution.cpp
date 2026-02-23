#include <queue>
class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   *
   * @param input int整型vector
   * @param k int整型
   * @return int整型vector
   */
  vector<int> GetLeastNumbers_Solution(vector<int> &input, int k) {
    // write code here
    // method: 单调队列

    if (k == 0)
      return std::vector<int>();
    std::priority_queue<int> pq; // 默认是大顶堆，堆顶是最大值

    for (int i = 0; i < k; ++i) {
      pq.push(input[i]);
    }

    for (int i = k; i < input.size(); ++i) {
      if (input[i] < pq.top()) {
        pq.pop();
        pq.push(input[i]);
      }
    }

    std::vector<int> ret;
    while (!pq.empty()) {
      ret.push_back(pq.top());
      pq.pop();
    }

    return ret;
  }
};