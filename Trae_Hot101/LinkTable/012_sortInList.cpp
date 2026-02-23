// /**
//  * struct ListNode {
//  *	int val;
//  *	struct ListNode *next;
//  *	ListNode(int x) : val(x), next(nullptr) {}
//  * };
//  */
// class Solution {
// public:
//     /**
//      * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
//      *
//      *
//      * @param head ListNode类 the head node
//      * @return ListNode类
//      */
//     ListNode* sortInList(ListNode* head) {
//         // write code here

//         // 这种是可以交换节点数值的，可以选择快排
//         //
//         如果是不允许交换节点数值的，只能交换节点的，可以选择插入排序、冒泡排序、简单选择排序(选择一个最大的插入放到头部)

//         quick_sort(head, nullptr);
//         return head;
//     }

//     void quick_sort(ListNode* head, ListNode* tail){
//         // 递归终止：区间为空或只有一个元素
//         if(head == tail || head->next == tail) return;
//         auto mid = pivot(head, tail);
//         quick_sort(head, mid);
//         quick_sort(mid->next, tail);
//     }

//     ListNode* pivot(ListNode* head, ListNode* tail){
//         int val = head->val; // 取head的值作为轴值
//         ListNode* p = head;
//         ListNode* q = head->next;
//         while(q != tail){
//             if(q->val < val){
//                 p = p->next;
//                 if(p != q) swap(q->val,p->val);
//             }
//             q = q->next;
//         }
//         swap(p->val, head->val);
//         return p;
//     }
// };

// 快排容易在已经基本上排好顺序的时候，时间复杂度接近O(n^2)，空间复杂度
// 平均O(logn)，最差O(n) 可以使用归并排序，归并排序的时间复杂度是O(nlogn),
// 空间复杂度 O(logn)

class Solution {
public:
  ListNode *sortInList(ListNode *head) {
    if (!head || !head->next)
      return head;
    return merge_sort(head);
  }

  ListNode *merge_sort(ListNode *head) {
    if (!head || !head->next)
      return head;

    // 需要非常注意的是这边查找中点的方式里面，fast初始位置是head->next !!!!
    auto slow = head, fast = head->next;
    while (fast && fast->next) {
      slow = slow->next;
      fast = fast->next->next;
    }
    // 分割链表
    auto mid = slow->next;
    slow->next = nullptr;

    auto left = merge_sort(head);
    auto right = merge_sort(mid);

    return merge_list(left, right);
  }

  // 合并两个有序链表
  ListNode *merge_list(ListNode *left, ListNode *right) {
    if (!left)
      return right;
    if (!right)
      return left;

    auto dummy = new ListNode(-1);
    auto cur = dummy;
    auto l1 = left, l2 = right;

    while (l1 && l2) {
      if (l1->val < l2->val) {
        cur->next = l1;
        cur = cur->next;
        l1 = l1->next;
      } else {
        cur->next = l2;
        cur = cur->next;
        l2 = l2->next;
      }
    }

    cur->next = l1 ? l1 : l2;
    auto ret = dummy->next;
    delete dummy;
    return ret;
  }
};