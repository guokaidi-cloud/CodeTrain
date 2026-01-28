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
   * @param n int整型
   * @return ListNode类
   */
  ListNode *removeNthFromEnd(ListNode *head, int n) {
    // write code here
    ListNode *dummy = new ListNode(-1);
    dummy->next = head;
    auto tail = dummy;
    while (n--) {
      tail = tail->next;
    }

    auto pre = dummy;
    while (tail->next) {
      pre = pre->next;
      tail = tail->next;
    }

    // 删除倒数第n个节点
    auto tmp = pre->next;
    pre->next = tmp->next;
    delete tmp;

    auto ret = dummy->next;
    delete dummy;
    return ret;
  }
};