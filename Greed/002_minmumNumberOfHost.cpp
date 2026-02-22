#include <exception>
class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   * 计算成功举办活动需要多少名主持人
   * @param n int整型 有n个活动
   * @param startEnd int整型vector<vector<>>
   * startEnd[i][0]用于表示第i个活动的开始时间，startEnd[i][1]表示第i个活动的结束时间
   * @return int整型
   */
  int minmumNumberOfHost(int n, vector<vector<int>> &startEnd) {
    // write code here
    // method:
    // 两个数组+双指针，贪心选择：优先安排开始最早的活动,优先处理结束最早的活动
    vector<int> starts(n);
    vector<int> ends(n);

    for (int i = 0; i < n; ++i) {
      starts[i] = startEnd[i][0];
      ends[i] = startEnd[i][1];
    }

    // 排序
    sort(starts.begin(), starts.end());
    sort(ends.begin(), ends.end());

    // 双指针
    int i = 0, j = 0;      // 分别是开始和结束数组的
    int current_hosts = 0; // 当前需要多少个主持人
    int min_hosts = 0;     // 最小的主持人
    while (i < n && j < n) {
      if (starts[i] < ends[j]) { // 有重叠，需要安排一个新的主持人
        ++current_hosts;
        min_hosts = max(min_hosts, current_hosts);
        ++i;
      } else { // 没有重叠，之前有一个主持人结束了
        --current_hosts;
        ++j;
      }
    }
    return min_hosts;
  }
};