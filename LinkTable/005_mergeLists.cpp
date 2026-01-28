/**
 * struct ListNode {
 *	int val;
 *	struct ListNode *next;
 *	ListNode(int x) : val(x), next(nullptr) {}
 * };
 */
#include <queue>
class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   *
   * @param lists ListNode类vector
   * @return ListNode类
   */

  // 顺序合并方法
  // ListNode* mergeKLists(vector<ListNode*>& lists) {
  //     // write code here
  //     if(lists.empty()) return nullptr;
  //     ListNode* ret = lists[0];
  //     for(int i = 1; i < lists.size(); ++i){
  //         ret = merge(ret, lists[i]);
  //     }
  //     return ret;

  // }

  // ListNode* merge(ListNode* phead1, ListNode* phead2){
  //     ListNode* pre = new ListNode(-1), *cur = pre;
  //     ListNode* l1 = phead1, *l2 = phead2;

  //     while(l1 && l2){
  //         if(l1->val < l2->val){
  //             cur->next = l1;
  //             l1 = l1->next;
  //             cur = cur->next;
  //         }else{
  //             cur->next = l2;
  //             l2 = l2->next;
  //             cur = cur->next;
  //         }
  //     }

  //     if(l1){
  //         cur->next = l1;
  //     }

  //     if(l2){
  //         cur->next = l2;
  //     }

  //     return pre->next;
  // }

  // 小顶堆合并方法
  struct Compare {
    bool operator()(ListNode *a, ListNode *b) {
      return a->val > b->val; // 小顶堆
    }
  };

  ListNode *mergeKLists(vector<ListNode *> &lists) {
    // 堆，优先级队列方法

    std::priority_queue<ListNode *, std::vector<ListNode *>, Compare> q;
    ListNode *pre = new ListNode(-1);
    ListNode *cur = pre;

    for (auto l : lists) {
      if (l)
        q.push(l);
    }

    while (!q.empty()) {
      auto tmp = q.top();
      q.pop();

      cur->next = tmp;
      cur = cur->next;

      if (tmp->next) {
        q.push(tmp->next);
      }
    }

    return pre->next;
  }
};
