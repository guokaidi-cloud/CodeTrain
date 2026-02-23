class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   *
   * @param numbers int整型vector
   * @return int整型
   */

  int MoreThanHalfNum_Solution(vector<int> &numbers) {
    // write code here
    // method: 排序
    // complexity: 时间 O(nlogn), 空间看std::sort实际上用了什么 插排O(1),快排
    // O(logn) - O(n), 堆排 稳定O(logn)

    std::sort(numbers.begin(), numbers.end());
    return numbers[numbers.size() / 2];
  }

  // int MoreThanHalfNum_Solution(vector<int>& numbers) {
  //     // write code here
  //     // method: 候选法（摩尔投票法）
  //     // complexity: 时间 O(n), 空间 O(1)

  //     int candidate = -1;
  //     int count = 0;
  //     for(int i = 0; i < numbers.size(); ++i){
  //         if(count == 0){
  //             candidate = numbers[i];
  //             ++count;
  //         }else{
  //             if(candidate == numbers[i]) ++count;
  //             else --count;
  //         }
  //     }

  //     count = 0;
  //     for(int i = 0; i < numbers.size(); ++i){
  //         if(candidate == numbers[i]){
  //             ++count;
  //         }
  //     }

  //     return count > numbers.size() /2 ? candidate : -1;
  // }
};