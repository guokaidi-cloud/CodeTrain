
/*
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
    }
};
*/
class Solution {
public:
  ListNode *EntryNodeOfLoop(ListNode *pHead) {
    ListNode *slow = pHead, *fast = pHead;
    // 检测环
    do {
      // 先检查是否能继续移动
      if (!fast || !fast->next)
        return nullptr;

      slow = slow->next;
      fast = fast->next->next;
    } while (slow != fast);

    ListNode *three = pHead;
    while (three != slow) {
      three = three->next;
      slow = slow->next;
    }
    return three;
  }
};