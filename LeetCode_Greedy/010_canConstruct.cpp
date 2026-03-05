class Solution {
public:
  bool canConstruct(string s, int k) {
    // 如果没有奇数次 count == 0
    // 如果k <= s.size() 则一定成立;
    // 如果有奇数次 count > 0
    // 如果 count <= k <= s.size() 就成立
    int table[26] = {0};
    int l = s.size();
    for (int i = 0; i < l; ++i) {
      ++table[s[i] - 'a'];
    }

    int count = 0;
    for (int i = 0; i < 26; ++i) {
      count += table[i] & 1;
    }
    return count <= k && k <= l;
  }
};