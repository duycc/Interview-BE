/**
 * @file     04.cpp
 * @brief
 * @author   YongDu
 * @date     2022-07-16
 */
#include <iostream>
#include <list>
#include <string>
#include <thread>
#include <vector>

using namespace std;

void thFunc(int num) { cout << "thFunc() start: num=" << num << " thread_id=" << std::this_thread::get_id() << endl; }

class A {
  public:
    void inMsgRecvQue() {
        for (int i = 0; i < 100000; ++i) {
            cout << "inMsgRecvQue(): msg=" << i << endl;
            msgRecvQue.emplace_back(i);
        }
    }

    void outMsgRecvQue() {
        for (int i = 0; i < 100000; ++i) {
            if (!msgRecvQue.empty()) {
                cout << "outMsgRecvQue(): msg=" << msgRecvQue.front() << endl;
                msgRecvQue.pop_front();
            } else {
                cout << "msgRecvQue is empty" << endl;
            }
        }
    }

  private:
    std::list<int> msgRecvQue;
};

int main() {
    cout << "main() start..." << endl;
    // vector<thread> ts;

    // for (int i = 0; i < 10; ++i) {
    //     ts.emplace_back(thread(thFunc, i));
    // }

    // for (auto& t : ts) {
    //     t.join();
    // }

    A           a;
    std::thread taIn(&A::outMsgRecvQue, &a);
    std::thread taOut(&A::inMsgRecvQue, &a);

    taIn.join();
    taOut.join();

    cout << "main() end..." << endl;
    return 0;
}