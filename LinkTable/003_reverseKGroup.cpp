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
   * @param head ListNode类
   * @param k int整型
   * @return ListNode类
   */
  ListNode *reverseKGroup(ListNode *head, int k) {
    // write code here
    ListNode *tail = head;
    // 遍历k次到尾部
    for (int i = 0; i < k; ++i) {
      if (tail == nullptr) {
        // 如果不足k则直接返回，不翻转
        return head;
      }
      tail = tail->next;
    }
    // 翻转时需要的前序和当前节点
    ListNode *pre = nullptr;
    ListNode *cur = head;
    while (cur != tail) {
      ListNode *tmp = cur->next;
      cur->next = pre;
      pre = cur;
      cur = tmp;
    }
    head->next = reverseKGroup(tail, k);
    return pre;
  }
};