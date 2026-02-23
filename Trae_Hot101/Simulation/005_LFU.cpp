#include <list> // 补充list头文件（原代码漏了）
#include <unordered_map>

using namespace std; // 工程中可按需调整，此处为简洁

class LFUCache {
private:
  int capacity_;     // 缓存最大容量K
  int min_freq_ = 1; // 当前最小访问频率

  // 核心节点：保存key/value/freq（记录访问次数）
  struct Node {
    int key;
    int value;
    int freq; // 被set/get调用的总次数
    Node(int k, int v, int f) : key(k), value(v), freq(f) {}
  };

  // 频率映射：freq ->
  // 对应频率的节点链表（同频率按"上次调用时间"排序，尾部是最早调用的）
  unordered_map<int, list<Node>> freq_list_;
  // 优化：仅存储迭代器，不再存freq（去掉冗余）
  unordered_map<int, list<Node>::iterator> key_iter_map_;

  // 辅助函数：移除最小频率链表的尾部节点（次数最少+上次调用最早）
  void remove_min_freq_node() {
    auto &min_list = freq_list_[min_freq_];
    int del_key = min_list.back().key; // 链表尾部是同频率中上次调用最早的
    // 先删索引，再删节点（避免迭代器失效）
    key_iter_map_.erase(del_key);
    min_list.pop_back();
    // 空链表直接删除，避免无效存储
    if (min_list.empty()) {
      freq_list_.erase(min_freq_);
    }
  }

public:
  // 构造函数：初始化缓存容量
  LFUCache(int capacity) { this->capacity_ = capacity; }

  // get操作：返回key对应value，不存在则返回-1；调用后访问次数+1
  int get(int key) {
    auto it = key_iter_map_.find(key);
    if (it == key_iter_map_.end()) {
      return -1; // key未出现/已被移除，返回-1
    }

    // 1. 获取原节点迭代器和旧频率（无拷贝）
    auto node_iter = it->second;
    int old_freq = node_iter->freq;
    int value = node_iter->value; // 仅记录返回值

    // 2. 核心：用splice将节点从旧频率链表移动到新频率链表头部
    int new_freq = old_freq + 1;
    // 2.1 移动节点（跨list移动，无拷贝）
    freq_list_[new_freq].splice(
        freq_list_[new_freq].begin(), // 插入到新链表头部
        freq_list_[old_freq],         // 源链表
        node_iter                     // 要移动的节点迭代器
    );
    // 2.2 更新节点的freq（移动后迭代器仍有效！）
    freq_list_[new_freq].begin()->freq = new_freq;
    // 2.3 更新索引表（指向新链表中的节点）
    key_iter_map_[key] = freq_list_[new_freq].begin();

    // 3. 清理旧频率链表（若为空则删除，并更新min_freq_）
    if (freq_list_[old_freq].empty()) {
      freq_list_.erase(old_freq);
      if (old_freq == min_freq_) {
        min_freq_ = new_freq;
      }
    }

    return value;
  }

  // set操作：插入/更新(key, value)；超容量时按LFU策略删除节点
  void set(int key, int value) {
    if (capacity_ == 0)
      return; // 容量为0时直接返回

    // 1. key已存在：更新value + 触发频率更新（复用get逻辑）
    auto it = key_iter_map_.find(key);
    if (it != key_iter_map_.end()) {
      auto node_iter = it->second;
      node_iter->value = value; // 直接更新value（无拷贝）
      this->get(key);           // 调用get更新频率和位置
      return;
    }

    // 2. 缓存满：删除最小频率的尾部节点
    if (key_iter_map_.size() >= capacity_) {
      remove_min_freq_node();
    }

    // 3. 新增节点：直接构造到频率1的链表头部（无拷贝）
    freq_list_[1].emplace_front(key, value, 1); // emplace直接构造，无拷贝
    // 4. 更新索引表
    key_iter_map_[key] = freq_list_[1].begin();
    // 5. 重置最小频率为1（新增节点频率必为1）
    min_freq_ = 1;
  }
};
class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   * lfu design
   * @param operators int整型vector<vector<>> ops
   * @param k int整型 the k
   * @return int整型vector
   */
  vector<int> LFU(vector<vector<int>> &operators, int k) {
    // write code here
    vector<int> ret;
    LFUCache lfu_cache(k);
    for (auto vec : operators) {
      if (vec[0] == 1) {
        lfu_cache.set(vec[1], vec[2]);
      } else {
        ret.push_back(lfu_cache.get(vec[1]));
      }
    }
    return ret;
  }
};