/**
 * struct ListNode {
 *	int val;
 *	struct ListNode *next;
 *	ListNode(int x) : val(x), next(nullptr) {}
 * };
 */
class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   *
   * @param head ListNode类
   * @param m int整型
   * @param n int整型
   * @return ListNode类
   */
  ListNode *reverseBetween(ListNode *head, int m, int n) {
    // write code here

    // 哨兵节点
    auto res = new ListNode(-1);
    res->next = head;
    // 双指针
    auto pre = res;
    auto cur = head;
    for (int i = 1; i < m; ++i) { // 这里需要小心，得从1开始
      pre = cur;
      cur = cur->next;
    }
    // 逆转区间，头插法
    for (int i = m; i < n; ++i) {
      auto tmp = cur->next;
      cur->next = tmp->next;
      tmp->next = pre->next;
      pre->next = tmp;
    }
    return res->next;
  }
};