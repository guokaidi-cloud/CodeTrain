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
  bool isCompleteTree(TreeNode *root) {
    // write code here
    // method: 层序遍历,queue
    if (!root)
      return true;
    queue<TreeNode *> queue;
    queue.emplace(root);

    bool nullptr_flag = false;
    while (!queue.empty()) {
      int size = queue.size();
      while (size--) {
        // 如果一层之中有nullptr了，则再次出现不是nullptr的节点则肯定不是完全二叉树
        auto node = queue.front();
        queue.pop();
        if (node == nullptr) {
          nullptr_flag = true;
        } else {
          if (nullptr_flag)
            return false;
          queue.emplace(node->left);
          queue.emplace(node->right);
        }
      }
    }
    return true;
  }
};