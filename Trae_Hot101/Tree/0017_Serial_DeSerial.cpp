/*
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {
    }
};
*/
// class Solution {
// public:
//     char* Serialize(TreeNode *root) {
//     }
//     TreeNode* Deserialize(char *str) {
//     }
// };

/*
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
*/

class Solution {
public:
  // 序列化二叉树 - 层序遍历实现
  char *Serialize(TreeNode *root) {
    // 处理空树
    if (!root) {
      char *res = new char[3];
      strcpy(res, "#,");
      return res;
    }

    string data;
    queue<TreeNode *> q;
    q.push(root);

    while (!q.empty()) {
      TreeNode *node = q.front();
      q.pop();

      if (node) {
        // 节点非空：记录值并将子节点入队（包括空子节点）
        data += to_string(node->val) + ",";
        q.push(node->left);
        q.push(node->right);
      } else {
        // 节点为空：记录空标记，不继续入队子节点
        data += "#,";
      }
    }

    // 分配内存并返回
    char *res = new char[data.length() + 1];
    strcpy(res, data.c_str());
    return res;
  }

  // 反序列化二叉树
  TreeNode *Deserialize(char *str) {
    if (!str || str[0] == '\0') {
      return nullptr;
    }

    // 分割字符串
    string data(str);
    vector<string> nodes;
    splitString(data, nodes, ',');

    if (nodes.empty() || nodes[0] == "#") {
      return nullptr;
    }

    // 创建根节点
    TreeNode *root = new TreeNode(stoi(nodes[0]));
    queue<TreeNode *> q;
    q.push(root);

    int index = 1; // 当前处理的节点索引
    int n = nodes.size();

    while (!q.empty() && index < n) {
      TreeNode *parent = q.front();
      q.pop();

      // 处理左子节点
      if (index < n && nodes[index] != "#") {
        parent->left = new TreeNode(stoi(nodes[index]));
        q.push(parent->left);
      }
      index++;

      // 处理右子节点
      if (index < n && nodes[index] != "#") {
        parent->right = new TreeNode(stoi(nodes[index]));
        q.push(parent->right);
      }
      index++;
    }

    return root;
  }

private:
  // 辅助函数：分割字符串
  void splitString(const string &s, vector<string> &tokens, char delim) {
    tokens.clear();
    stringstream ss(s);
    string token;

    while (getline(ss, token, delim)) {
      if (!token.empty()) {
        tokens.push_back(token);
      }
    }
  }
};