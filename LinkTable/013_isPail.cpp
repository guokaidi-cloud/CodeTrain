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
   * @param head ListNode类 the head
   * @return bool布尔型
   */
  bool isPail(ListNode *head) {
    // method: 反转后半部分链表，随后开始比较
    // complexity: 时间复杂度O(n),空间复杂度O(1)
    if (!head || !head->next)
      return true;
    auto slow = head, fast = head;
    while (fast && fast->next) {
      slow = slow->next;
      fast = fast->next->next;
    }
    // {1,2,3}  slow -> 2, fast -> 3
    // {1,2,3,4} slow -> 2, fast -> 3
    // 反转 slow->next即可

    auto part2 = reverse_list(slow->next);
    while (part2) {
      if (part2->val != head->val)
        return false;
      head = head->next;
      part2 = part2->next;
    }

    return true;
  }

  ListNode *reverse_list(ListNode *head) {
    if (!head || !head->next) {
      return head;
    }

    auto dummy = new ListNode(-1);
    // 头插法
    while (head) {
      auto tmp = head->next;
      head->next = dummy->next;
      dummy->next = head;
      head = tmp;
    }
    auto ret = dummy->next;
    delete dummy;
    return ret;
  }
};