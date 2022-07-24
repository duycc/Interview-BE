#include <iostream>
#include <string>
#include <thread>

using namespace std;

void myPrint() {
    cout << "my thread start..." << endl;
    // ...
    cout << "my thread end..." << endl;
}

class A {
  public:
    void operator()() { // 不能带参数
        cout << "A thread start..." << endl;
    }
};

// join()
// detach(): 主线程和子线程失去关联，子线程驻留后台运行，执行完成后，由运行时库清理该子线程相关资源
// joinable(): 判断是否可以使用join或者detach

int main() {
    // thread myTOb(myPrint); // thread构造接受一个可调用对象
    // myTOb.join();          // join: 阻塞主线程，让主线程等待子线程执行完毕
    // myTOb.detach();

    // 仿函数
    // A      a;
    // thread mytob2(a);
    // mytob2.join();

    // lambda表达式
    auto f = [] { cout << "L thread start..." << endl; };

    thread mytob3(f);
    mytob3.join();

    cout << "I Love China..." << endl;
    return EXIT_SUCCESS;
}