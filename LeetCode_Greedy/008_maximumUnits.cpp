class Solution {
public:
  int maximumUnits(vector<vector<int>> &boxTypes, int truckSize) {
    std::sort(boxTypes.begin(), boxTypes.end(),
              [](const vector<int> &left, const vector<int> &right) {
                return left[1] > right[1];
              });

    int max_sum = 0;
    for (const auto &vec : boxTypes) {
      if (vec[0] <= truckSize) {
        max_sum += vec[0] * vec[1];
        truckSize -= vec[0];
      } else {
        max_sum += truckSize * vec[1];
        break;
      }
    }
    return max_sum;
  }
};