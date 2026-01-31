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
   * @return bool布尔型
   */
  bool isValidBST(TreeNode *root) {
    // write code
    // method: 中序遍历，如果pre一直小于cur则是BST树
    return in_order(root);
  }

  bool in_order(TreeNode *root) {
    if (!root)
      return true;
    bool l = in_order(root->left);
    if (pre && pre->val >= root->val)
      return false;
    pre = root;
    bool r = in_order(root->right);
    return l && r;
  }

private:
  TreeNode *pre{nullptr};
};