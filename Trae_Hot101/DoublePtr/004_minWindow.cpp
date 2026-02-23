#include <unordered_map>
class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   *
   * @param S string字符串
   * @param T string字符串
   * @return string字符串
   */

  string minWindow(string S, string T) {
    // write code here

    std::unordered_map<char, int> hash;
    for (auto &ch : T) { // 这里需要以++来进行初始化，因为有可能数字又重复的
      hash[ch]++;
    }

    int left = 0, right = 0;
    int count = T.size();  // 还需要匹配的字符总数（而非种类）
    int min_len = INT_MAX; // 最小窗口长度
    int start = 0;         // 最小窗口起始位置
    while (right < S.size()) {
      // 右指针右移: 找到一个T中字符就减少count
      if (hash[S[right]] > 0) {
        count--;
      }
      hash[S[right]]--; // 非T的字符会被减为负数，不影响count
      right++;

      // 当count=0（窗口包含所有T字符），尝试收缩左指针找最小窗口
      while (count == 0) {
        if (right - left < min_len) {
          min_len = right - left;
          start = left;
        }
        // 左指针右移：如果移出的是T中的字符，且刚好够数，需要恢复count
        if (hash[S[left]] == 0) {
          count++;
        }
        hash[S[left]]++;
        left++;
      }
    }
    return min_len == INT_MAX ? "" : S.substr(start, min_len);
  }
};