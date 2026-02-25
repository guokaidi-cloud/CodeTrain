class Solution {
public:
  bool lemonadeChange(vector<int> &bills) {
    int five_c = 0;
    int ten_c = 0;
    int twen_c = 0;

    for (auto bill : bills) {
      if (bill == 5) {
        five_c++;
      } else if (bill == 10) {
        if (five_c == 0)
          return false;
        five_c--;
        ten_c++;
      } else {
        if (ten_c >= 1 && five_c >= 1) {
          ten_c--;
          five_c--;
          twen_c++;
        } else if (five_c >= 3) {
          five_c -= 3;
          twen_c++;
        } else {
          return false;
        }
      }
    }

    return true;
  }
};