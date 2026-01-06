/**
 * RingBuffer 测试程序
 * 包括：RingBuffer, ThreadSafeRingBuffer, LockFreeRingBuffer
 */

#include "RingBuffer.hpp"
#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

// ==================== RingBuffer 基础测试 ====================
void test_ring_buffer() {
  std::cout << "========================================" << std::endl;
  std::cout << "         RingBuffer 测试" << std::endl;
  std::cout << "========================================\n" << std::endl;

  // 1. 基本操作测试
  std::cout << "--- 1. 基本操作测试 ---" << std::endl;
  RingBuffer<int> rb(5);
  std::cout << "创建容量为5的RingBuffer" << std::endl;

  for (int i = 1; i <= 5; ++i) {
    rb.push(i);
    std::cout << "push " << i << ": " << rb << std::endl;
  }

  std::cout << "push 6 (满): " << (rb.push(6) ? "成功" : "失败") << std::endl;

  // 2. 覆盖模式测试
  std::cout << "\n--- 2. 覆盖模式测试 ---" << std::endl;
  rb.push_overwrite(6);
  std::cout << "push_overwrite 6: " << rb << std::endl;
  rb.push_overwrite(7);
  std::cout << "push_overwrite 7: " << rb << std::endl;

  // 3. 读取测试
  std::cout << "\n--- 3. 读取测试 ---" << std::endl;
  while (!rb.empty()) {
    auto val = rb.pop();
    std::cout << "pop: " << *val << ", 剩余: " << rb << std::endl;
  }

  // 4. 循环特性测试
  std::cout << "\n--- 4. 循环特性测试 ---" << std::endl;
  RingBuffer<int> rb2(3);
  for (int round = 1; round <= 3; ++round) {
    std::cout << "第 " << round << " 轮:" << std::endl;
    rb2.push(round * 10 + 1);
    rb2.push(round * 10 + 2);
    rb2.push(round * 10 + 3);
    std::cout << "  push后: " << rb2 << std::endl;
    rb2.pop();
    rb2.pop();
    rb2.pop();
    std::cout << "  pop后: " << rb2 << std::endl;
  }

  // 5. front/back 测试
  std::cout << "\n--- 5. front/back 测试 ---" << std::endl;
  RingBuffer<int> rb3(5);
  rb3.push(10);
  rb3.push(20);
  rb3.push(30);
  std::cout << "buffer: " << rb3 << std::endl;
  std::cout << "front: " << *rb3.front() << std::endl;
  std::cout << "back: " << *rb3.back() << std::endl;
}

// ==================== ThreadSafeRingBuffer 测试 ====================
void test_thread_safe_ring_buffer() {
  std::cout << "\n========================================" << std::endl;
  std::cout << "    ThreadSafeRingBuffer 测试" << std::endl;
  std::cout << "========================================\n" << std::endl;

  ThreadSafeRingBuffer<int> rb(10);
  std::atomic<int> produced{0};
  std::atomic<int> consumed{0};
  const int NUM_ITEMS = 1000;

  // 多个生产者
  auto producer = [&](int id) {
    for (int i = 0; i < NUM_ITEMS / 2; ++i) {
      rb.push(id * 1000 + i);
      ++produced;
    }
  };

  // 多个消费者
  auto consumer = [&]() {
    while (consumed < NUM_ITEMS) {
      auto val = rb.pop_for(std::chrono::milliseconds(10));
      if (val) {
        ++consumed;
      }
    }
  };

  std::thread p1(producer, 1);
  std::thread p2(producer, 2);
  std::thread c1(consumer);
  std::thread c2(consumer);

  p1.join();
  p2.join();
  c1.join();
  c2.join();

  std::cout << "生产: " << produced << ", 消费: " << consumed << std::endl;
  std::cout << "验证: " << (produced == consumed ? "通过" : "失败")
            << std::endl;

  // 测试覆盖写入
  std::cout << "\n--- 覆盖写入测试 ---" << std::endl;
  ThreadSafeRingBuffer<int> rb2(3);
  rb2.push_overwrite(1);
  rb2.push_overwrite(2);
  rb2.push_overwrite(3);
  rb2.push_overwrite(4); // 覆盖1
  rb2.push_overwrite(5); // 覆盖2

  std::cout << "push_overwrite 1,2,3,4,5 到容量为3的buffer" << std::endl;
  std::cout << "pop顺序: ";
  while (!rb2.empty()) {
    std::cout << rb2.pop() << " ";
  }
  std::cout << "(期望: 3 4 5)" << std::endl;
}

// ==================== LockFreeRingBuffer 测试 ====================
void test_lock_free_ring_buffer() {
  std::cout << "\n========================================" << std::endl;
  std::cout << "    LockFreeRingBuffer (SPSC) 测试" << std::endl;
  std::cout << "========================================\n" << std::endl;

  LockFreeRingBuffer<int> rb(1024);
  std::atomic<bool> done{false};
  std::atomic<long long> sum{0};
  const int NUM_ITEMS = 100000;

  // 单生产者
  auto producer = [&]() {
    for (int i = 1; i <= NUM_ITEMS; ++i) {
      while (!rb.push(i)) {
        std::this_thread::yield();
      }
    }
    done = true;
  };

  // 单消费者
  auto consumer = [&]() {
    long long local_sum = 0;
    int count = 0;
    while (!done || !rb.empty()) {
      int val;
      if (rb.pop(val)) {
        local_sum += val;
        ++count;
      } else {
        std::this_thread::yield();
      }
    }
    sum = local_sum;
    std::cout << "消费了 " << count << " 个元素" << std::endl;
  };

  auto start = std::chrono::high_resolution_clock::now();

  std::thread p(producer);
  std::thread c(consumer);
  p.join();
  c.join();

  auto end = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start);

  long long expected = (long long)NUM_ITEMS * (NUM_ITEMS + 1) / 2;
  std::cout << "累加和: " << sum << " (期望: " << expected << ")" << std::endl;
  std::cout << "验证: " << (sum == expected ? "通过" : "失败") << std::endl;
  std::cout << "耗时: " << duration.count() << " 微秒" << std::endl;
  std::cout << "吞吐量: " << (NUM_ITEMS * 1000000.0 / duration.count())
            << " ops/s" << std::endl;
}

// ==================== 性能对比测试 ====================
void test_performance_comparison() {
  std::cout << "\n========================================" << std::endl;
  std::cout << "         性能对比测试" << std::endl;
  std::cout << "========================================\n" << std::endl;

  const int NUM_ITEMS = 100000;

  // 测试 ThreadSafeRingBuffer
  {
    ThreadSafeRingBuffer<int> rb(1024);
    std::atomic<bool> done{false};

    auto start = std::chrono::high_resolution_clock::now();

    std::thread producer([&]() {
      for (int i = 0; i < NUM_ITEMS; ++i) {
        rb.push(i);
      }
      done = true;
    });

    std::thread consumer([&]() {
      int count = 0;
      while (!done || !rb.empty()) {
        if (rb.try_pop()) {
          ++count;
        }
      }
    });

    producer.join();
    consumer.join();

    auto end = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "ThreadSafeRingBuffer: " << duration.count() << " 微秒, "
              << (NUM_ITEMS * 1000000.0 / duration.count()) << " ops/s"
              << std::endl;
  }

  // 测试 LockFreeRingBuffer
  {
    LockFreeRingBuffer<int> rb(1024);
    std::atomic<bool> done{false};

    auto start = std::chrono::high_resolution_clock::now();

    std::thread producer([&]() {
      for (int i = 0; i < NUM_ITEMS; ++i) {
        while (!rb.push(i)) {
          std::this_thread::yield();
        }
      }
      done = true;
    });

    std::thread consumer([&]() {
      int count = 0;
      while (!done || !rb.empty()) {
        int val;
        if (rb.pop(val)) {
          ++count;
        } else {
          std::this_thread::yield();
        }
      }
    });

    producer.join();
    consumer.join();

    auto end = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "LockFreeRingBuffer:   " << duration.count() << " 微秒, "
              << (NUM_ITEMS * 1000000.0 / duration.count()) << " ops/s"
              << std::endl;
  }
}

int main() {
  std::cout << "========================================" << std::endl;
  std::cout << "      RingBuffer 系列测试程序" << std::endl;
  std::cout << "========================================" << std::endl;

  test_ring_buffer();
  test_thread_safe_ring_buffer();
  test_lock_free_ring_buffer();
  test_performance_comparison();

  std::cout << "\n========================================" << std::endl;
  std::cout << "         所有测试完成" << std::endl;
  std::cout << "========================================" << std::endl;

  return 0;
}
