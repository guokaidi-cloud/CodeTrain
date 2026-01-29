// 整个代码需要对齐开闭区间

class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   *
   * @param nums int整型vector
   * @return int整型
   */
  int InversePairs(vector<int> &nums) {
    // method: 归并排序，当left中有大于right时候触发
    // complexity: 时间 O(n log n) 空间 O(n)

    if (nums.size() < 2)
      return 0;
    vector<int> tmp(nums.size());
    return merge_sort_and_count(nums, tmp, 0, nums.size() - 1);
  }

private:
  int merge_sort_and_count(vector<int> &nums, vector<int> &tmp, int left,
                           int right) { // 返回count
    if (left >= right)
      return 0;
    int mid = left + (right - left) / 2;

    int count = 0;
    count = (count + merge_sort_and_count(nums, tmp, left, mid)) %
            1000000007; // 取模需要非常谨慎
    count =
        (count + merge_sort_and_count(nums, tmp, mid + 1, right)) % 1000000007;
    count = (count + merge_count(nums, tmp, left, mid, right)) % 1000000007;

    return count;
  }

  int merge_count(vector<int> &nums, vector<int> &tmp, int left, int mid,
                  int right) {
    for (int i = left; i <= right; ++i) { // 这里的 i <= right需要非常注意
      tmp[i] = nums[i];
    }

    int i = left;    // 左半部分开始
    int j = mid + 1; // 右半部分开始
    int k = left;    // 合并数组开始

    int count = 0; // 计数

    while (i <= mid && j <= right) {
      if (tmp[i] <= tmp[j]) {
        nums[k++] = tmp[i++];
      } else {
        count += mid - i + 1;
        count %= 1000000007;
        nums[k++] = tmp[j++];
      }
    }

    while (i <= mid) {
      nums[k++] = tmp[i++];
    }

    while (j <= right) {
      nums[k++] = tmp[j++];
    }

    return count;
  }
};