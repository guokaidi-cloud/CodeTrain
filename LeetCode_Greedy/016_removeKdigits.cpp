class Solution {
public:
  string removeKdigits(string num, int k) {
    // 单调栈：为了高位可以更小，如果遇到比栈顶大的数就删除
    std::vector<char> stk;
    for (auto c : num) {
      while (k > 0 && !stk.empty() && stk.back() > c) {
        stk.pop_back();
        --k;
      }
      stk.push_back(c);
    }

    // 把剩余的k用完
    while (k > 0 && !stk.empty()) {
      stk.pop_back();
      --k;
    }

    // 去除前导0
    int start = 0;
    while (start < stk.size() && stk[start] == '0')
      start++;

    // 如果没有数了
    if (start == stk.size())
      return "0";

    // 传入到ret
    std::string ret;
    for (int i = start; i < stk.size(); ++i) {
      ret.push_back(stk[i]);
    }
    return ret;
  }
};