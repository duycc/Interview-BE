#include <iostream>

struct A {
  int m_a{4};

  A() : m_a(3) { m_a = 2; }
};

int main() {
  //   int a = 0;
  //   static int b = a;
  A a;
  std::cout << a.m_a << std::endl;
  return 0;
}
