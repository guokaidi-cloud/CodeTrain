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
   * @return int整型vector<vector<>>
   */
  vector<vector<int>> levelOrder(TreeNode *root) {
    // write code here
    // method: queue
    // complexity: 时间O(n),空间O(n)
    vector<vector<int>> ret;
    if (!root)
      return ret;
    queue<TreeNode *> queue;
    queue.emplace(root);

    while (!queue.empty()) {
      int size = queue.size();
      vector<int> layer_ret;
      while (size--) {
        auto tmp = queue.front();
        queue.pop();
        layer_ret.push_back(tmp->val);
        if (tmp->left)
          queue.emplace(tmp->left);
        if (tmp->right)
          queue.emplace(tmp->right);
      }
      ret.emplace_back(std::move(layer_ret));
    }
    return ret;
  }
};