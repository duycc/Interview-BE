/**
 * @file     09.cpp
 * @brief
 * @author   YongDu
 * @date     2022-07-29
 */

#include <algorithm>
#include <future>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

using namespace std;

class A {
  public:
    int myThread(int x) {
        cout << "[myThread] start: thread_id=" << std::this_thread::get_id() << endl;
        cout << "x=" << x << endl;
        std::this_thread::sleep_for(5s);
        cout << "[myThread] end: thread_id=" << std::this_thread::get_id() << endl;
        return 5;
    }
};

int myThread(int x) {
    cout << "[myThread] start: thread_id=" << std::this_thread::get_id() << endl;
    cout << "x=" << x << endl;
    std::this_thread::sleep_for(5s);
    cout << "[myThread] end: thread_id=" << std::this_thread::get_id() << endl;
    return 5;
}

void fun1(std::promise<int> &tmp, int x) {
    x++;
    x *= 10;
    std::this_thread::sleep_for(5s);
    tmp.set_value(x);
}

void fun2(std::future<int> &tmp) {
    int result = tmp.get();
    cout << "[fun2] result=" << result << endl;
}

int main() {
    cout << "[main] start: thread_id=" << std::this_thread::get_id() << endl;
    // 1. std::async, std::future创建后台任务并返回值
    /*
    std::future: 线程入口函数返回的结果，一种访问异步操作结果的机制
    std::launch::deferred
    延迟创建线程，到调用wait()或者get()时执行线程函数，并不会创建新线程，在主线程中调用线程入口函数
    */
    // A a;
    // int x = 12;
    // // std::future<int> result = std::async(std::launch::deferred, &A::myThread, &a, x);
    // std::future<int> result = std::async(std::launch::async, &A::myThread, &a, x);
    // cout << "[main] continue..." << endl;
    // cout << result.get() << endl; // 阻塞直到拿到结果

    // 2. std::packaged_task 打包任务，类模板，模板参数为可调用对象
    // packaged_task 包装的可调用对象本身可以直接调用

    // std::packaged_task<int(int)> mypt(myThread);
    // std::thread t1(std::ref(mypt), 1);
    // t1.join();

    // std::future<int> result = mypt.get_future();
    // cout << "result=" << result.get() << endl;

    // std::packaged_task<int(int)> myTh2([](int x) {
    //     cout << "[myThread] start: thread_id=" << std::this_thread::get_id() << endl;
    //     cout << "x=" << x << endl;
    //     std::this_thread::sleep_for(5s);
    //     cout << "[myThread] end: thread_id=" << std::this_thread::get_id() << endl;
    //     return 5;
    // });

    // std::thread t1(std::ref(myTh2), 1);
    // t1.join();

    // std::future<int> result = myTh2.get_future();
    // cout << "result=" << result.get() << endl;

    // myTh2(2);
    // std::future<int> result = myTh2.get_future();
    // cout << "result=" << result.get() << endl;

    // std::vector<std::packaged_task<int(int)>> tasks;
    // tasks.push_back(std::move(myTh2));

    // auto myTh3 = std::move(tasks.front());
    // std::vector<std::packaged_task<int(int)>>().swap(tasks);

    // myTh3(123);
    // std::future<int> result = myTh3.get_future();
    // cout << "result=" << result.get() << endl;

    // 3. std::promise 类模板
    // 能在某个线程中给它赋值，其它线程中取出这个值。通过promise保存某个值，在将来某个时刻通过future来得到这个值，实现线程间数据共享

    std::promise<int> prom;
    std::thread t1(fun1, std::ref(prom), 4);
    t1.join();
    std::future<int> fu1 = prom.get_future();
    // cout << "result=" << result.get() << endl;
    std::thread t2(fun2, std::ref(fu1));
    t2.join();

    cout << "[main] end..." << endl;
    return 0;
}