/**
 * @file     08.cpp
 * @brief
 * @author   YongDu
 * @date     2022-07-28
 */

#include <condition_variable>
#include <iostream>
#include <list>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

using namespace std;

class A {
  public:
    void inMsgRecvQue() {
        for (int i = 0; i < 100000; ++i) {
            std::unique_lock<std::mutex> lGuard(m_mutex);
            cout << "inMsgRecvQue(): msg=" << i << endl;
            msgRecvQue.emplace_back(i);
            cond_.notify_one();
        }
    }

    void outMsgRecvQue() {
        int msg;
        while (true) {
            std::unique_lock<std::mutex> lGuard(m_mutex);

            cond_.wait(lGuard, [this] { return !msgRecvQue.empty(); });

            msg = msgRecvQue.front();
            msgRecvQue.pop_front();
            lGuard.unlock();
            cout << "[outMsgRecvQue] msg=" << msg << endl;
        }
    }

  private:
    std::list<int> msgRecvQue;
    std::mutex m_mutex;
    std::condition_variable cond_;
};

int main() {
    cout << "main() start..." << endl;

    A a;
    std::thread taIn(&A::outMsgRecvQue, &a);
    std::thread taOut(&A::inMsgRecvQue, &a);

    taIn.join();
    taOut.join();

    cout << "main() end..." << endl;
    return 0;
}