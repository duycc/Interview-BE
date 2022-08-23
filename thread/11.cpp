/**
 * @file     11.cpp
 * @brief
 * @author   YongDu
 * @date     2022-07-31
 */

#include <algorithm>
#include <atomic>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

using namespace std;

std::atomic<int> g_count{0};

void fun1() {
    for (int i = 0; i < 10000000; ++i) {
        // g_count++;
        // g_count += 1;
        g_count = g_count + 1;
    }
}

int main() {
    cout << "[main] start: thread_id=" << std::this_thread::get_id() << endl;
    std::thread t1(fun1);
    std::thread t2(fun1);
    t1.join();
    t2.join();
    cout << "[main] g_count=" << g_count << endl;

    cout << "[main] end..." << endl;
    return 0;
}