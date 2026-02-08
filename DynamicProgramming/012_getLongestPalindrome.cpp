// 有 两种方法可以做，一种是中心扩散法，另外一种是动态规划

class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   *
   * @param A string字符串
   * @return int整型
   */
  int getLongestPalindrome(string A) {
    // write code here
    // method: 中心扩散法
    // complexity: 时间 O(n), 空间 O(1)
    int ret = 1;
    for (int i = 0; i < A.size() - 1; ++i) {
      int len1 = expand(A, i, i);
      int len2 = expand(A, i, i + 1);
      int len = max(len1, len2);

      if (len > ret) {
        ret = len;
      }
    }

    return ret;
  }

  int expand(string &A, int left, int right) {
    // 奇数和偶数都一样
    while (left >= 0 && right < A.size() && A[left] == A[right]) {
      --left;
      ++right;
    }

    return right - left - 1;
  }
};