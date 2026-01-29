
// 这个题目有两种不错的方法，一种是左下角开始搜索，另外一种是双二分查找
// 当 m 和 n 都很大且接近时，O（log m * log n） 会比 O(m + n) 好

// class Solution {
//   public:
//     /**
//      * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
//      *
//      *
//      * @param target int整型
//      * @param array int整型vector<vector<>>
//      * @return bool布尔型
//      */
//     bool Find(int target, vector<vector<int> >& array) {
//         // method: double_binary_search
//         // complexity: 时间 O(log m * log n), 空间 O(log m + log n)
//         if (array.size() == 0) return false;
//         return double_binary_search(array, 0, array.size(), 0,
//         array[0].size(),
//                                     target); // 闭开区间，[x1,x2) [y1,y2)
//     }

//     bool double_binary_search(vector<vector<int> >& array, int x1, int x2,
//     int y1,
//                               int y2, int target) {
//         if(x1 == x2 || y1 == y2) return false;  // 必须要加递归的终止条件
//         int xmid = x1 + (x2 - x1) / 2;
//         int ymid = y1 + (y2 - y1) / 2;
//         int num = array[xmid][ymid];
//         if (num == target) {
//             return true;
//         } else if (num > target) { // 说明target在左上角，则过滤右下角区域
//             if (double_binary_search(array, x1, xmid, y1, y2, target)) return
//             true; if (double_binary_search(array, xmid, x2, y1, ymid,
//             target)) return true;
//         } else { // 说明target在右下角，则过滤左上角区域
//             if (double_binary_search(array, xmid + 1, x2, y1, y2, target))
//             return true; if (double_binary_search(array, x1, xmid + 1, ymid +
//             1, y2, target)) return true;
//         }
//         return false;
//     }
// };

class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   *
   * @param target int整型
   * @param array int整型vector<vector<>>
   * @return bool布尔型
   */
  bool Find(int target, vector<vector<int>> &array) {
    // method: 搜索
    // complexity: 时间 O(m + n), 空间 O(1)
    if (array.size() == 0)
      return false;
    int x = array.size() - 1, y = 0; //  行列不能弄混
    while (
        x >= 0 &&
        y < array[0].size()) { //  x >= 0 和 y < array[0].size()的条件不能弄混
      if (array[x][y] == target) {
        return true;
      } else if (array[x][y] > target) {
        --x;
      } else {
        ++y;
      }
    }
    return false;
  }
};