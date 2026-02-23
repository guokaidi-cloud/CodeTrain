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
  ListNode *oddEvenList(ListNode *head) {
    // method: 双指针法
    // complexity: 时间O(n),空间 O(1)

    if (!head || !head->next)
      return head;

    auto odd = head;        // 奇节点
    auto even = head->next; // 偶节点
    auto even_head = even;  // 保存偶节点的头

    while (even && even->next) {
      odd->next = even->next;
      odd = odd->next;
      even->next = odd->next;
      even = even->next;
    }
    odd->next = even_head;
    return head;
  }
};