class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   *
   * @param numbers int整型vector
   * @param target int整型
   * @return int整型vector
   */
  vector<int> twoSum(vector<int> &numbers, int target) {
    // write code here
    // method: hash表

    std::unordered_map<int, int> hash;
    for (int i = 0; i < numbers.size(); ++i) {
      if (hash.find(target - numbers[i]) != hash.end()) {
        return {hash[target - numbers[i]] + 1, i + 1};
      } else {
        hash[numbers[i]] = i;
      }
    }
    return {};
  }
};