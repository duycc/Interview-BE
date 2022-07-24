/**
 * @file     07.cpp
 * @brief
 * @author   YongDu
 * @date     2022-07-23
 */
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

using namespace std;

std::once_flag g_flag;

class Singleton {
    static void CreateInstance() { m_instance = new Singleton(); }

  private:
    static Singleton *m_instance;
    std::mutex m_mtx;

  public:
    static Singleton *GetInstance();

  private:
    Singleton() {}
};

Singleton *Singleton::m_instance = nullptr;

Singleton *Singleton::GetInstance() {
    // if (m_instance == nullptr) {
    //     std::unique_lock<std::mutex> mtx(m_mtx);
    //     if (m_instance == nullptr) {
    //         m_instance = new Singleton();
    //     }
    // }
    std::call_once(g_flag, CreateInstance);
    return m_instance;
}

int main() {
    // Singleton *ps = Singleton::GetInstance();
    cout << "hwllo world" << endl;

    return 0;
}