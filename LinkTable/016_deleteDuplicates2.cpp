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
   * @return ListNode类
   */
  ListNode *deleteDuplicates(ListNode *head) {
    // method: 单指针
    // complecity: 时间O(n),空间 O(n)

    auto dummy = new ListNode(-1);
    dummy->next = head;

    auto pre = dummy;
    while (pre->next && pre->next->next) {
      if (pre->next->val == pre->next->next->val) {
        int dup_value = pre->next->val;

        auto cur = pre->next;
        while (cur && cur->val == dup_value) {
          auto tmp = cur;
          cur = cur->next;
          delete tmp;
        }
        pre->next = cur;
      } else {
        pre = pre->next;
      }
    }

    auto ret = dummy->next;
    delete dummy;
    return ret;
  }
};