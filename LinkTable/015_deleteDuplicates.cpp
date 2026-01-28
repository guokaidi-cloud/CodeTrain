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
    // complexity: 时间 O（n），空间 O(1)

    if (!head || !head->next)
      return head;

    auto cur = head;
    while (cur->next) {
      if (cur->val == cur->next->val) {
        auto tmp = cur->next;
        cur->next = tmp->next;
        delete tmp;
      } else {
        cur = cur->next;
      }
    }
    return head;
  }
};