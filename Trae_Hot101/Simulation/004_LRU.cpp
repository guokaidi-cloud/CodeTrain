#include <list>
#include <unordered_map>
class Solution {

private:
  int capacity_;
  // 双向链表：存储(key, value)，表头是最近使用，表尾是最久未使用
  std::list<std::pair<int, int>> cache_list_;
  // 链表的map，用于快速定位
  std::unordered_map<int, std::list<std::pair<int, int>>::iterator> cache_map_;

public:
  Solution(int capacity) {
    // write code here
    this->capacity_ = capacity;
  }

  int get(int key) {
    // write code here
    auto it = cache_map_.find(key);
    if (it == cache_map_.end()) {
      return -1;
    }
    // 这个操作很nb,就是把节点移动到头部
    cache_list_.splice(cache_list_.begin(), cache_list_, it->second);

    return it->second->second;
  }

  void set(int key, int value) {
    // write code here
    // 如果有的话就改一下
    auto it = cache_map_.find(key);
    if (it != cache_map_.end()) {
      it->second->second = value;
      cache_list_.splice(cache_list_.begin(), cache_list_, it->second);
      return;
    }
    // 如果满了就删除尾巴
    if (cache_list_.size() >= capacity_) {
      int back_key = cache_list_.back().first;
      cache_list_.pop_back();
      cache_map_.erase(back_key);
    }
    // 如果没有就新建一个
    cache_list_.push_front({key, value});
    cache_map_[key] = cache_list_.begin();
    return;
  }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* solution = new Solution(capacity);
 * int output = solution->get(key);
 * solution->set(key,value);
 */