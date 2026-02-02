class Solution {
private:
  TreeNode *build(vector<int> &pre, int preStart, int preEnd, vector<int> &vin,
                  int vinStart, int vinEnd) {
    if (preStart > preEnd || vinStart > vinEnd)
      return nullptr;

    // 创建根节点
    TreeNode *root = new TreeNode(pre[preStart]);

    // 在中序序列中找到根节点的位置
    int rootIndex = vinStart;
    for (; rootIndex <= vinEnd; ++rootIndex) {
      if (vin[rootIndex] == pre[preStart])
        break;
    }

    // 计算左子树大小
    int leftSize = rootIndex - vinStart;

    // 递归构建左右子树
    root->left = build(pre, preStart + 1, preStart + leftSize, vin, vinStart,
                       rootIndex - 1);
    root->right =
        build(pre, preStart + leftSize + 1, preEnd, vin, rootIndex + 1, vinEnd);

    return root;
  }

public:
  TreeNode *reConstructBinaryTree(vector<int> &preOrder,
                                  vector<int> &vinOrder) {
    if (preOrder.empty() || vinOrder.empty() ||
        preOrder.size() != vinOrder.size()) {
      return nullptr;
    }
    return build(preOrder, 0, preOrder.size() - 1, vinOrder, 0,
                 vinOrder.size() - 1);
  }
};