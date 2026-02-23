/**
 * struct TreeNode {
 *	int val;
 *	struct TreeNode *left;
 *	struct TreeNode *right;
 *	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 * };
 */
// #include <vector>
// class Solution {
// public:
//     /**
//      * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
//      *
//      *
//      * @param root TreeNode类
//      * @return int整型vector
//      */
//     vector<int> postorderTraversal(TreeNode* root) {
//         // write code here
//         // method: 递归
//         // complexity: 时间 O(n), 空间 O(n)
//         vector<int> ret;
//         post_order(ret, root);
//         return ret;
//     }

//     void post_order(vector<int>& ret, TreeNode* root){
//         if(!root) return;
//         post_order(ret, root->left);
//         post_order(ret, root->right);
//         ret.push_back(root->val);
//     }
// };

#include <vector>
class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   *
   * @param root TreeNode类
   * @return int整型vector
   */
  vector<int> postorderTraversal(TreeNode *root) {
    // write code here
    // method: 非递归栈
    // complexity: 时间 O(n), 空间 O(n)
    vector<int> ret;
    std::stack<TreeNode *> stack;
    TreeNode *pre = nullptr;

    while (root != nullptr || !stack.empty()) {
      // 先到达最左边节点
      while (root != nullptr) {
        stack.emplace(root);
        root = root->left;
      }

      // 先到达判断该节点有没有右边节点
      auto top = stack.top();
      stack.pop();

      // 如果没有右边节点，或者右边节点已经访问过
      if (!top->right || top->right == pre) {
        ret.push_back(top->val);
        // 并且记录为访问过了
        pre = top;
      } else {
        stack.emplace(top);
        root = top->right;
      }
    }
    return ret;
  }
};
/**
 * struct TreeNode {
 *	int val;
 *	struct TreeNode *left;
 *	struct TreeNode *right;
 *	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 * };
 */
// #include <vector>
// class Solution {
// public:
//     /**
//      * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
//      *
//      *
//      * @param root TreeNode类
//      * @return int整型vector
//      */
//     vector<int> postorderTraversal(TreeNode* root) {
//         // write code here
//         // method: 递归
//         // complexity: 时间 O(n), 空间 O(n)
//         vector<int> ret;
//         post_order(ret, root);
//         return ret;
//     }

//     void post_order(vector<int>& ret, TreeNode* root){
//         if(!root) return;
//         post_order(ret, root->left);
//         post_order(ret, root->right);
//         ret.push_back(root->val);
//     }
// };

#include <vector>
class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   *
   * @param root TreeNode类
   * @return int整型vector
   */
  vector<int> postorderTraversal(TreeNode *root) {
    // write code here
    // method: 非递归栈
    // complexity: 时间 O(n), 空间 O(n)
    vector<int> ret;
    std::stack<TreeNode *> stack;
    TreeNode *pre = nullptr;

    while (root != nullptr || !stack.empty()) {
      // 先到达最左边节点
      while (root != nullptr) {
        stack.emplace(root);
        root = root->left;
      }

      // 先到达判断该节点有没有右边节点
      auto top = stack.top();
      stack.pop();

      // 如果没有右边节点，或者右边节点已经访问过
      if (!top->right || top->right == pre) {
        ret.push_back(top->val);
        // 并且记录为访问过了
        pre = top;
      } else {
        stack.emplace(top);
        root = top->right;
      }
    }
    return ret;
  }
};
