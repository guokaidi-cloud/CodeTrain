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
   * @param head1 ListNode类
   * @param head2 ListNode类
   * @return ListNode类
   */
  ListNode *addInList(ListNode *head1, ListNode *head2) {
    // write code here
    auto newhead1 = reverList(head1);
    auto newhead2 = reverList(head2);
    auto l1 = newhead1, l2 = newhead2;

    auto dummy = new ListNode(-1);
    auto cur = dummy;

    int count = 0;
    while (l1 && l2) {
      cur->next = new ListNode((count + l1->val + l2->val) % 10);
      count = (count + l1->val + l2->val) / 10;
      cur = cur->next;
      l1 = l1->next;
      l2 = l2->next;
    }

    while (l1) {
      cur->next = new ListNode((count + l1->val) % 10);
      count = (count + l1->val) / 10;
      cur = cur->next;
      l1 = l1->next;
    }

    while (l2) {
      cur->next = new ListNode((count + l2->val) % 10);
      count = (count + l2->val) / 10;
      cur = cur->next;
      l2 = l2->next;
    }

    if (count) {
      cur->next = new ListNode(1);
    }

    auto ret = dummy->next;
    delete dummy;
    return reverList(ret);
  }

  ListNode *reverList(ListNode *head) {
    auto dummy = new ListNode(-1);
    // 头插法
    while (head) {
      auto tmp = head->next;
      head->next = dummy->next;
      dummy->next = head;
      head = tmp; // 这里需要小心，不能写head = head->next
    }
    auto ret = dummy->next;
    delete dummy;
    return ret;
  }
};