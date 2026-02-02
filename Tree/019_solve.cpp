#include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
  vector<int> solve(vector<int> &preOrder, vector<int> &inOrder) {
    vector<int> result;
    // 构建中序索引映射，快速查找
    unordered_map<int, int> inMap;
    for (int i = 0; i < inOrder.size(); ++i) {
      inMap[inOrder[i]] = i;
    }

    // 递归构建并获取右视图
    buildAndView(preOrder, 0, preOrder.size() - 1, inOrder, 0,
                 inOrder.size() - 1, inMap, result, 0);

    return result;
  }

private:
  void buildAndView(vector<int> &pre, int preStart, int preEnd, vector<int> &in,
                    int inStart, int inEnd, unordered_map<int, int> &inMap,
                    vector<int> &result, int depth) {
    if (preStart > preEnd || inStart > inEnd)
      return;

    // 当前根节点
    int rootVal = pre[preStart];

    // 如果是当前深度的第一个节点（最右侧），加入结果
    if (depth == result.size()) {
      result.push_back(rootVal);
    }

    // 在中序中找到根节点位置
    int rootIndex = inMap[rootVal];
    int leftSize = rootIndex - inStart;

    // 关键：先递归右子树，这样同一层会先访问到右边的节点
    // 右子树
    buildAndView(pre, preStart + leftSize + 1, preEnd, in, rootIndex + 1, inEnd,
                 inMap, result, depth + 1);

    // 左子树
    buildAndView(pre, preStart + 1, preStart + leftSize, in, inStart,
                 rootIndex - 1, inMap, result, depth + 1);
  }
};