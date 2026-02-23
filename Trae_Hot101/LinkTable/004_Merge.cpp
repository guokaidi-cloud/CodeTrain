/**
 * struct ListNode {
 *	int val;
 *	struct ListNode *next;
 *	ListNode(int x) : val(x), next(nullptr) {}
 * };
 */
#include <list>
class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   *
   * @param pHead1 ListNode类
   * @param pHead2 ListNode类
   * @return ListNode类
   */
  ListNode *Merge(ListNode *pHead1, ListNode *pHead2) {
    // write code here
    if (!pHead1 && !pHead2)
      return nullptr;
    ListNode *pre = new ListNode(-1);
    ListNode *cur = pre;
    ListNode *l1 = pHead1;
    ListNode *l2 = pHead2;
    while (l1 != nullptr && l2 != nullptr) {
      if (l1->val < l2->val) {
        cur->next = l1;
        l1 = l1->next;
        cur = cur->next;
      } else {
        cur->next = l2;
        l2 = l2->next;
        cur = cur->next;
      }
    }

    if (l1) {
      cur->next = l1;
    }

    if (l2) {
      cur->next = l2;
    }

    return pre->next;
  }
};