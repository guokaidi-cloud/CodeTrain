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
   * @param o1 int整型
   * @param o2 int整型
   * @return int整型
   */
  int lowestCommonAncestor(TreeNode *root, int o1, int o2) {
    // write code here
    // 如果当前节点是 o1 或 o2，则返回该节点。
    // 如果左右子树递归结果都不为空，说明当前节点就是
    // LCA（因为o1和o2分居两侧）。
    // 如果只有一侧不为空，则将该侧结果向上传递（表示该子树包含目标节点之一）。
    // 如果都为空，返回空。

    if (!root)
      return -1;
    // 如果有一个就直接上传，哪怕看不到另外一个更底层的也没关系，可以一直到顶部去判断
    if (root->val == o1 || root->val == o2) {
      return root->val;
    }

    int l = lowestCommonAncestor(root->left, o1, o2);
    int r = lowestCommonAncestor(root->right, o1, o2);

    // 如果两个分别在左边和右边
    if (l != -1 && r != -1) {
      return root->val;
    }

    // 左边有一个或者右边有一个，就直接上传就行；
    // 如果没有这两个都是-1也没关系
    return l != -1 ? l : r;
  }
};