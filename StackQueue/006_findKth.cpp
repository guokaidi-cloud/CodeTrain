#include <vector>
class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   *
   * @param a int整型vector
   * @param n int整型
   * @param K int整型
   * @return int整型
   */
  int findKth(vector<int> &a, int n, int K) {
    // write code here
    // method: 每次快排可以确定一个数的排序位置
    return quick_sort_find_k(a, 0, n - 1, K);
  }

  int quick_sort_find_k(vector<int> &a, int begin, int end, int k) {
    if (begin >= end)
      return a[begin];
    int pivot_index = partition(a, begin, end);
    if (pivot_index == a.size() - k) {
      return a[pivot_index];
    } else if (pivot_index > a.size() - k) {
      return quick_sort_find_k(a, begin, pivot_index - 1, k);
    } else {
      return quick_sort_find_k(a, pivot_index + 1, end, k);
    }
  }

  int partition(vector<int> &a, int begin, int end) {
    int pivot = a[begin]; // 直接取begin为轴值

    int l = begin, r = end;
    // 写一个标准快排
    while (l < r) {
      while (l < r && a[r] >= pivot) {
        --r;
      }
      while (l < r && a[l] <= pivot) {
        ++l;
      }
      if (l < r)
        swap(a[l], a[r]);
    }
    swap(a[l], a[begin]);
    return l;
  }
};