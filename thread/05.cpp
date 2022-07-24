/**
 * @file     05.cpp
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
            // m_mutex.lock();
            // msgRecvQue.emplace_back(i);
            // m_mutex.unlock();
            {
                std::lock_guard<std::mutex> mtx(m_mutex);
                msgRecvQue.emplace_back(i);
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
        std::lock_guard<std::mutex> mtx(m_mutex);
        // m_mutex.lock();
        if (!msgRecvQue.empty()) {
            msg = msgRecvQue.front();
            msgRecvQue.pop_front();
            // m_mutex.unlock();
            return true;
        }
        // m_mutex.unlock();
        return false;
    }

  private:
    std::list<int> msgRecvQue;
    std::mutex     m_mutex;
};

int main() {
    cout << "main() start..." << endl;

    A           a;
    std::thread taIn(&A::outMsgRecvQue, &a);
    std::thread taOut(&A::inMsgRecvQue, &a);

    taIn.join();
    taOut.join();

    cout << "main() end..." << endl;
    return 0;
}