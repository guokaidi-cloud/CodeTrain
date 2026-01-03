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
  // ListNode* ReverseList(ListNode* head) {
  //     ListNode* pre = nullptr;
  //     ListNode* cur = head;

  //     while(cur){
  //         auto tmp = cur->next;
  //         cur->next = pre;
  //         pre = cur;
  //         cur = tmp;
  //     }
  //     return pre;
  // }
  // ListNode* ReverseList(ListNode* head) {
  //     if(head->next == nullptr || head->next == nullptr){
  //         return head;
  //     }
  //     auto tmp = ReverseList(head->next);
  //     head->next->next = head;
  //     head->next = nullptr;
  //     return tmp;
  // }
  ListNode *ReverseList(ListNode *head) {
    auto dummy = new ListNode(-1);
    dummy->next = head;

    auto pre = dummy;
    auto cur = head;

    // 头插法
    while (cur && cur->next) {
      auto tmp = cur->next;
      cur->next = tmp->next;
      tmp->next = pre->next;
      pre->next = tmp;
    }
    return dummy->next;
  }
};
