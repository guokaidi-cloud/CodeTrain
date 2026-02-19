/**
 * struct Interval {
 *	int start;
 *	int end;
 *	Interval(int s, int e) : start(start), end(e) {}
 * };
 */
class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   *
   * @param intervals Interval类vector
   * @return Interval类vector
   */
  vector<Interval> merge(vector<Interval> &intervals) {
    // write code here
    if (intervals.empty())
      return intervals;
    std::sort(
        intervals.begin(), intervals.end(),
        [](const Interval &a, const Interval &b) { return a.start < b.start; });

    // 结果数组，初始化加入第一个区间
    vector<Interval> res;
    res.push_back(intervals[0]);

    // 遍历剩余区间，仅与结果数组最后一个区间对比
    for (size_t i = 1; i < intervals.size(); ++i) {
      Interval &last = res.back(); // 引用，避免拷贝
      if (intervals[i].start <= last.end) {
        // 合并：更新最后一个区间的end
        last.end = max(last.end, intervals[i].end);
      } else {
        // 无重叠，加入结果
        res.push_back(intervals[i]);
      }
    }

    return res;
  }
};