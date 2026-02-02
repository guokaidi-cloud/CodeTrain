class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   *
   * @param num int整型vector
   * @param size int整型
   * @return int整型vector
   */
  vector<int> maxInWindows(vector<int> &num, int size) {
    // write code here
    // merthod: 单调队列
    std::vector<int> ret;
    if (num.size() < size || size == 0)
      return ret;

    std::deque<int> dq;

    for (int i = 0; i < size; ++i) {
      // 维护单调队列
      while (!dq.empty() && num[dq.back()] < num[i]) {
        dq.pop_back();
      }
      if (dq.size() < size)
        dq.push_back(i);
    }
    ret.push_back(num[dq.front()]);

    for (int i = size; i < num.size(); ++i) {
      // 需要考虑长度的单调队列
      if (!dq.empty() && dq.front() <= i - size) {
        dq.pop_front();
      }
      // 维护单调队列
      while (!dq.empty() && num[dq.back()] < num[i]) {
        dq.pop_back();
      }
      dq.push_back(i);

      ret.push_back(num[dq.front()]);
    }
    return ret;
  }
};