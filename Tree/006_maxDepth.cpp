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
   * @return int整型
   */
  int maxDepth(TreeNode *root) {
    // write code here
    // method: 递归求深度
    // complexity: 时间O(n)，空间 树深 O(logn) - O(n)

    if (!root)
      return 0;
    return max(maxDepth(root->left), maxDepth(root->right)) + 1;
  }
};