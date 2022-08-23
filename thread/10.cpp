/**
 * @file     10.cpp
 * @brief
 * @author   YongDu
 * @date     2022-07-29
 */

#include <algorithm>
#include <atomic>
#include <future>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

using namespace std;
using namespace chrono;

int fun1() {
    cout << "[fun1] start: thread_id=" << std::this_thread::get_id() << endl;
    std::this_thread::sleep_for(3s);
    cout << "[fun1] end..." << endl;
    return 5;
}

void fun2(std::shared_future<int> &x) {
    cout << "[fun2] start: thread_id=" << std::this_thread::get_id() << endl;
    int result = x.get();
    cout << "[fun2] result=" << result << endl;
}

int fun3(int x) {
    cout << "[fun3] start: thread_id=" << std::this_thread::get_id() << endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    return 5;
}

// int g_count = 0;
std::atomic<int> g_count(0);
std::mutex g_mtx;

std::atomic<bool> g_flag(false);

void fun5() {
    while (!g_flag) {
        cout << "[fun5] running: thread_id=" << std::this_thread::get_id() << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    cout << "[fun5] end..." << endl;
}

void fun4() {
    for (int i = 0; i < 10000000; ++i) {
        // std::unique_lock<std::mutex> mtx(g_mtx);
        g_count++;
    }
}

int main() {
    cout << "[main] start: thread_id=" << std::this_thread::get_id() << endl;

    // std::future<int> fu1 = std::async(std::launch::async, fun1);
    // cout << "[main] continue..." << endl;
    // // int result = fu1.get();
    // std::future_status status = fu1.wait_for(std::chrono::seconds(5));
    // if (status == std::future_status::timeout) {
    //     cout << "[main] fun1 timeout" << endl;
    // } else if (status == std::future_status::ready) {
    //     cout << "[main] fun1 succeed" << endl;
    //     cout << "[main] result=" << fu1.get() << endl;
    // } else if (status == std::future_status::deferred) {
    //     // 如果async被指定为std::launch::defered，此条件成立
    //     cout << "[main] fun1 defered" << endl;
    //     cout << "[main] result=" << fu1.get() << endl;
    // }
    // cout << "[main] result=" << result << endl;

    // 2. std::shared_future
    // std::packaged_task<int(int)> pt1(fun3);
    // std::thread t1(std::ref(pt1), 1);
    // t1.join();
    // std::future<int> fu1 = pt1.get_future();
    // std::shared_future<int> sfu1(fu1.share());

    // std::thread t2(fun2, std::ref(sfu1));
    // t2.join();

    // 3. std::atomic
    // mutex: 多线程保护共享数据。针对代码片段
    // 原子操作：多线程执行中，不会被打断的程序执行片段。比使用锁效率更高。针对变量

    // std::thread t1(fun4);
    // std::thread t2(fun4);
    // t1.join();
    // t2.join();

    // cout << "[main] g_count=" << g_count << endl;

    std::thread t1(fun5);
    std::thread t2(fun5);
    std::this_thread::sleep_for(std::chrono::seconds(5));
    g_flag = true;
    t1.join();
    t2.join();

    cout << "[main] end..." << endl;
    return 0;
}