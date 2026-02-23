// 三种方法
// 一种是递归，比较简单
// 另外两种是非递归，使用辅助栈

/**
 * struct TreeNode {
 *  int val;
 *  struct TreeNode *left;
 *  struct TreeNode *right;
 *  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 * };
 */
// class Solution {
// public:
//     /**
//      * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
//      *
//      *
//      * @param root TreeNode类
//      * @return int整型vector
//      */

//     void pre_order(std::vector<int>& ret, TreeNode* root){
//         if(!root) return;
//         ret.push_back(root->val);
//         pre_order(ret, root->left);
//         pre_order(ret, root->right);
//     }

//     vector<int> preorderTraversal(TreeNode* root) {
//         // method: 递归
//         // complexity: 时间 O(n), 空间O(n)
//         vector<int> ret;
//         pre_order(ret, root);
//         return ret;
//     }
// };

// #include <asm-generic/errno.h>
// class Solution {
//   public:
//     /**
//      * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
//      *
//      *
//      * @param root TreeNode类
//      * @return int整型vector
//      */
//     vector<int> preorderTraversal(TreeNode* root) {
//         // method: 辅助栈，非递归
//         // complexity: 时间 O(n), 空间O(n)
//         std::vector<int> ret;
//         if (root == nullptr) return ret;
//         std::stack<TreeNode*> stack;
//         stack.emplace(root);

//         while (!stack.empty()) {
//             auto tmp = stack.top();
//             stack.pop();
//             ret.push_back(tmp->val);
//             // 因为这边是栈，所以先压右边的
//             if (tmp->right) stack.emplace(tmp->right);
//             if (tmp->left) stack.emplace(tmp->left);
//         }
//         return ret;
//     }
// };

// class Solution {
//   public:
//     /**
//      * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
//      *
//      *
//      * @param root TreeNode类
//      * @return int整型vector
//      */
//     vector<int> preorderTraversal(TreeNode* root) {
//         // method: 辅助栈，非递归
//         // complexity: 时间 O(n), 空间O(n)
//         std::vector<int> ret;
//         if (root == nullptr) return ret;
//         std::stack<TreeNode*> stack;
//         stack.emplace(root);

//         while (!stack.empty()) {
//             auto tmp = stack.top();
//             stack.pop();
//             ret.push_back(tmp->val);
//             // 因为这边是栈，所以先压右边的
//             if (tmp->right) stack.emplace(tmp->right);
//             if (tmp->left) stack.emplace(tmp->left);
//         }
//         return ret;
//     }
// };

class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   *
   * @param root TreeNode类
   * @return int整型vector
   */
  vector<int> preorderTraversal(TreeNode *root) {
    // method: 辅助栈，非递归
    // complexity: 时间 O(n), 空间O(n)
    std::vector<int> ret;
    std::stack<TreeNode *> stack;

    while (root != nullptr || !stack.empty()) {
      while (root != nullptr) {
        stack.emplace(root);
        ret.push_back(root->val);
        root = root->left;
      }
      auto top = stack.top();
      stack.pop();
      root = top->right;
    }

    return ret;
  }
};
