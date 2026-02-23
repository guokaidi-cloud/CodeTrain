/**
 * struct TreeNode {
 *  int val;
 *  struct TreeNode *left;
 *  struct TreeNode *right;
 *  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 * };
 */
class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   *
   * @param pRoot TreeNode类
   * @return int整型vector<vector<>>
   */
  vector<vector<int>> Print(TreeNode *pRoot) {
    vector<vector<int>> ret;
    if (!pRoot)
      return ret;
    queue<TreeNode *> queue;
    queue.emplace(pRoot);
    int layer_index = 0;

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
      if ((layer_index++) % 2) { // 不能使用/
        std::reverse(layer_ret.begin(), layer_ret.end());
      }
      ret.emplace_back(std::move(layer_ret));
    }
    return ret;
  }
};