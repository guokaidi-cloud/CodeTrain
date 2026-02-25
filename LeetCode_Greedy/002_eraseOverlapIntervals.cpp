class Solution {
public:
  int eraseOverlapIntervals(vector<vector<int>> &intervals) {
    std::sort(
        intervals.begin(), intervals.end(),
        [](const vector<int> &a, const vector<int> &b) { return a[1] < b[1]; });

    int min_no_overlay = 1;
    int right = intervals[0][1];
    for (int i = 1; i < intervals.size(); ++i) {
      if (intervals[i][0] >= right) {
        right = intervals[i][1];
        min_no_overlay++;
      }
    }
    return intervals.size() - min_no_overlay;
  }
};