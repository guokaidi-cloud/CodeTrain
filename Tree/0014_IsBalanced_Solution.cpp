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
  bool IsBalanced_Solution(TreeNode *pRoot) {
    // write code here
    // method: 自底向上
    // complexity: 时间 O(n), 空间O(logn) - O(n)
    if (!pRoot)
      return true;

    return getHeight(pRoot) != -1;
  }

  int getHeight(TreeNode *root) {
    // 自底向上获取高度，中间有几个return可以早一点skip
    if (!root)
      return 0;
    int l = getHeight(root->left);
    if (l == -1)
      return -1;
    int r = getHeight(root->right);
    if (r == -1)
      return -1;

    if (abs(l - r) > 1)
      return -1;
    return max(l, r) + 1;
  }
};