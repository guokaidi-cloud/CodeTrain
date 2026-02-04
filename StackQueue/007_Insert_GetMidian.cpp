class Solution {
private:
  std::priority_queue<int> max_stack; // 偏小的一半数，最大的在堆顶
  std::priority_queue<int, std::vector<int>, std::greater<int>>
      min_stack; // 偏大的一半数，最小的在堆顶
public:
  void Insert(int num) {
    if (!max_stack.empty() && num < max_stack.top()) {
      max_stack.emplace(num);
    } else {
      min_stack.emplace(num);
    }

    // 保持两个堆平衡, max_stack.size() == min_stack()或 min_stack() + 1，即平衡
    if (max_stack.size() > min_stack.size() + 1) {
      min_stack.emplace(max_stack.top());
      max_stack.pop();
    } else if (max_stack.size() < min_stack.size()) {
      max_stack.emplace(min_stack.top());
      min_stack.pop();
    }
  }

  double GetMedian() {
    if (max_stack.size() == min_stack.size()) {
      return (double)(max_stack.top() + min_stack.top()) / 2.0;
    }

    return max_stack.top();
  }
};