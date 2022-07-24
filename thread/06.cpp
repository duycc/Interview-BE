/**
 * @file     06.cpp
 * @brief
 * @author   YongDu
 * @date     2022-07-16
 */

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
            cout << "inMsgRecvQue(): msg=" << i << endl;
            {
                // std::lock_guard<std::mutex> mtx(m_mutex);
                // std::unique_lock<std::mutex> mtx(m_mutex, std::try_to_lock);
                std::unique_lock<std::mutex> mtx(m_mutex, std::defer_lock);
                // mtx.lock();
                // mtx.unlock();
                if (mtx.try_lock()) {
                    msgRecvQue.emplace_back(i);
                } else {
                    cout << "[inMsgRecvQue] skip lock, do other thing" << endl;
                }
                auto* pMtx = mtx.release();
                // if (mtx.owns_lock()) {
                //     msgRecvQue.emplace_back(i);
                // } else {
                //     cout << "[inMsgRecvQue] skip lock, do other thing" << endl;
                // }
            }
        }
    }

    void outMsgRecvQue() {
        int msg;
        for (int i = 0; i < 100000; ++i) {
            if (outMsgLULProc(msg)) {
                cout << "outMsgRecvQue(): msg=" << msg << endl;
            } else {
                cout << "msgRecvQue is empty" << endl;
            }
        }
    }

    bool outMsgLULProc(int& msg) {
        // std::lock_guard<std::mutex> mtx(m_mutex);
        std::unique_lock<std::mutex> mtx(m_mutex);
        // std::chrono::milliseconds dura(20000);
        // std::this_thread::sleep_for(dura);

        if (!msgRecvQue.empty()) {
            msg = msgRecvQue.front();
            msgRecvQue.pop_front();
            return true;
        }
        return false;
    }

  private:
    std::list<int> msgRecvQue;
    std::mutex m_mutex;
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