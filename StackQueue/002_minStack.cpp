class Solution {
public:
  void push(int value) {
    int min_value = value;
    if (!stack1.empty()) {
      min_value = std::min(min_value, stack2.top());
    }

    stack1.push(value);
    stack2.push(min_value);
  }
  void pop() {
    stack1.pop();
    stack2.pop();
  }
  int top() { return stack1.top(); }
  int min() { return stack2.top(); }

private:
  stack<int> stack1;
  stack<int> stack2;
};