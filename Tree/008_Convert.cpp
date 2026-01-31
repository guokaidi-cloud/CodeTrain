/*
struct TreeNode {
        int val;
        struct TreeNode *left;
        struct TreeNode *right;
        TreeNode(int x) :
                        val(x), left(NULL), right(NULL) {
        }
};*/
class Solution {
public:
  TreeNode *Convert(TreeNode *pRootOfTree) {
    // method: 递归，中序遍历,但是要先移动到最左边
    // complexity: 时间O(n), 空间O(logn) - O(n)
    if (!pRootOfTree)
      return pRootOfTree;
    TreeNode *p = pRootOfTree;
    while (p->left) {
      p = p->left;
    }
    in_order(pRootOfTree); // 这里要小心是从root开始的
    return p;
  }

private:
  void in_order(TreeNode *root) {
    if (!root)
      return;
    in_order(root->left);
    // 将root和pre_node串起来
    root->left = pre_node;
    if (pre_node) {
      pre_node->right = root;
    }
    pre_node = root;
    in_order(root->right);
  }
  TreeNode *pre_node{nullptr};
};