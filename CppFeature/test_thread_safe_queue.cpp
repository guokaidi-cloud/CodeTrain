/**
 * ThreadSafeQueue 测试程序
 */

#include "ThreadSafeQueue.hpp"
#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>

int main() {
  std::cout << "========================================" << std::endl;
  std::cout << "      ThreadSafeQueue 测试" << std::endl;
  std::cout << "========================================\n" << std::endl;

  // 1. 基本操作测试
  std::cout << "--- 1. 基本操作测试 ---" << std::endl;
  ThreadSafeQueue<int> q1;
  q1.push(1);
  q1.push(2);
  q1.push(3);
  std::cout << "push 1, 2, 3 后, size = " << q1.size() << std::endl;

  auto val = q1.try_pop();
  std::cout << "try_pop: " << (val ? std::to_string(*val) : "empty")
            << std::endl;
  std::cout << "pop: " << q1.pop() << std::endl;
  std::cout << "剩余 size = " << q1.size() << std::endl;

  // 2. 有界队列测试
  std::cout << "\n--- 2. 有界队列测试 ---" << std::endl;
  ThreadSafeQueue<int> q2(3); // 容量为3
  std::cout << "创建容量为3的队列" << std::endl;
  std::cout << "try_push 1: " << (q2.try_push(1) ? "成功" : "失败")
            << std::endl;
  std::cout << "try_push 2: " << (q2.try_push(2) ? "成功" : "失败")
            << std::endl;
  std::cout << "try_push 3: " << (q2.try_push(3) ? "成功" : "失败")
            << std::endl;
  std::cout << "try_push 4: " << (q2.try_push(4) ? "成功" : "失败")
            << " (队列已满)" << std::endl;

  // 3. 多线程生产者-消费者测试
  std::cout << "\n--- 3. 多线程生产者-消费者测试 ---" << std::endl;
  ThreadSafeQueue<int> q3;
  std::atomic<int> sum{0};
  const int NUM_ITEMS = 100;

  // 生产者线程
  auto producer = [&q3, NUM_ITEMS]() {
    for (int i = 1; i <= NUM_ITEMS; ++i) {
      q3.push(i);
      std::this_thread::sleep_for(std::chrono::microseconds(10));
    }
    std::cout << "生产者: 完成生产 " << NUM_ITEMS << " 个元素" << std::endl;
  };

  // 消费者线程
  auto consumer = [&q3, &sum, NUM_ITEMS]() {
    int count = 0;
    while (count < NUM_ITEMS) {
      auto val = q3.pop_for(std::chrono::milliseconds(100));
      if (val) {
        sum += *val;
        ++count;
      }
    }
    std::cout << "消费者: 完成消费 " << count << " 个元素" << std::endl;
  };

  std::thread t1(producer);
  std::thread t2(consumer);
  t1.join();
  t2.join();

  int expected = NUM_ITEMS * (NUM_ITEMS + 1) / 2;
  std::cout << "累加和: " << sum << " (期望: " << expected << ")" << std::endl;
  std::cout << "验证: " << (sum == expected ? "通过" : "失败") << std::endl;

  // 4. 多生产者多消费者测试
  std::cout << "\n--- 4. 多生产者多消费者测试 ---" << std::endl;
  ThreadSafeQueue<int> q4;
  std::atomic<int> total_produced{0};
  std::atomic<int> total_consumed{0};
  const int ITEMS_PER_PRODUCER = 500;
  const int NUM_PRODUCERS = 4;
  const int NUM_CONSUMERS = 2;

  auto multi_producer = [&](int id) {
    for (int i = 0; i < ITEMS_PER_PRODUCER; ++i) {
      q4.push(id * 10000 + i);
      ++total_produced;
    }
  };

  auto multi_consumer = [&]() {
    while (total_consumed < NUM_PRODUCERS * ITEMS_PER_PRODUCER) {
      auto val = q4.pop_for(std::chrono::milliseconds(50));
      if (val) {
        ++total_consumed;
      }
    }
  };

  std::vector<std::thread> producers;
  std::vector<std::thread> consumers;

  for (int i = 0; i < NUM_PRODUCERS; ++i) {
    producers.emplace_back(multi_producer, i);
  }
  for (int i = 0; i < NUM_CONSUMERS; ++i) {
    consumers.emplace_back(multi_consumer);
  }

  for (auto &t : producers)
    t.join();
  for (auto &t : consumers)
    t.join();

  std::cout << "生产: " << total_produced << ", 消费: " << total_consumed
            << std::endl;
  std::cout << "验证: " << (total_produced == total_consumed ? "通过" : "失败")
            << std::endl;

  std::cout << "\n========================================" << std::endl;
  std::cout << "      ThreadSafeQueue 测试完成" << std::endl;
  std::cout << "========================================" << std::endl;

  return 0;
}
