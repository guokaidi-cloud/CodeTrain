/**
 * struct TreeNode {
 *	int val;
 *	struct TreeNode *left;
 *	struct TreeNode *right;
 *	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 * };
 */
class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   *
   * @param t1 TreeNode类
   * @param t2 TreeNode类
   * @return TreeNode类
   */
  TreeNode *mergeTrees(TreeNode *t1, TreeNode *t2) {
    // write code here
    // method: 递归合并
    if (!t1)
      return t2;
    if (!t2)
      return t1;
    TreeNode *head = new TreeNode(t1->val + t2->val);
    head->left = mergeTrees(t1->left, t2->left);
    head->right = mergeTrees(t1->right, t2->right);
    return head;
  }
};
