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
   * @param root TreeNode类
   * @param p int整型
   * @param q int整型
   * @return int整型
   */
  int lowestCommonAncestor(TreeNode *root, int p, int q) {
    // write code here
    if (root->val >= p && root->val <= q)
      return root->val;
    if (root->val <= p && root->val >= q)
      return root->val;
    if (root->val > p && root->val > q) {
      return lowestCommonAncestor(root->left, p, q);
    } else {
      return lowestCommonAncestor(root->right, p, q);
    }
  }
};