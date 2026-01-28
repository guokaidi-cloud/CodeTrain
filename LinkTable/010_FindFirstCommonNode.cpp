/*
struct ListNode {
        int val;
        struct ListNode *next;
        ListNode(int x) :
                        val(x), next(NULL) {
        }
};*/
class Solution {
public:
  ListNode *FindFirstCommonNode(ListNode *pHead1, ListNode *pHead2) {
    ListNode *l1 = pHead1;
    ListNode *l2 = pHead2;
    int len1 = 0, len2 = 0;
    while (l1) {
      l1 = l1->next;
      ++len1;
    }
    while (l2) {
      l2 = l2->next;
      ++len2;
    }

    // 长的链表先走diff步
    auto cur1 = pHead1, cur2 = pHead2;
    if (len1 > len2) {
      auto diff = len1 - len2;
      while (diff--) {
        cur1 = cur1->next;
      }
    } else if (len1 < len2) {
      auto diff = len2 - len1;
      while (diff--) {
        cur2 = cur2->next;
      }
    }

    // 同时走，直到找到公共节点
    while (cur1 != cur2) {
      cur1 = cur1->next;
      cur2 = cur2->next;
    }
    return cur1;
  }
};