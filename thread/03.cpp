#include <iostream>
#include <thread>

using namespace std;

class A {
  public:
    A(int i) : m_i(i) {
        cout << "[A(int i)] was called: this=" << this << " thread_id=" << std::this_thread::get_id() << endl;
    }
    A(const A& a) : m_i(a.m_i) {
        cout << "[A(const A& a)] was called: this=" << this << " thread_id=" << std::this_thread::get_id() << endl;
    }

    ~A() { cout << "[~A()] was called: this=" << this << " thread_id=" << std::this_thread::get_id() << endl; }

    int m_i;
};

void printAddr(const int& i, char* str) {
    cout << "i=" << i << ", addr=" << &i << endl;
    cout << "str=" << str << ", addr=" << &str << endl;
}

void printA(const A& a) { cout << "m_i=" << a.m_i << " addr=" << &a << endl; }

int main() {
    cout << "main thread_id=" << std::this_thread::get_id() << endl;
    int  i = 3;
    int& ra = i;
    char str[] = "hello world";

    // cout << "ra=" << ra << ", addr=" << &ra << endl;
    // cout << "str=" << str << ", addr=" << &str << endl;

    // thread tPrint(printAddr, ra, str);
    // tPrint.join();

    // int    ia = 4;
    // thread ta(printA, A(ia));
    // cout << "ta thread_id=" << ta.get_id() << endl;

    A      aa(5);
    thread taa(printA, std::ref(aa));

    taa.join();
    // ta.detach();

    return EXIT_SUCCESS;
}