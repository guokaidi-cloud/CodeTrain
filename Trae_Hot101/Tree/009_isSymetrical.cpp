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
   * @param pRoot TreeNode类
   * @return bool布尔型
   */
  bool isSymmetrical(TreeNode *pRoot) {
    // method: 递归比较左右树
    if (!pRoot)
      return true;
    return twoTreeSymmetrical(pRoot->left, pRoot->right);
  }

  bool twoTreeSymmetrical(TreeNode *tree1, TreeNode *tree2) {
    if (tree1 == nullptr && tree2 == nullptr)
      return true;
    if (tree1 == nullptr && tree2 != nullptr)
      return false;
    if (tree2 == nullptr && tree1 != nullptr)
      return false;
    if (tree1->val != tree2->val)
      return false;
    return twoTreeSymmetrical(tree1->left, tree2->right) &&
           twoTreeSymmetrical(tree1->right, tree2->left);
  }
};