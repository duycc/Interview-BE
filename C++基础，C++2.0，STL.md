***

## 一、C++基础

***

### const

**作用：**

- 修饰变量，说明该变量不可以被改变
- 修饰指针，分为指向常量的指针（pointer to const）和自身是常量的指针（常量指针，const pointer）
- 修饰引用，指向常量的引用（reference to const），用于形参类型，即避免了拷贝，又避免了函数对值的修改
- 修饰成员函数，说明该成员函数内不能修改成员变量

**示例代码：**

```cpp
class A {
private:
  const int a; // 常对象成员，只能在初始化列表赋值

public:
  // 构造函数
  A() : a(0){};
  A(int x) : a(x){}; // 初始化列表

  // const可用于对重载函数的区分
  int getValue();       // 普通成员函数，只能被非const对象访问
  int getValue() const; // 常成员函数，不得修改类中的任何数据成员的值
};

void function() {
  // 对象
  A b;             // 普通对象，可以调用全部成员函数、更新常成员变量
  const A a;       // 常对象，可调用常成员函数，也可调用非常成员函数
  const A *p = &a; // 指针变量，指向常对象
  const A &q = a;  // 指向常对象的引用

  // 指针
  char greeting[] = "Hello";
  char *p1 = greeting; // 指针变量，指向字符数组变量
  const char *p2 = greeting; // 指针变量，指向字符数组常量（const 后面是 char，说明指向的字符（char）不可改变）
  char *const p3 = greeting; // 自身是常量的指针，指向字符数组变量（const 后面是 p3，说明 p3 指针自身不可改变）
  const char *const p4 = greeting; // 自身是常量的指针，指向字符数组常量
}

// 函数
void function1(const int Var);   // 传递过来的参数在函数内不可变
void function2(const char *Var); // 参数指针所指内容为常量
void function3(char *const Var); // 参数指针为常量
void function4(const int &Var);  // 引用参数在函数内为常量

// 函数返回值
const int function5();  // 返回一个常数
const int *function6(); // 返回一个指向常量的指针变量，使用：const int *p = function6();
int *const function7(); // 返回一个指向变量的常指针，使用：int* const p = function7();
```

### static

- 修饰普通变量，修改变量的存储区域和生命周期，使变量存储在静态区，在 main 函数运行前就分配了空间，如果有初始值就用初始值初始化它，如果没有初始值系统用默认值初始化它
- 修饰普通函数，表明函数的作用范围，仅在定义该函数的文件内才能使用。在多人开发项目时，为了防止与他人命名空间里的函数重名，可以将函数定位为 static
- 修饰成员变量，修饰成员变量使所有的对象只保存一个该变量，而且不需要生成对象就可以访问该成员
- 修饰成员函数，修饰成员函数使得不需要生成对象就可以访问该函数，但是在 static 函数内不能访问非静态成员

**静态变量什么时候初始化：**

* 初始化只有一次，但是可以多次赋值，在主程序之前，编译器已经为其分配好了内存

* 静态局部变量和全局变量一样，数据都存放在全局区域，所以在主程序之前，编译器已经为其分配好了内存，但在C和C++中静态局部变量的初始化节点又有点不太一样。在C中，初始化发生在代码执行之前，编译阶段分配好内存之后，就会进行初始化，所以我们看到在C语言中无法使用变量对静态局部变量进行初始化，在程序运行结束，变量所处的全局内存会被全部回收

* 而在C++中，初始化时在执行相关代码时才会进行初始化，主要是由于C++引入对象后，要进行初始化必须执行相应构造函数和析构函数，在构造函数或析构函数中经常会需要进行某些程序中需要进行的特定操作，并非简单地分配内存。所以C++标准定为全局或静态对象是有首次用到时才会进行构造，并通过atexit()来管理。在程序结束，按照构造顺序反方向进行逐个析构。所以在C++中是可以使用变量对静态局部变量进行初始化的

### this

- `this` 指针是一个隐含于每一个非静态成员函数中的特殊指针。它指向调用该成员函数的那个对象
- 当对一个对象调用成员函数时，编译程序先将对象的地址赋给 `this` 指针，然后调用成员函数，每次成员函数存取数据成员时，都隐式使用 `this` 指针
- 当一个成员函数被调用时，自动向它传递一个隐含的参数，该参数是一个指向这个成员函数所在的对象的指针
- `this` 指针被隐含地声明为: `ClassName *const this`，这意味着不能给 `this` 指针赋值；在 `ClassName` 类的 `const` 成员函数中，`this` 指针的类型为：`const ClassName* const`，这说明不能对 `this` 指针所指向的这种对象是不可修改的（即不能对这种对象的数据成员进行赋值操作）
- `this` 并不是一个常规变量，而是个右值，所以不能取得 `this` 的地址（不能 `&this`）
- 在以下场景中，经常需要显式引用 `this` 指针：
   - 为实现对象的链式引用
   - 为避免对同一对象进行赋值操作
   - 在实现一些数据结构时，如 `list`

**几个this指针的易混问题：**

**A. this指针是什么时候创建的？**

this在成员函数的开始执行前构造，在成员的执行结束后清除

**B. this指针存放在何处？堆、栈、全局变量，还是其他？**

this指针会因编译器不同而有不同的放置位置。可能是栈，也可能是寄存器，甚至全局变量。在汇编级别里面，一个值只会以3种形式出现：立即数、寄存器值和内存变量值。不是存放在寄存器就是存放在内存中，它们并不是和高级语言变量对应的。

**C. this指针是如何传递类中的函数的？绑定？还是在函数参数的首参数就是this指针？那么，this指针又是如何找到“类实例后函数的”？**

大多数编译器通过ecx（寄数寄存器）寄存器传递this指针。事实上，这也是一个潜规则。一般来说，不同编译器都会遵从一致的传参规则，否则不同编译器产生的obj就无法匹配了。

在call之前，编译器会把对应的对象地址放到eax中。this是通过函数参数的首参来传递的。this指针在调用之前生成，至于“类实例后函数”，没有这个说法。类在实例化时，只分配类中的变量空间，并没有为函数分配空间。自从类的函数定义完成后，它就在那儿，不会跑的

**D. this指针是如何访问类中的变量的？**

如果不是类，而是结构体的话，那么，如何通过结构指针来访问结构中的变量呢？如果你明白这一点的话，就很容易理解这个问题了。

在C++中，类和结构是只有一个区别的：类的成员默认是private，而结构是public。

this是类的指针，如果换成结构体，那this就是结构的指针了。

**E.我们只有获得一个对象后，才能通过对象使用this指针。如果我们知道一个对象this指针的位置，可以直接使用吗？**

**this指针只有在成员函数中才有定义。**因此，你获得一个对象后，也不能通过对象使用this指针。所以，我们无法知道一个对象的this指针的位置（只有在成员函数里才有this指针的位置）。当然，在成员函数里，你是可以知道this指针的位置的（可以通过&this获得），也可以直接使用它。

**F.每个类编译后，是否创建一个类中函数表保存函数指针，以便用来调用函数？**

普通的类函数（不论是成员函数，还是静态函数）都不会创建一个函数表来保存函数指针。只有虚函数才会被放到函数表中。但是，即使是虚函数，如果编译期就能明确知道调用的是哪个函数，编译器就不会通过函数表中的指针来间接调用，而是会直接调用该函数。正是由于this指针的存在，用来指向不同的对象，从而确保不同对象之间调用相同的函数可以互不干扰

### inline

**特点：**

* 相当于把内联函数里面的内容写在调用内联函数处
* 相当于不用执行进入函数的步骤，直接执行函数体
* 相当于宏，却比宏多了类型检查，真正具有函数特性
* 编译器一般不内联包含循环、递归、switch 等复杂操作的内联函数
* 在类声明中定义的函数，除了虚函数的其他函数都会自动隐式地当成内联函数

**使用：**

```cpp
// 声明1（加 inline，建议使用）
inline int functionName(int first, int second, ...);

// 声明2（不加 inline）
int functionName(int first, int second, ...);

// 定义
inline int functionName(int first, int second, ...){/****/};

// 类内定义，隐式内联
class A {
  int doA() { return 0; } // 隐式内联
}

// 类外定义，需要显式内联
class A {
  int doA();
};

inline int A::doA() { return 0; } // 需要显式内联
```

**编译器对内联函数的处理：**

- 将 inline 函数体复制到 inline 函数调用点处 
- 为所用 inline 函数中的局部变量分配内存空间
- 将 inline 函数的的输入参数和返回值映射到调用方法的局部变量空间中
- 如果 inline 函数有多个返回点，将其转变为 inline 函数代码块末尾的分支（使用 GOTO）

**优缺点：**

==优点==

1. 内联函数同宏函数一样将在被调用处进行代码展开，省去了参数压栈、栈帧开辟与回收，结果返回等，从而提高程序运行速度。
2. 内联函数相比宏函数来说，在代码展开时，会做安全检查或自动类型转换（同普通函数），而宏定义则不会。 
3. 在类中声明同时定义的成员函数，自动转化为内联函数，因此内联函数可以访问类的成员变量，宏定义则不能。
4. 内联函数在运行时可调试，而宏定义不可以。

==缺点==

1. 代码膨胀。内联是以代码膨胀（复制）为代价，消除函数调用带来的开销。如果执行函数体内代码的时间，相比于函数调用的开销较大，那么效率的收获会很少。另一方面，每一处内联函数的调用都要复制代码，将使程序的总代码量增大，消耗更多的内存空间。
2. inline 函数无法随着函数库升级而升级。inline函数的改变需要重新编译，不像 non-inline 可以直接链接。
3. 是否内联，程序员不可控。内联函数只是对编译器的建议，是否对函数内联，决定权在于编译器。

**虚函数（virtual）可以是内联函数（inline）吗？**

* 虚函数可以是内联函数，内联是可以修饰虚函数的，但是当虚函数表现多态性的时候不能内联。
* 内联是在编译器建议编译器内联，而虚函数的多态性在运行期，编译器无法知道运行期调用哪个代码，因此虚函数表现为多态性时（运行期）不可以内联。
* `inline virtual` 唯一可以内联的时候是：编译器知道所调用的对象是哪个类（如 `Base::who()`），这只有在编译器具有实际对象而不是对象的指针或引用时才会发生。

```cpp
#include <iostream>
using namespace std;

class Base {
public:
  inline virtual void who() { cout << "I am Base\n"; }
  virtual ~Base() {}
};

class Derived : public Base {
public:
  inline void who() {
    // 不写inline时隐式内联
    cout << "I am Derived\n";
  }
};

int main() {
  // 此处的虚函数
  // who()，是通过类（Base）的具体对象（b）来调用的，编译期间就能确定了，所以它可以是内联的，但最终是否内联取决于编译器。
  Base b;
  b.who();

  // 此处的虚函数是通过指针调用的，呈现多态性，需要在运行时期间才能确定，所以不能为内联。
  Base *ptr = new Derived();
  ptr->who();

  // 因为Base有虚析构函数（virtual ~Base() {}），所以 delete
  // 时，会先调用派生类（Derived）析构函数，再调用基类（Base）析构函数，防止内存泄漏。
  delete ptr;
  ptr = nullptr;

  system("pause");
  return 0;
}
```

### volatile

* volatile 关键字是一种类型修饰符，用它声明的类型变量表示可以被某些编译器未知的因素（操作系统、硬件、其它线程等）更改。所以使用 volatile 告诉编译器不应对这样的对象进行读取时优化。
* volatile 关键字声明的变量，每次访问时都必须从内存中取出值（没有被 volatile 修饰的变量，可能由于编译器的优化，从 CPU 寄存器中取值），保证对特殊地址的稳定访问
* const 可以是 volatile （如只读的状态寄存器）
* 指针可以是 volatile
*  注意：

  - 可以把一个非volatile int赋给volatile int，但是不能把非volatile对象赋给一个volatile对象。
  - 除了基本类型外，对用户定义类型也可以用volatile类型进行修饰。
  - C++中一个有volatile标识符的类只能访问它接口的子集，一个由类的实现者控制的子集。用户只能用const_cast来获得对类型接口的完全访问。此外，volatile向const一样会从类传递到它的成员。

### mutable

mutable的中文意思是“可变的，易变的”，跟constant（既C++中的const）是反义词。在C++中，mutable也是为了突破const的限制而设置的。被mutable修饰的变量，将永远处于可变的状态，即使在一个const函数中。我们知道，如果类的成员函数不会改变对象的状态，那么这个成员函数一般会声明成const的。但是，有些时候，我们需要**在const函数里面修改一些跟类状态无关的数据成员，那么这个函数就应该被mutable来修饰，并且放在函数后后面关键字位置**。

### assert()

断言，是宏，而非函数。assert 宏的原型定义在 `<assert.h>`（C）、`<cassert>`（C++）中，其作用是如果它的条件返回错误，则终止程序执行。可以通过定义 `NDEBUG` 来关闭 assert，但是需要在源代码的开头，`include <assert.h>` 之前。

```cpp
#define NDEBUG          // 加上这行，则 assert 不可用
#include <assert.h>

assert( p != NULL );    // assert 不可用
```

### sizeof()

* sizeof 对数组，得到整个数组所占空间大小。
* sizeof 对指针，得到指针本身所占空间大小。

### #pragma pack(n)

`#pragma pack(n)`用来设定结构体、联合以及类成员变量以 n 字节方式对齐

```cpp
#pragma pack(push) // 保存对齐状态
#pragma pack(4)    // 设定为 4 字节对齐

struct test {
  char m1;
  double m4;
  int m3;
};

#pragma pack(pop) // 恢复对齐状态
```

### extern

* 被 extern 限定的函数或变量是 extern 类型的
* 被 `extern "C"` 修饰的变量和函数是按照 C 语言方式编译和链接的

`extern "C"` 的作用是让 C++ 编译器将 `extern "C"` 声明的代码当作 C 语言代码处理，可以避免 C++ 因符号修饰导致代码不能和C语言库中的符号进行链接的问题。

```cpp
#ifdef __cplusplus
extern "C" {
#endif

void *memset(void *, int, size_t);

#ifdef __cplusplus
}
#endif
```

### union

联合（union）是一种节省空间的特殊的类，一个 union 可以有多个数据成员，但是在任意时刻只有一个数据成员可以有值。当某个成员被赋值后其他成员变为未定义状态。联合有如下特点：

* 默认访问控制符为 public
* 可以含有构造函数、析构函数
* 不能含有引用类型的成员
* 不能继承自其他类，不能作为基类
* 不能含有虚函数
* 匿名 union 在定义所在作用域可直接访问 union 成员
* 匿名 union 不能包含 protected 成员或 private 成员
* 全局匿名联合必须是静态（static）的

```cpp
#include <iostream>

union UnionTest {
  UnionTest() : i(10){};
  int i;
  double d;
};

static union {
  int i;
  double d;
};

int main() {
  UnionTest u;

  union {
    int i;
    double d;
  };

  std::cout << u.i << std::endl; // 输出 UnionTest 联合的 10

  ::i = 20;
  std::cout << ::i << std::endl; // 输出全局静态匿名联合的 20

  i = 30;
  std::cout << i << std::endl; // 输出局部匿名联合的 30

  return 0;
}
```

### explicit

* explicit 修饰构造函数时，可以防止==隐式转换和复制初始化==
* explicit 修饰转换函数时，可以防止隐式转换，但 [按语境转换](https://zh.cppreference.com/w/cpp/language/implicit_conversion) 除外

```cpp
struct A {
  A(int) {}
  operator bool() const { return true; }
};

struct B {
  explicit B(int) {}
  explicit operator bool() const { return true; }
};

void doA(A a) {}

void doB(B b) {}

int main() {
  A a1(1);     // OK：直接初始化
  A a2 = 1;    // OK：复制初始化
  A a3{1};     // OK：直接列表初始化
  A a4 = {1};  // OK：复制列表初始化
  A a5 = (A)1; // OK：允许 static_cast 的显式转换
  doA(1);      // OK：允许从 int 到 A 的隐式转换
  if (a1)
    ;                              // OK：使用转换函数 A::operator bool() 的从 A 到 bool 的隐式转换
  bool a6(a1);                     // OK：使用转换函数 A::operator bool() 的从 A 到 bool 的隐式转换
  bool a7 = a1;                    // OK：使用转换函数 A::operator bool() 的从 A 到 bool 的隐式转换
  bool a8 = static_cast<bool>(a1); // OK ：static_cast 进行直接初始化

  B b1(1);     // OK：直接初始化
  B b2 = 1;    // 错误：被 explicit 修饰构造函数的对象不可以复制初始化
  B b3{1};     // OK：直接列表初始化
  B b4 = {1};  // 错误：被 explicit 修饰构造函数的对象不可以复制列表初始化
  B b5 = (B)1; // OK：允许 static_cast 的显式转换
  doB(1);      // 错误：被 explicit 修饰构造函数的对象不可以从 int 到 B 的隐式转换
  if (b1)
    ; // OK：被 explicit 修饰转换函数 B::operator bool() 的对象可以从 B 到 bool 的按语境转换
  bool b6(b1); // OK：被 explicit 修饰转换函数 B::operator bool() 的对象可以从 B 到 bool 的按语境转换
  bool b7 = b1; // 错误：被 explicit 修饰转换函数 B::operator bool() 的对象不可以隐式转换
  bool b8 = static_cast<bool>(b1); // OK：static_cast 进行直接初始化

  return 0;
}
```

### friend

* 能访问私有成员  
* 破坏封装性
* 友元关系不可传递
* 友元关系的单向性
* 友元声明的形式及数量不受限制

### 位域

```cpp
Bit mode: 2;    // mode 占 2 位
```

类可以将其（非静态）数据成员定义为位域（bit-field），在一个位域中含有一定数量的二进制位。当一个程序需要向其他程序或硬件设备传递二进制数据时，通常会用到位域。

* 位域在内存中的布局是与机器有关的
* 位域的类型必须是整型或枚举类型，带符号类型中的位域的行为将因具体实现而定
* 取地址运算符（&）不能作用于位域，任何指针都无法指向类的位域

### 什么情况下会调用拷贝构造函数

- 用类的一个实例化对象去初始化另一个对象的时候
- 函数的参数是类的对象时（非引用传递）
- 函数的返回值是函数体内局部对象的类的对象时 ,此时虽然发生（Named return Value优化）NRV优化，但是由于返回方式是值传递，所以会在返回值的地方调用拷贝构造函数

**另：第三种情况在Linux g++ 下则不会发生拷贝构造函数，不仅如此即使返回局部对象的引用，依然不会发生拷贝构造函数**

**总结就是：即使发生NRA优化的情况下，Linux+ g++的环境是不管值返回方式还是引用方式返回的方式都不会发生拷贝构造函数，而Windows + VS2015在值返回的情况下发生拷贝构造函数，引用返回方式则不发生拷贝构造函数**。

**在VS Code + Clang++下进行下述实验：**

```C++
#include <iostream>
using std::cout;
using std::endl;

class A {
public:
  A(){};
  A(const A &a) { cout << "copy constructor is called." << endl; };
  ~A(){};
};

void useClassA(A a) {}

A getClassA() {
  A a;
  // 此时会发生拷贝构造函数的调用，虽然发生NRV优化，但是依然调用拷贝构造函数
  return a;
}

A &getClassA2() {
  A a;
  return a;
}

int main() {
  A a1, a3, a4;
  // A a2 = a1; // 调用拷贝构造函数,对应情况1
  // useClassA(a1); // 调用拷贝构造函数，对应情况2
  // a3 = getClassA(); // clang++ Win下没有调用构造函数
  a4 = getClassA2(); // 发生NRV优化，且引用返回自身，不会调用
  return 0;
}
```

### using的使用规范

**using声明：**

一条 `using 声明` 语句一次只引入命名空间的一个成员。它使得我们可以清楚知道程序中所引用的到底是哪个名字。如：

```cpp
using namespace_name::name;
```

**构造函数的using声明：**

在 C++11 中，派生类能够重用其直接基类定义的构造函数。

```cpp
class Base {};

class Derived : Base {
public:
  using Base::Base; // 继承构造函数
};
```

如上 using 声明，对于基类的每个构造函数，编译器都生成一个与之对应（形参列表完全相同）的派生类构造函数。生成如下类型构造函数：

```cpp
Derived(parms) : Base(args) { }
```

**using指示：**

`using 指示` 使得某个特定命名空间中所有名字都可见，这样我们就无需再为它们添加任何前缀限定符了。如：

```cpp
using namespace_name name;
```

**尽量少使用 `using 指示` 污染命名空间**

> 一般说来，使用 using 声明比使用 using 编译命令更安全，这是由于它**只导入了指定的名称**。如果该名称与局部名称发生冲突，编译器将**发出指示**。using编译命令导入所有的名称，包括可能并不需要的名称。如果与局部名称发生冲突，则**局部名称将覆盖名称空间版本**，而编译器**并不会发出警告**。另外，名称空间的开放性意味着名称空间的名称可能分散在多个地方，这使得难以准确知道添加了哪些名称。

```cpp
using namespace std;	// 尽量少使用 using 指示
```

```cpp
// 应该多使用 using 声明
int x;
std::cin >> x ;
std::cout << x << std::endl;
```

```cpp
using std::cin;
using std::cout;
using std::endl;
int x;
cin >> x;
cout << x << endl;
```

### :: 范围解析运算符

1. 全局作用域符（`::name`）：用于类型名称（类、类成员、成员函数、变量等）前，表示作用域为全局命名空间
2. 类作用域符（`class::name`）：用于表示指定类型的作用域范围是具体某个类的
3. 命名空间作用域符（`namespace::name`）:用于表示指定类型的作用域范围是具体某个命名空间的

```cpp
int count = 11; // 全局（::）的 count

class A {
public:
  static int count; // 类 A 的 count（A::count）
};
int A::count = 21;

void fun() {
  int count = 31; // 初始化局部的 count 为 31
  count = 32;     // 设置局部的 count 的值为 32
}

int main() {
  ::count = 12;  // 测试 1：设置全局的 count 的值为 12
  A::count = 22; // 测试 2：设置类 A 的 count 为 22
  fun();         // 测试 3

  return 0;
}
```

### enum枚举类型

**强枚举类型**

```cpp
enum class open_modes { input, output, append };
```

**不限定作用域的枚举类型**

```cpp
enum color { red, yellow, green };
enum { floatPrec = 6, doublePrec = 10 };
```

### C++引用

**左值引用**

常规引用，一般表示对象的身份。

**右值引用**

右值引用就是必须绑定到右值（一个临时对象、将要销毁的对象）的引用，一般表示对象的值。

右值引用可实现转移语义（Move Sementics）和完美转发（Perfect Forwarding），它的主要目的有两个方面：

* 消除两个对象交互时不必要的对象拷贝，节省运算存储资源，提高效率
* 能够更简洁明确地定义泛型函数

**引用折叠**

* `X& &`、`X& &&`、`X&& &` 可折叠成 `X&`
* `X&& &&` 可折叠成 `X&&`

左值和右值的区别在于能否获取地址，左值是指表达式结束后依然存在的持久化对象，右值是指表达式结束时就不再存在的临时对象，右值又分为纯右值和将亡值

左值引用只能绑定左值，右值引用只能绑定右值，如果绑定的不对，编译就会失败。但是，**常量左值引用**却是个奇葩，它可以算是一个“万能”的引用类型，它可以绑定非常量左值、常量左值、右值，而且在绑定右值的时候，常量左值引用还可以像右值引用一样将右值的生命期延长，缺点是，只能读不能改

所谓转发，就是通过一个函数将参数继续转交给另一个函数进行处理，原参数可能是右值，可能是左值，如果还能继续保持参数的原有特征，那么它就是完美的

- 由两种值类型，左值和右值
- 有三种引用类型，左值引用、右值引用和通用引用。左值引用只能绑定左值，右值引用只能绑定右值，通用引用由初始化时绑定的值的类型确定
- 左值和右值是独立于他们的类型的，右值引用可能是左值可能是右值，如果这个右值引用已经被命名了，他就是左值
- 引用折叠规则：所有的右值引用叠加到右值引用上仍然是一个右值引用，其他引用折叠都为左值引用。当`T&&`为模板参数时，输入左值，它将变成左值引用，输入右值则变成具名的右值应用
- 移动语义可以减少无谓的内存拷贝，要想实现移动语义，需要实现移动构造函数和移动赋值函数
- `std::move()`将一个左值转换成一个右值，强制使用移动构造和赋值函数，这个函数本身并没有对这个左值什么特殊操作
- `std::forward()`和`universal references`通用引用共同实现完美转发

### 面向对象

面向对象程序设计（Object-oriented programming，OOP）是种具有对象概念的程序编程典范，同时也是一种程序开发的抽象方针。面向对象三大特征 —— 封装、继承、多态。

![](https://gitee.com/duycc/picgo/raw/master/20210311183651.png)

**封装：**

把客观事物封装成抽象的类，并且类可以把自己的数据和方法只让可信的类或者对象操作，对不可信的进行信息隐藏。关键字：public, protected, private。不写默认为 private。

* `public` 成员：可以被任意实体访问
* `protected` 成员：只允许被子类及本类的成员函数访问
* `private` 成员：只允许被本类的成员函数、友元类或友元函数访问

**继承：**

基类（父类）——&gt; 派生类（子类）

**多态：**

* 多态，即多种状态（形态）。简单来说，我们可以将多态定义为消息以多种形式显示的能力。
* 多态是以封装和继承为基础的。
* C++ 多态分类及实现：
  1. 重载多态（Ad-hoc Polymorphism，编译期）：函数重载、运算符重载
  2. 子类型多态（Subtype Polymorphism，运行期）：虚函数
  3. 参数多态性（Parametric Polymorphism，编译期）：类模板、函数模板
  4. 强制多态（Coercion Polymorphism，编译期/运行期）：基本类型转换、自定义类型转换

**静态多态（编译期/早绑定）**

函数重载，泛型编程

```cpp
class A {
public:
  void do(int a);
  void do(int a, int b);
};
```

**动态多态（运行期/晚绑定）**

* 虚函数：用 virtual 修饰成员函数，使其成为虚函数

**注意：**

* 普通函数（非类成员函数）不能是虚函数
* 静态函数（static）不能是虚函数
* 构造函数不能是虚函数（因为在调用构造函数时，虚表指针并没有在对象的内存空间中，必须要构造函数调用完成后才会形成虚表指针）
* 内联函数不能是表现多态性时的虚函数

```cpp
class Shape { // 形状类
public:
  virtual double calcArea() {}
  virtual ~Shape();
};

class Circle : public Shape { // 圆形类
public:
  virtual double calcArea();
};

class Rect : public Shape { // 矩形类
public:
  virtual double calcArea();
};

int main() {
  Shape *shape1 = new Circle();
  Shape *shape2 = new Rect();
  shape1->calcArea(); // 调用圆形类里面的方法
  shape2->calcArea(); // 调用矩形类里面的方法
  delete shape1;
  shape1 = nullptr;
  delete shape2;
  shape2 = nullptr;
  return 0;
}
```

### 什么情况会自动生成默认构造函数？

1) 带有默认构造函数的类成员对象，如果一个类没有任何构造函数，但它含有一个成员对象，而后者有默认构造函数，那么编译器就为该类合成出一个默认构造函数。不过这个合成操作只有在构造函数真正被需要的时候才会发生；如果一个类A含有多个成员类对象的话，那么类A的每一个构造函数必须调用每一个成员对象的默认构造函数而且必须按照类对象在类A中的声明顺序进行；

2) 带有默认构造函数的基类，如果一个没有默认构造函数的派生类派生自一个带有默认构造函数基类，那么该派生类会合成一个构造函数调用上一层基类的默认构造函数；

3) 带有一个虚函数的类

4) 带有一个虚基类的类

5) 合成的默认构造函数中，只有基类子对象和成员类对象会被初始化。所有其他的非静态数据成员都不会被初始化。

### 构造函数中的default和delete

default关键字可以显式要求编译器生成合成构造函数，防止在调用时相关构造函数类型没有定义而报错

```C++
#include <string>

class CString {
public:
  CString() = default; // 语句1
  CString(const char *pstr) : _str(pstr) {}
  ~CString() {}

public:
  std::string _str;
};

int main() {
  auto a = new CString(); // 没有语句一，则编译失败
  return 0;
}
```

如果没有加语句1，构造无参对象会报错，表示找不到参数为空的构造函数，将其设置为default可以解决这个问题，主要是因为当显式声明任一构造函数时，编译器便不会再生成任何默认构造函数。

delete关键字可以删除构造函数、赋值运算符函数等，这样在使用的时候会得到友善的提示

```C++
#include <iostream>
using namespace std;

class CString {
public:
  void *operator new(size_t size) = delete; // 禁止使用new关键字
  ~CString() {}
};

int main() {
  auto a = new CString(); // 语句1
  cout << "Hello World" << endl;
  return 0;
}
```

在执行语句1时，会提示new方法已经被删除，如果将new设置为私有方法，则会报惨不忍睹的错误，因此使用delete关键字可以更加人性化的删除一些默认方法

### 如何定义一个只能在堆上（栈上）生成对象的类？

**只能在堆上**

方法：将析构函数设置为私有，或者使用delete关键字显式删除析构函数

原因：C++ 是静态绑定语言，编译器管理栈上对象的生命周期，编译器在为类对象分配栈空间时，会先检查类的析构函数的访问性。若析构函数不可访问，则不能在栈上创建对象。

**只能在栈上**

方法：将 new 和 delete 重载为私有，或者用delete关键字显式删除

原因：在堆上生成对象，使用 new 关键词操作，其过程分为两阶段：第一阶段，使用 new 在堆上寻找可用内存，分配给对象；第二阶段，调用构造函数生成对象。将 new 操作设置为私有，那么第一阶段就无法完成，就不能够在堆上生成对象。

### 类成员初始化方式？构造函数的执行顺序 ？为什么用成员初始化列表会快一些？

* 赋值初始化，通过在构造函数体内进行赋值初始化
* 列表初始化，在冒号后使用初始化列表进行初始化

**这两种方式的主要区别在于：**

对于在函数体中初始化,是在所有的数据成员被分配内存空间后才进行的。

列表初始化是给数据成员分配内存空间时就进行初始化，就是说分配一个数据成员只要冒号后有此数据成员的赋值表达式(此表达式必须是括号赋值表达式)，那么分配了内存空间后在进入函数体之前给数据成员赋值，就是说初始化这个数据成员此时函数体还未执行。 

构造函数中的初始化会产生临时对象，没有列表初始化效率高。

**一个派生类构造函数的执行顺序如下：**

①   虚拟基类的构造函数（多个虚拟基类则按照继承的顺序执行构造函数）。

②   基类的构造函数（多个普通基类也按照继承的顺序执行构造函数）。

③   类类型的成员对象的构造函数（按照初始化顺序）

④   派生类自己的构造函数。

**哪几种情况必须用到初始化成员列表？**

* 当初始化一个引用成员时；

* 当初始化一个常量成员时；

* 当调用一个基类的构造函数，而它拥有一组参数时；

* 当调用一个成员类的构造函数，而它拥有一组参数时；

### public，protected和private详解

- public的变量和函数在类的内部外部都可以访问。

- protected的变量和函数只能在类的内部和其派生类中访问。

- private修饰的元素只能在类内访问。

（一）访问权限

派生类可以继承基类中除了构造/析构、赋值运算符重载函数之外的成员，但是这些成员的访问属性在派生过程中也是可以调整的，三种派生方式的访问权限如下表所示：注意外部访问并不是真正的外部访问，而是在通过派生类的对象对基类成员的访问。

![image-20210930004605165](https://gitee.com/duycc/picgo/raw/master/20210930004608.png)

派生类对基类成员的访问形象有如下两种：

- 内部访问：由派生类中新增的成员函数对从基类继承来的成员的访问
- 外部访问：在派生类外部，通过派生类的对象对从基类继承来的成员的访问

（二）继承权限

**public继承**

公有继承的特点是基类的公有成员和保护成员作为派生类的成员时，都保持原有的状态，而基类的私有成员任然是私有的，不能被这个派生类的子类所访问

**protected继承**

保护继承的特点是基类的所有公有成员和保护成员都成为派生类的保护成员，并且只能被它的派生类成员函数或友元函数访问，基类的私有成员仍然是私有的，访问规则如下表

![image-20210930004718842](https://gitee.com/duycc/picgo/raw/master/20210930004720.png)

**private继承**

私有继承的特点是基类的所有公有成员和保护成员都成为派生类的私有成员，并不被它的派生类的子类所访问，基类的成员只能由自己派生类访问，无法再往下继承，访问规则如下表

![image-20210930004838098](https://gitee.com/duycc/picgo/raw/master/20210930004839.png)

### C++的虚机制

**纯虚函数**

纯虚函数是一种特殊的虚函数，在基类中不能对虚函数给出有意义的实现，而把它声明为纯虚函数，它的实现留给该基类的派生类去做。

```cpp
virtual int A() = 0;
```

* 类里如果声明了虚函数，这个函数是实现的，哪怕是空实现，它的作用就是为了能让这个函数在它的子类里面可以被覆盖（override），这样的话，编译器就可以使用后期绑定来达到多态了。纯虚函数只是一个接口，是个函数的声明而已，它要留到子类里去实现
* 虚函数在子类里面可以不重写；但纯虚函数必须在子类实现才可以实例化子类
* 虚函数的类用于 “实作继承”，继承接口的同时也继承了父类的实现。纯虚函数关注的是接口的统一性，实现由子类完成 
* 带纯虚函数的类叫抽象类，这种类不能直接生成对象，而只有被继承，并重写其虚函数后，才能使用。抽象类被继承后，子类可以继续是抽象类，也可以是普通类

**虚继承，虚函数**

虚继承用于解决多继承条件下的菱形继承问题（浪费存储空间、存在二义性）。

底层实现原理与编译器相关，一般通过**虚基类指针**和**虚基类表**实现，每个虚继承的子类都有一个虚基类指针（占用一个指针的存储空间，4字节）和虚基类表（不占用类对象的存储空间）（需要强调的是，虚基类依旧会在子类里面存在拷贝，只是仅仅最多存在一份而已，并不是不在子类里面了）；当虚继承的子类被当做父类继承时，虚基类指针也会被继承。实际上，vbptr 指的是虚基类表指针（virtual base table pointer），该指针指向了一个虚基类表（virtual table），虚表中记录了虚基类与本类的偏移地址；通过偏移地址，这样就找到了虚基类成员，而虚继承也不用像普通多继承那样维持着公共基类（虚基类）的两份同样的拷贝，节省了存储空间。

* 相同之处：都利用了虚指针（均占用类的存储空间）和虚表（均不占用类的存储空间）
* 不同之处：
  * 虚继承
    * 虚基类依旧存在继承类中，只占用存储空间
    * 虚基类表存储的是虚基类相对直接继承类的偏移
  * 虚函数
    * 虚函数不占用存储空间
    * 虚函数表存储的是虚函数地址
* 模板类中可以使用虚函数，但虚函数本身不能是成员函数模板

**基类的虚函数表存放在内存的什么区，虚表指针vptr的初始化时间**

首先整理一下虚函数表的特征：

- 虚函数表是全局共享的元素，即全局仅有一个，在编译时就构造完成

- 虚函数表类似一个数组，类对象中存储vfptr指针，指向虚函数表，即虚函数表不是函数，不是程序代码，不可能存储在代码段

- 虚函数表存储虚函数的地址,即虚函数表的元素是指向类成员函数的指针,而类中虚函数的个数在编译时期可以确定，即虚函数表的大小可以确定,即大小是在编译时期确定的，不必动态分配内存空间存储虚函数表，所以不在堆中

根据以上特征，虚函数表类似于类中静态成员变量.静态成员变量也是全局共享，大小确定，因此最有可能存在全局数据区，测试结果显示：虚函数表vtable在Linux/Unix中存放在可执行文件的只读数据段中(rodata)，这与微软的编译器将虚函数表存放在常量段存在一些差别

由于虚表指针vptr跟虚函数密不可分，对于有虚函数或者继承于拥有虚函数的基类，对该类进行实例化时，在构造函数执行时会对虚表指针进行初始化，并且位于对象内存布局的最前面。

### 构造函数和析构函数是否可以为虚函数？

**构造函数不可以为虚函数**

虚函数的运行机制是依赖于虚函数表和虚指针的，虚函数表不属于类，是全局变量，但虚指针是类对象的一部分，在实例化一个对象时，会生成虚函数指针，且位于对象内存布局的最前面，占一个指针大小的内存。并且进行了初始化。也就是说，虚指针是在调用构造函数实例化一个对象之后才产生的，如果将构造函数声明为虚函数，那么又如何生成虚指针呢？所以构造函数不可以为虚函数。

**当存在继承关系时，析构函数需声明为虚函数**

直接的讲，C++中基类采用virtual虚析构函数是**为了防止内存泄漏。**

具体地说，如果派生类中申请了内存空间，并在其析构函数中对这些内存空间进行释放。假设基类中采用的是非虚析构函数，当删除基类指针指向的派生类对象时就不会触发动态绑定，因而只会调用基类的析构函数，而不会调用派生类的析构函数。那么在这种情况下，派生类中申请的空间就得不到释放从而产生内存泄漏。

所以，为了防止这种情况的发生，C++中基类的析构函数应采用virtual虚析构函数。

```C++
#include <iostream>
using namespace std;

class Parent {
public:
  Parent() { cout << "Parent construct function" << endl; };
  ~Parent() { cout << "Parent destructor function" << endl; }
};

class Son : public Parent {
public:
  Son() { cout << "Son construct function" << endl; };
  ~Son() { cout << "Son destructor function" << endl; }
};

int main() {
  Parent *p = new Son();
  delete p;
  p = NULL;
  return 0;
}
// Parent construct function
// Son construct function
// Parent destructor function
```

将基类的析构函数声明为虚函数：

```C++
#include <iostream>
using namespace std;

class Parent {
public:
  Parent() { cout << "Parent construct function" << endl; };
  virtual ~Parent() { cout << "Parent destructor function" << endl; }
};

class Son : public Parent {
public:
  Son() { cout << "Son construct function" << endl; };
  ~Son() { cout << "Son destructor function" << endl; }
};

int main() {
  Parent *p = new Son();
  delete p;
  p = NULL;
  return 0;
}
// Parent construct function
// Son construct function
// Son destructor function
// Parent destructor function
```

### 构造函数和析构函数可以调用虚函数吗，为什么

1) 在C++中，不提倡在构造函数和析构函数中调用虚函数；

2) 构造函数和析构函数调用虚函数时都不使用动态联编，如果在构造函数或析构函数中调用虚函数，则运行的是为构造函数或析构函数自身类型定义的版本；

3) 因为父类对象会在子类之前进行构造，此时子类部分的数据成员还未初始化，因此调用子类的虚函数时不安全的，故而C++不会进行动态联编；

4) 析构函数是用来销毁一个对象的，在销毁一个对象时，先调用子类的析构函数，然后再调用基类的析构函数。所以在调用基类的析构函数时，派生类对象的数据成员已经销毁，这个时候再调用子类的虚函数没有任何意义。

### 抽象类、接口类、聚合类

* 抽象类：含有纯虚函数的类
* 接口类：仅含有纯虚函数的抽象类
* 聚合类：用户可以直接访问其成员，并且具有特殊的初始化语法形式。满足如下特点：
  * 所有成员都是 public
  * 没有定义任何构造函数
  * 没有类内初始化
  * 没有基类，也没有 virtual 函数

### new和delete详解

**malloc、calloc、realloc、alloca**

1. malloc：申请指定字节数的内存。申请到的内存中的初始值不确定。
2. calloc：为指定长度的对象，分配能容纳其指定个数的内存。申请到的内存的每一位（bit）都初始化为 0。
3. realloc：更改以前分配的内存长度（增加或减少）。当增加长度时，可能需将以前分配区的内容移到另一个足够大的区域，而新增区域内的初始值则不确定。
4. alloca：在栈上申请内存。程序在出栈的时候，会自动释放内存。但是需要注意的是，alloca 不具可移植性, 而且在没有传统堆栈的机器上很难实现。alloca 不宜使用在必须广泛移植的程序中。C99 中支持变长数组 (VLA)，可以用来替代 alloca。

**new、delete**

1、new简单类型直接调用operator new分配内存；

而对于复杂结构，先调用operator new分配内存，然后在分配的内存上调用构造函数；

对于简单类型，new[]计算好大小后调用operator new；

对于复杂数据结构，new[]先调用operator new[]分配内存，然后在p的前四个字节写入数组大小n，然后调用n次构造函数，针对复杂类型，new[]会额外存储数组大小；

①   new表达式调用一个名为operator new(operator new[])函数，分配一块足够大的、原始的、未命名的内存空间；

②   编译器运行相应的构造函数以构造这些对象，并为其传入初始值；

③   对象被分配了空间并构造完成，返回一个指向该对象的指针。

2、 delete简单数据类型默认只是调用free函数；复杂数据类型先调用析构函数再调用operator delete；针对简单类型，delete和delete[]等同。假设指针p指向new[]分配的内存。因为要4字节存储数组大小，实际分配的内存地址为[p-4]，系统记录的也是这个地址。delete[]实际释放的就是p-4指向的内存。而delete会直接释放p指向的内存，这个内存根本没有被系统记录，所以会崩溃。

3、 需要在 new [] 一个对象数组时，需要保存数组的维度，C++ 的做法是在分配数组空间时多分配了 4 个字节的大小，专门保存数组的大小，在 delete [] 时就可以取出这个保存的数，就知道了需要调用析构函数多少次了。

```cpp
int main() {
  T *t = new T(); // 先内存分配 ，再构造函数
  delete t;       // 先析构函数，再内存释放
  return 0;
}
```

**在C++中，new有三种典型的使用方法：plain new，nothrow new和placement new**

（1）**plain new**

言下之意就是普通的new，就是我们常用的new，在C++中定义如下：

```C++
void* operator new(std::size_t) throw(std::bad_alloc);
void operator delete(void *) throw();
```

因此**plain new**在空间分配失败的情况下，抛出异常**std::bad_alloc**而不是返回NULL，因此通过判断返回值是否为NULL是徒劳的，举个例子：

```C++
int main() {
  try {
    char *p = new char[10e11];
    delete p;
  } catch (const std::bad_alloc &ex) {
    cout << ex.what() << endl;
  }
  return 0;
}
// 执行结果：bad allocation
```

（2）**nothrow new**

nothrow new在空间分配失败的情况下是不抛出异常，而是返回NULL，定义如下：

```C++
void * operator new(std::size_t,const std::nothrow_t&) throw();
void operator delete(void*) throw();
```

举个例子：

```C++
int main() {
  char *p = new (nothrow) char[10e11];
  if (p == NULL) {
    cout << "alloc failed" << endl;
  }
  delete p;
  return 0;
}
// 运行结果：alloc failed
```

（3）**placement new**

这种new允许在一块已经分配成功的内存上重新构造对象或对象数组。placement new不用担心内存分配失败，因为它根本不分配内存，它做的唯一一件事情就是调用对象的构造函数。定义如下：

```C++
void* operator new(size_t,void*);
void operator delete(void*,void*);
```

使用placement new需要注意两点：

- palcement new的主要用途就是反复使用一块较大的动态分配的内存来构造不同类型的对象或者他们的数组

- placement new构造起来的对象数组，要显式的调用他们的析构函数来销毁（析构函数并不释放对象的内存），千万不要使用delete，这是因为placement new构造起来的对象或数组大小并不一定等于原来分配的内存大小，使用delete会造成内存泄漏或者之后释放内存时出现运行时错误。

举个例子：

```C++
class ADT {
  int i;
  int j;

public:
  ADT() {
    i = 10;
    j = 100;
    cout << "ADT construct i=" << i << ", j=" << j << endl;
  }
  ~ADT() { cout << "ADT destruct" << endl; }
};
int main() {
  char *p = new (nothrow) char[sizeof(ADT) + 1];
  if (p == NULL) {
    cout << "alloc failed" << endl;
  }
  ADT *q = new (p) ADT; // placement new:不必担心失败，只要p所指对象的的空间足够ADT创建即可
  // delete q; // 错误!不能在此处调用delete q;
  q->ADT::~ADT(); // 显示调用析构函数
  delete[] p;
  return 0;
}
// 输出结果：
// ADT construct i=10j=100
// ADT destruct
```

**delete this 合法吗？**

合法，但：

1. 必须保证 this 对象是通过 `new`（不是 `new[]`、不是 placement new、不是栈上、不是全局、不是其他对象成员）分配的
2. 必须保证调用 `delete this` 的成员函数是最后一个调用 this 的成员函数
5. 析构函数中调用delete this 会导致无限递归，堆栈溢出

### C++中NULL和nullptr区别

算是为了与C语言进行兼容而定义的一个问题吧，NULL来自C语言，一般由宏定义实现，而 nullptr 则是C++11的新增关键字。**在Win平台，NULL被定义为(void*)0,而在C++语言中，NULL则被定义为整数0**。编译器一般对其实际定义如下：

```C++
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif
```


在C++中指针必须有明确的类型定义。但是将NULL定义为0带来的另一个问题是无法与整数的0区分。因为C++中允许有函数重载，所以可以试想如下函数定义情况：

```C++
void fun(char *p) { cout << "char*" << endl; }

void fun(int p) { cout << "int" << endl; }

int main() {
  fun(NULL);
  return 0;
}
// 输出结果：int
```

那么**在传入NULL参数时，会把NULL当做整数0来看，如果我们想调用参数是指针的函数，该怎么办呢?。nullptr在C++11被引入用于解决这一问题，nullptr可以明确区分整型和指针类型，能够根据环境自动转换成相应的指针类型，但不会被转换为任何整型，所以不会造成参数传递错误。**

nullptr的一种实现方式如下：

```C++
const class nullptr_t {
public:
  template <class T>
  inline operator T *() const {
    return 0;
  }
  template <class C, class T>
  inline operator T C::*() const {
    return 0;
  }

private:
  void operator&() const;
} nullptr = {};
```


以上通过模板类和运算符重载的方式来对不同类型的指针进行实例化从而解决了(void*)指针带来参数类型不明的问题，**另外由于nullptr是明确的指针类型，所以不会与整形变量相混淆。**但nullptr仍然存在一定问题，例如：

```C++
void fun(char *p) { cout << "char* p" << endl; }
void fun(int *p) { cout << "int* p" << endl; }

void fun(int p) { cout << "int p" << endl; }
int main() {
  fun((char *)nullptr); // 语句1
  fun(nullptr);         // 语句2
  fun(NULL);            // 语句3
  return 0;
}
// 语句1：char* p
// 语句2:报错，有多个匹配
// 语句3：int p
```

在这种情况下存在对不同指针类型的函数重载，此时如果传入nullptr指针则仍然存在无法区分应实际调用哪个函数，这种情况下必须显示的指明参数类型。

### 智能指针

**shared_ptr**

多个智能指针可以共享同一个对象，对象的最末一个拥有责任销毁对象，并清理与该对象相关的所有资源。

* 支持定制型删除器（custom deleter），可防范 Cross-DLL 问题（对象在动态链接库（DLL）中被 new 创建，却在另一个 DLL 内被 delete 销毁）、自动解除互斥锁

**unique_ptr**

unique_ptr 是 C++11 才开始提供的类型，是一种在异常时可以帮助避免资源泄漏的智能指针。采用独占式拥有，意味着可以确保一个对象和其相应的资源同一时间只被一个 pointer 拥有。一旦拥有者被销毁或变成empty，或开始拥有另一个对象，先前拥有的那个对象就会被销毁，其任何相应资源亦会被释放。

* unique_ptr 用于取代 auto_ptr

**weak_ptr**

weak_ptr 允许共享但不拥有某对象，一旦最末一个拥有该对象的智能指针失去了所有权，任何 weak_ptr 都会自动成空（empty）。因此，在 default 和 copy 构造函数之外，weak_ptr 只提供 “接受一个 shared_ptr” 的构造函数。

* 可打破环状引用（cycles of references，两个其实已经没有被使用的对象彼此互指，使之看似还在 “被使用” 的状态）的问题

**auto_ptr（被 C++11 弃用）**

* 被 c++11 弃用，原因是缺乏语言特性如 “针对构造和赋值” 的 `std::move` 语义，以及其他瑕疵；
* auto_ptr 可以赋值拷贝，复制拷贝后所有权转移；unqiue_ptr 无拷贝赋值语义，但实现了`move` 语义；
* auto_ptr 对象不能管理数组（析构调用 `delete`），unique_ptr 可以管理数组（析构调用 `delete[]` ）；

### C++强制类型转换

**static_cast**

* 用于非多态类型的转换
* 不执行运行时类型检查（转换安全性不如 dynamic_cast）
* 通常用于转换数值数据类型（如 float -> int）
* 可以在整个类层次结构中移动指针，子类转化为父类安全（向上转换），父类转化为子类不安全（因为子类可能有不在父类的字段或方法）

**dynamic_cast**

* 用于多态类型的转换
* 执行行运行时类型检查
* 只适用于指针或引用
* 对不明确的指针的转换将失败（返回 nullptr），但不引发异常
* 可以在整个类层次结构中移动指针，包括向上转换、向下转换

**const_cast**

* 用于删除 const、volatile 和 __unaligned 特性（如将 const int 类型转换为 int 类型 ）

**reinterpret_cast**

* 用于位的简单重新解释
* 滥用 reinterpret_cast 运算符可能很容易带来风险。 除非所需转换本身是低级别的，否则应使用其他强制转换运算符之一。
* 允许将任何指针转换为任何其他指针类型（如 `char*` 到 `int*` 或 `One_class*` 到 `Unrelated_class*` 之类的转换，但其本身并不安全）
* 也允许将任何整数类型转换为任何指针类型以及反向转换。
* reinterpret_cast 运算符不能丢掉 const、volatile 或 __unaligned 特性。 
* reinterpret_cast 的一个实际用途是在哈希函数中，即，通过让两个不同的值几乎不以相同的索引结尾的方式将值映射到索引。

### 运行时类型信息 (RTTI)

**typeid**

* typeid 运算符允许在运行时确定对象的类型
* type\_id 返回一个 type\_info 对象的引用
* 如果想通过基类的指针获得派生类的数据类型，基类必须带有虚函数
* 只能获取对象的实际类型

**typeinfo**

* type_info 类描述编译器在程序中生成的类型信息。 此类的对象可以有效存储指向类型的名称的指针。 type_info 类还可存储适合比较两个类型是否相等或比较其排列顺序的编码值。 类型的编码规则和排列顺序是未指定的，并且可能因程序而异。
* 头文件：`typeinfo`

```cpp
class Flyable {
public:
  virtual void takeoff() = 0; // 起飞
  virtual void land() = 0;    // 降落
};
class Bird : public Flyable {
public:
  void foraging() {} // 觅食
  virtual void takeoff() {}
  virtual void land() {}
  virtual ~Bird() {}
};
class Plane : public Flyable {
public:
  void carry() {} // 运输
  virtual void takeoff() {}
  virtual void land() {}
};

void doSomething(Flyable *obj) {
  obj->takeoff();

  cout << typeid(*obj).name() << endl; // 输出传入对象类型（"class Bird" or "class Plane"）

  if (typeid(*obj) == typeid(Bird)) {
    Bird *bird = dynamic_cast<Bird *>(obj); // 对象转化
    bird->foraging();
  }

  obj->land();
}

int main() {
  Bird *b = new Bird();
  doSomething(b);
  delete b;
  b = nullptr;
  return 0;
}
```

### 在main执行之前和之后执行的代码可能是什么？

**main函数执行之前**，主要就是初始化系统相关资源：

+ 设置栈指针
+ 初始化静态`static`变量和`global`全局变量，即`.data`段的内容
+ 将未初始化部分的全局变量赋初值：数值型`short`，`int`，`long`等为`0`，`bool`为`FALSE`，指针为`NULL`等等，即`.bss`段的内容     
+ 全局对象初始化，在`main`之前调用构造函数，这是可能会执行前的一些代码
+ 将main函数的参数`argc`，`argv`等传递给`main`函数，然后才真正运行`main`函数
+ __attribute__((constructor)) 

**main函数执行之后**：  

+ 全局对象的析构函数会在main函数之后执行； 
+ 可以用 **`atexit`** 注册一个函数，它会在main 之后执行;
+ __attribute__((destructor)) 

### C和C++的类型安全

 **什么是类型安全？**

类型安全很大程度上可以等价于内存安全，类型安全的代码不会试图访问自己没被授权的内存区域。“类型安全”常被用来形容编程语言，其根据在于该门编程语言是否提供保障类型安全的机制；有的时候也用“类型安全”形容某个程序，判别的标准在于该程序是否隐含类型错误。类型安全的编程语言与类型安全的程序之间，没有必然联系。好的程序员可以使用类型不那么安全的语言写出类型相当安全的程序，相反的，差一点儿的程序员可能使用类型相当安全的语言写出类型不太安全的程序。绝对类型安全的编程语言暂时还没有。

**（1）C的类型安全**

C只在局部上下文中表现出类型安全，比如试图从一种结构体的指针转换成另一种结构体的指针时，编译器将会报告错误，除非使用显式类型转换。然而，C中相当多的操作是不安全的。以下是两个十分常见的例子：

- printf格式输出

  ```c
  #include <stdio.h>
  
  int main() {
    printf("out: %f\n", 10);
  
    return 0;
  }
  // out: 0.000000
  ```

上述代码中，使用%d控制整型数字的输出，没有问题，但是改成%f时，明显输出错误，再改成%s时，运行直接报segmentation fault错误

- malloc函数的返回值

malloc是C中进行内存分配的函数，它的返回类型是void\*即空类型指针，常常有这样的用法char\* pStr=(char\*)malloc(100\*sizeof(char))，这里明显做了显式的类型转换。类型匹配尚且没有问题，但是一旦出现int\* pInt=(int*)malloc(100\*sizeof(char))就很可能带来一些问题，而这样的转换C并不会提示错误。

**（2）C++的类型安全**

如果C++使用得当，它将远比C更有类型安全性。相比于C语言，C++提供了一些新的机制保障类型安全：

- 操作符new返回的指针类型严格与对象匹配，而不是void\*

- C中很多以void\*为参数的函数可以改写为C++模板函数，而模板是支持类型检查的；

- 引入const关键字代替#define constants，它是有类型、有作用域的，而#define constants只是简单的文本替换

- 一些#define宏可被改写为inline函数，结合函数的重载，可在类型安全的前提下支持多种类型，当然改写为模板也能保证类型安全

- C++提供了**dynamic_cast**关键字，使得转换过程更加安全，因为dynamic_cast比static_cast涉及更多具体的类型检查。

  例1：使用void\*进行类型转换

  ```cpp
  #include <iostream>
  #include <cstdio>
  
  int main() {
    int a = 5;
    std::cout << "int a = " << a << std::endl;
  
    int *p = &a;
    std::cout << "double a = " << *(double *)p << std::endl;
  
    return 0;
  }
  /*
  int a = 5
  double a = -2.78587e+117
  */
  ```
  
  例2：不同类型指针之间转换
  
  ```cpp
  #include <iostream>
  using namespace std;
  
  class Parent {};
  class Child1 : public Parent {
  public:
    int i;
    Child1(int e) : i(e) {}
  };
  class Child2 : public Parent {
  public:
    double d;
    Child2(double e) : d(e) {}
  };
  int main() {
    Child1 c1(5);
    Child2 c2(4.1);
    Parent *pp;
    Child1 *pc1;
  
    pp = &c1;
    pc1 = (Child1 *)pp;     // 类型向下转换 强制转换，由于类型仍然为Child1*，不造成错误
    cout << pc1->i << endl; // 输出：5
  
    pp = &c2;
    pc1 = (Child1 *)pp;     // 强制转换，且类型发生变化，将造成错误
    cout << pc1->i << endl; // 输出：1717986918
    return 0;
  }
  ```

上面两个例子之所以引起类型不安全的问题，是因为程序员使用不得当。第一个例子用到了空类型指针void\*，第二个例子则是在两个类型指针之间进行强制转换。因此，想保证程序的类型安全性，应尽量避免使用空类型指针void\*，尽量不对两种类型指针做强制转换。

***

## 二、C++2.0

***

### C++左值，右值，左值引用和右值引用

**左值和右值**

左值：表示的是可以获取地址的表达式，它能出现在赋值语句的左边，对该表达式进行赋值。但是修饰符const的出现使得可以声明如下的标识符，它可以取得地址，但是没办法对其进行赋值

```C++
const int& a = 10;
```

右值：表示无法获取地址的对象，有常量值、函数返回值、lambda表达式等。无法获取地址，但不表示其不可改变，当定义了右值的右值引用时就可以更改右值。

**左值引用，右值引用**

C++11正是通过引入右值引用来优化性能，具体来说是通过移动语义来避免无谓拷贝的问题，通过move语义来将临时生成的左值中的资源无代价的转移到另外一个对象中去，通过完美转发来解决不能按照参数实际类型来转发的问题（同时，完美转发获得的一个好处是可以实现移动语义）。 

1)  在C++11中所有的值必属于左值、右值两者之一，右值又可以细分为纯右值、将亡值。在C++11中可以取地址的、有名字的就是左值，反之，不能取地址的、没有名字的就是右值（将亡值或纯右值）。举个例子，int a = b+c, a 就是左值，其有变量名为a，通过&a可以获取该变量的地址；表达式b+c、函数int func()的返回值是右值，在其被赋值给某一变量前，我们不能通过变量名找到它，＆(b+c)这样的操作则不会通过编译。

2)  C++11对C++98中的右值进行了扩充。在C++11中右值又分为纯右值（prvalue，Pure Rvalue）和将亡值（xvalue，eXpiring Value）。其中纯右值的概念等同于我们在C++98标准中右值的概念，指的是临时变量和不跟对象关联的字面量值；将亡值则是C++11新增的跟右值引用相关的表达式，这样表达式通常是将要被移动的对象（移为他用），比如返回右值引用T&&的函数返回值、std::move的返回值，或者转换为T&&的类型转换函数的返回值。将亡值可以理解为通过“盗取”其他变量内存空间的方式获取到的值。在确保其他变量不再被使用、或即将被销毁时，通过“盗取”的方式可以避免内存空间的释放和分配，能够延长变量值的生命期。

3)  左值引用就是对一个左值进行引用的类型。右值引用就是对一个右值进行引用的类型，事实上，由于右值通常不具有名字，我们也只能通过引用的方式找到它的存在。右值引用和左值引用都是属于引用类型。无论是声明一个左值引用还是右值引用，都必须立即进行初始化。而其原因可以理解为是引用类型本身自己并不拥有所绑定对象的内存，只是该对象的一个别名。左值引用是具名变量值的别名，而右值引用则是不具名（匿名）变量的别名。左值引用通常也不能绑定到右值，但常量左值引用是个“万能”的引用类型。它可以接受非常量左值、常量左值、右值对其进行初始化。不过常量左值所引用的右值在它的“余生”中只能是只读的。相对地，非常量左值引用只能接受非常量左值对其进行初始化。

4)  右值值引用通常不能绑定到任何的左值，要想绑定一个左值到右值引用，通常需要std::move()将左值强制转换为右值。

**这里主要说一下右值引用的特点：**

- 特点1：通过右值引用的声明，右值又“重获新生”，其生命周期与右值引用类型变量的生命周期一样长，只要该变量还活着，该右值临时量将会一直存活下去
- 特点2：右值引用独立于左值和右值。意思是右值引用类型的变量可能是左值也可能是右值
- 特点3：T&& t在发生自动类型推断的时候，它是左值还是右值取决于它的初始化。

举个例子：

```C++
template <typename T>
void fun(T &&t) {
  cout << t << endl;
}

int getInt() { return 5; }

int main() {
  int a = 10;
  int &b = a;         // b是左值引用
  int &c = 10;        // 错误，c是左值不能使用右值初始化
  int &&d = 10;       // 正确，右值引用用右值初始化
  int &&e = a;        // 错误，e是右值引用不能使用左值初始化
  const int &f = a;   // 正确，左值常引用相当于是万能型，可以用左值或者右值初始化
  const int &g = 10;  // 正确，左值常引用相当于是万能型，可以用左值或者右值初始化
  const int &&h = 10; // 正确，右值常引用
  const int &aa = h;  // 正确
  int &i = getInt();  // 错误，i是左值引用不能使用临时变量（右值）初始化
  int &&j = getInt(); // 正确，函数返回值是右值
  fun(10);            // 此时fun函数的参数t是右值
  fun(a);             // 此时fun函数的参数t是左值
  return 0;
}
```

### auto、decltype和decltype(auto)的用法

**（1）auto**

C++11新标准引入了auto类型说明符，用它就能让编译器替我们去分析表达式所属的类型。和原来那些只对应某种特定的类型说明符(例如 int)不同，**auto 让编译器通过初始值来进行类型推演。从而获得定义变量的类型，所以说 auto 定义的变量必须有初始值。**举个例子：

```c++
// 普通；类型
int a = 1, b = 3;
auto c = a + b; // c为int型

// const类型
const int i = 5;
auto j = i;       // 变量i是顶层const, 会被忽略, 所以j的类型是int
auto k = &i;      // 变量i是一个常量, 对常量取地址是一种底层const, 所以 k 的类型是const int*
const auto l = i; // 如果希望推断出的类型是顶层const的, 那么就需要在auto前面加上const

// 引用和指针类型
int x = 2;
int &y = x;
auto z = y;   // z是int型不是int& 型
auto &p1 = y; // p1是int&型
auto p2 = &x; // p2是指针类型int*
```

**（2）decltype**

decltype 关键字用于检查实体的声明类型或表达式的类型及值分类。语法：

```cpp
decltype ( expression )
```

```cpp
// 尾置返回允许我们在参数列表之后声明返回类型
template <typename It>
auto fcn(It beg, It end) -> decltype(*beg) {
  // 处理序列
  return *beg; // 返回序列中一个元素的引用
}
// 为了使用模板参数成员，必须用 typename
template <typename It>
auto fcn2(It beg, It end) -> typename remove_reference<decltype(*beg)>::type {
  // 处理序列
  return *beg; // 返回序列中一个元素的拷贝
}
```

有的时候我们还会遇到这种情况，**我们希望从表达式中推断出要定义变量的类型，但却不想用表达式的值去初始化变量。**还有可能是函数的返回类型为某表达式的值类型。在这些时候auto显得就无力了，所以C++11又引入了第二种类型说明符decltype，**它的作用是选择并返回操作数的数据类型。在此过程中，编译器只是分析表达式并得到它的类型，却不进行实际的计算表达式的值。**

```C++
int func(){return 0};

//普通类型
decltype(func()) sum = 5; // sum的类型是函数func()的返回值的类型int, 但是这时不会实际调用函数func()
int a = 0;
decltype(a) b = 4; // a的类型是int, 所以b的类型也是int

// 不论是顶层const还是底层const, decltype都会保留
const int c = 3;
decltype(c) d = c; // d的类型和c是一样的, 都是顶层const
int e = 4;
const int *f = &e; // f是底层const
decltype(f) g = f; // g也是底层const

// 引用与指针类型
// 1. 如果表达式是引用类型, 那么decltype的类型也是引用
const int i = 3, &j = i;
decltype(j) k = 5; // k的类型是 const int&

// 2. 如果表达式是引用类型, 但是想要得到这个引用所指向的类型, 需要修改表达式:
int i = 3, &r = i;
decltype(r + 0) t = 5; // 此时是int类型

// 3. 对指针的解引用操作返回的是引用类型
int i = 3, j = 6, *p = &i;
decltype(*p) c = j; // c是int&类型, c和j绑定在一起

// 4. 如果一个表达式的类型不是引用, 但是我们需要推断出引用, 那么可以加上一对括号, 就变成了引用类型了
int i = 3;
decltype((i)) j = i; // 此时j的类型是int&类型, j和i绑定在了一起
```

**（3）decltype(auto)**

decltype(auto)是C++14新增的类型指示符，可以用来声明变量以及指示函数返回类型。在使用时，会将“=”号右边的表达式替换掉auto，再根据decltype的语法规则来确定类型。举个例子：

```cpp
int e = 4;
const int *f = &e;    // f是底层const
decltype(auto) j = f; // j的类型是const int* 并且指向的是e
```

### 模板函数和模板特化

**引入原因**

编写单一的模板，它能适应多种类型的需求，使每种类型都具有相同的功能，但对于某种特定类型，如果要实现其特有的功能，单一模板就无法做到，这时就需要模板特例化

**定义**

对单一模板提供的一个特殊实例，它将一个或多个模板参数绑定到特定的类型或值上

**（1）模板函数特例化**

必须为原函数模板的每个模板参数都提供实参，且使用关键字template后跟一个空尖括号对<>，表明将原模板的所有模板参数提供实参，举例如下：

```C++
template <typename T> // 模板函数
int compare(const T &v1, const T &v2) {
  if (v1 > v2)
    return -1;
  if (v2 > v1)
    return 1;
  return 0;
}
// 模板特例化,满足针对字符串特定的比较，要提供所有实参，这里只有一个T
template <>
int compare(const char *const &v1, const char *const &v2) {
  return strcmp(p1, p2);
}
```

**本质**

特例化的本质是实例化一个模板，而非重载它。特例化不影响参数匹配。参数匹配都以最佳匹配为原则。例如，此处如果是compare(3,5)，则调用普通的模板，若为compare(“hi”,”haha”)则调用**特例化版本**（因为这个cosnt char*相对于T，更匹配实参类型），注意二者函数体的语句不一样了，实现不同功能。

**注意**

模板及其特例化版本应该声明在同一个头文件中，且所有同名模板的声明应该放在前面，后面放特例化版本。

**（2）类模板特例化**

原理类似函数模板，**不过在类中，我们可以对模板进行特例化，也可以对类进行部分特例化。**对类进行特例化时，仍然用template<>表示是一个特例化版本，例如：

```C++
template <>
class hash<sales_data> {
  size_t operator()(sales_data &s);
  // 里面所有T都换成特例化类型版本sales_data
  // 按照最佳匹配原则，若T != sales_data，就用普通类模板，否则，就使用含有特定功能的特例化版本。
};
```

**类模板的部分特例化**

不必为所有模板参数提供实参，可以**指定一部分而非所有模板参数**，一个类模板的部分特例化本身仍是一个模板，使用它时还必须为其特例化版本中未指定的模板参数提供实参(特例化时类名一定要和原来的模板相同，只是参数类型不同，按最佳匹配原则，哪个最匹配，就用相应的模板)

**可以特例化类中的部分成员函数而不是整个类**，举个例子：

```C++
template <typename T>
class Foo {
  void Bar();
  void Barst(T a)();
};

template <>
void Foo<int>::Bar() {
  // 进行int类型的特例化处理
  cout << "我是int型特例化" << endl;
}

Foo<string> fs;
Foo<int> fi; // 使用特例化
fs.Bar();    // 使用的是普通模板，即Foo<string>::Bar()
fi.Bar();    // 特例化版本，执行Foo<int>::Bar()
// Foo<string>::Bar()和Foo<int>::Bar()功能不同
```

***

## 三、[STL](STL)

***

### [STL 使用索引](STL/STL.md)

### STL 容器

|        容器        |  底层数据结构  |                          时间复杂度                          | 是否有序 | 是否重复 |                             其它                             |
| :----------------: | :------------: | :----------------------------------------------------------: | :------: | :------: | :----------------------------------------------------------: |
|       array        |      数组      |                       随机读写<br>O(1)                       |   无序   |  可重复  |                         支持随机访问                         |
|       vector       |      数组      | 随机读写<br>尾部插入<br>尾部删除<br>O(1)<br>头部插入<br>头部删除<br>O(n) |   无序   |  可重复  |                         支持随机访问                         |
|       deque        |    双端队列    |                 头尾插入<br>头尾删除<br>O(1)                 |   无序   |  可重复  | 一个中央控制器<br>多个缓冲区<br>支持首尾快速增删<br>支持随机访问 |
|    forward_list    |    单向链表    |                      插入，删除<br>O(1)                      |   无序   |  可重复  |                        不支持随机访问                        |
|        list        |    双向链表    |                      插入，删除<br>O(1)                      |   无序   |  可重复  |                        不支持随机访问                        |
|       stack        |  deque、list   |                 顶部插入<br>顶部删除<br>O(1)                 |   无序   |  可重复  |                      vector扩容耗时不用                      |
|       queue        |  deque、list   |                       头删尾插<br>O(1)                       |   无序   |  可重复  |                      vector扩容耗时不用                      |
|   priority_queue   | vector+max-map |                     插入删除<br>O(logn)                      |   有序   |  可重复  |                       vector+heap处理                        |
|        set         |     红黑树     |                   插入删除<br>查找O(logn)                    |   有序   | 不可重复 |                                                              |
|      multiset      |     红黑树     |                              -                               |   有序   |  可重复  |                                                              |
|        map         |     红黑树     |                              -                               |   有序   | 不可重复 |                                                              |
|      multimap      |     红黑树     |                              -                               |   有序   |  可重复  |                                                              |
|   unordered_set    |     哈希表     |                       O(1)<br>最差O(n)                       |   无序   | 不可重复 |                                                              |
| unordered_multiset |     哈希表     |                              -                               |   无序   |  可重复  |                                                              |
|   unordered_map    |     哈希表     |                              -                               |   无序   | 不可重复 |                                                              |
|  undered_multimap  |     哈希表     |                              -                               |   无序   |  可重复  |                                                              |

### [STL容器实现细节](STL/README.md)

### STL中hashtable的实现？

STL中的hashtable使用的是**开链法**解决hash冲突问题，如下图所示。

![](https://gitee.com/duycc/picgo/raw/master/20210331191638.png)

hashtable中的bucket所维护的list既不是list也不是slist，而是其自己定义的由hashtable_node数据结构组成的linked-list，而bucket聚合体本身使用vector进行存储。hashtable的迭代器只提供前进操作，不提供后退操作

在hashtable设计bucket的数量上，其内置了28个质数[53, 97, 193,...,429496729]，在创建hashtable时，会根据存入的元素个数选择大于等于元素个数的质数作为hashtable的容量（vector的长度），其中每个bucket所维护的linked-list长度也等于hashtable的容量。如果插入hashtable的元素个数超过了bucket的容量，就要进行重建table操作，即找出下一个质数，创建新的buckets vector，重新计算元素在新hashtable的位置。

### 简单说一下STL中的traits技法

traits技法利用“内嵌型别“的编程技巧与**编译器的template参数推导功能**，增强C++未能提供的关于型别认证方面的能力。常用的有iterator_traits和type_traits。

**iterator_traits**

被称为**特性萃取机**，能够方面的让外界获取以下5中型别：

- value_type：迭代器所指对象的型别
- difference_type：两个迭代器之间的距离
- pointer：迭代器所指向的型别
- reference：迭代器所引用的型别
- iterator_category：三两句说不清楚，建议看书

**type_traits**

关注的是型别的**特性**，例如这个型别是否具备non-trivial defalt ctor（默认构造函数）、non-trivial copy ctor（拷贝构造函数）、non-trivial assignment operator（赋值运算符） 和non-trivial dtor（析构函数），如果答案是否定的，可以采取直接操作内存的方式提高效率，一般来说，type_traits支持以下5中类型的判断：

```c++
__type_traits<T>::has_trivial_default_constructor
__type_traits<T>::has_trivial_copy_constructor
__type_traits<T>::has_trivial_assignment_operator
__type_traits<T>::has_trivial_destructor
__type_traits<T>::is_POD_type
```

由于编译器只针对class object形式的参数进行参数推导，因此上式的返回结果不应该是个bool值，实际上使用的是一种空的结构体：

```C++
struct __true_type{};
struct __false_type{};
```

这两个结构体没有任何成员，不会带来其他的负担，又能满足需求，可谓一举两得

当然，如果我们自行定义了一个Shape类型，也可以针对这个Shape设计type_traits的特化版本

```C++
template<> struct __type_traits<Shape>{
	typedef __true_type has_trivial_default_constructor;
	typedef __false_type has_trivial_copy_constructor;
	typedef __false_type has_trivial_assignment_operator;
	typedef __false_type has_trivial_destructor;
	typedef __false_type is_POD_type;
};
```

### STL的两级空间配置器

我们知道动态开辟内存时，要在堆上申请，但若是我们需要频繁的在堆开辟释放内存，则就会**在堆上造成很多外部碎片**，浪费了内存空间；每次都要进行调用**malloc、free**函数等操作，使空间就会增加一些附加信息，降低了空间利用率；随着外部碎片增多，内存分配器在找不到合适内存情况下需要合并空闲块，浪费了时间，大大降低了效率。于是就设置了二级空间配置器，**当开辟内存<=128bytes时，即视为开辟小块内存，则调用二级空间配置器。**关于STL中一级空间配置器和二级空间配置器的选择上，一般默认**选择的为二级空间配置器**。 如果大于128字节再转去一级配置器器。

##### 一级配置器

 **一级空间配置器**中重要的函数就是allocate、deallocate、reallocate 。 一级空间配置器是以malloc()，free()，realloc()等C函数执行实际的内存配置 。大致过程是：

1、直接allocate分配内存，其实就是malloc来分配内存，成功则直接返回，失败就调用处理函数

2、如果用户自定义了内存分配失败的处理函数就调用，没有的话就返回异常

3、如果自定义了处理函数就进行处理，完事再继续分配试试

![](https://gitee.com/duycc/picgo/raw/master/20210331191747.png)



##### 二级配置器

![](https://gitee.com/duycc/picgo/raw/master/20210331191757.png)



1、维护16条链表，分别是0-15号链表，最小8字节，以8字节逐渐递增，最大128字节，你传入一个字节参数，表示你需要多大的内存，会自动帮你校对到第几号链表（如需要13bytes空间，我们会给它分配16bytes大小），在找到第你个链表后查看链表是否为空，如果不为空直接从对应的free_list中拔出，将已经拨出的指针向后移动一位。

2、对应的free_list为空，先看其内存池是不是空时，如果内存池不为空：
（1）先检验它剩余空间是否够20个节点大小（即所需内存大小(提升后) * 20），若足够则直接从内存池中拿出20个节点大小空间，将其中一个分配给用户使用，另外19个当作自由链表中的区块挂在相应的free_list下，这样下次再有相同大小的内存需求时，可直接拨出。
（2）如果不够20个节点大小，则看它是否能满足1个节点大小，如果够的话则直接拿出一个分配给用户，然后从剩余的空间中分配尽可能多的节点挂在相应的free_list中。
（3）如果连一个节点内存都不能满足的话，则将内存池中剩余的空间挂在相应的free_list中（找到相应的free_list），然后再给内存池申请内存，转到3。
3、内存池为空，申请内存
此时二级空间配置器会使用malloc()从heap上申请内存，（一次所申请的内存大小为2 * 所需节点内存大小（提升后）* 20 + 一段额外空间），申请40块，一半拿来用，一半放内存池中。
4、malloc没有成功
在第三种情况下，如果malloc()失败了，说明heap上没有足够空间分配给我们了，这时，二级空间配置器会从比所需节点空间大的free_list中一一搜索，从比它所需节点空间大的free_list中拔除一个节点来使用。如果这也没找到，说明比其大的free_list中都没有自由区块了，那就要调用一级适配器了。

释放时调用deallocate()函数，若释放的n>128，则调用一级空间配置器，否则就直接将内存块挂上自由链表的合适位置。

STL二级空间配置器虽然解决了外部碎片与提高了效率，但它同时增加了一些缺点：

1.因为自由链表的管理问题，它会把我们需求的内存块自动提升为8的倍数，这时若你需要1个字节，它会给你8个字节，即浪费了7个字节，所以它又引入了内部碎片的问题，若相似情况出现很多次，就会造成很多内部碎片；

2.二级空间配置器是在堆上申请大块的狭义内存池，然后用自由链表管理，供现在使用，在程序执行过程中，它将申请的内存一块一块都挂在自由链表上，即不会还给操作系统，并且它的实现中所有成员全是静态的，所以它申请的所有内存只有在进程结束才会释放内存，还给操作系统，由此带来的问题有：1.即我不断的开辟小块内存，最后整个堆上的空间都被挂在自由链表上，若我想开辟大块内存就会失败；2.若自由链表上挂很多内存块没有被使用，当前进程又占着内存不释放，这时别的进程在堆上申请不到空间，也不可以使用当前进程的空闲内存，由此就会引发多种问题。

### vector与list的区别与应用？

* vector和数组类似，拥有一段连续的内存空间，并且起始地址不变。因此能高效的进行随机存取，时间复杂度为o(1);但因为内存空间是连续的，所以在进行插入和删除操作时，会造成内存块的拷贝，时间复杂度为o(n)。另外，当数组中内存空间不够时，会重新申请一块内存空间并进行内存拷贝。连续存储结构：vector是可以实现动态增长的对象数组，支持对数组高效率的访问和在数组尾端的删除和插入操作，在中间和头部删除和插入相对不易，需要挪动大量的数据。它与数组最大的区别就是vector不需程序员自己去考虑容量问题，库里面本身已经实现了容量的动态增长，而数组需要程序员手动写入扩容函数进形扩容。
* list是由双向链表实现的，因此内存空间是不连续的。只能通过指针访问数据，所以list的随机存取非常没有效率，时间复杂度为o(n);但由于链表的特点，能高效地进行插入和删除。非连续存储结构：list是一个双链表结构，支持对链表的双向遍历。每个节点包括三个信息：元素本身，指向前一个元素的节点（prev）和指向下一个元素的节点（next）。因此list可以高效率的对数据元素任意位置进行访问和插入删除等操作。由于涉及对额外指针的维护，所以开销比较大。 

### STL 中vector删除其中的元素，迭代器如何变化？为什么是两倍扩容？释放空间？

size()函数返回的是已用空间大小，capacity()返回的是总空间大小，capacity()-size()则是剩余的可用空间大小。当size()和capacity()相等，说明vector目前的空间已被用完，如果再添加新元素，则会引起vector空间的动态增长。由于动态增长会引起重新分配内存空间、拷贝原空间、释放原空间，这些过程会降低程序效率。因此，可以使用reserve(n)预先分配一块较大的指定大小的内存空间，这样当指定大小的内存空间未使用完时，是不会重新分配内存空间的，这样便提升了效率。只有当n>capacity()时，调用reserve(n)才会改变vector容量。 resize()成员函数只改变元素的数目，不改变vector的容量。

- 空的vector对象，size()和capacity()都为0

- 当空间大小不足时，新分配的空间大小为原空间大小的2倍。

- 使用reserve()预先分配一块内存后，在空间未满的情况下，不会引起重新分配，从而提升了效率。

- 当reserve()分配的空间比原空间小时，是不会引起重新分配的。

- resize()函数只改变容器的元素数目，未改变容器大小。

- 用reserve(size_type)只是扩大capacity值，这些内存空间可能还是“野”的，如果此时使用“[ ]”来访问，则可能会越界。而resize(size_type new_size)会真正使容器具有new_size个对象。

**扩容机制：**

 不同的编译器，vector有不同的扩容大小。在vs下是1.5倍，在GCC下是2倍；

空间和时间的权衡。简单来说， 空间分配的多，平摊时间复杂度低，但浪费空间也多。使用k=2增长因子的问题在于，每次扩展的新尺寸必然刚好大于之前分配的总和，也就是说，之前分配的内存空间不可能被使用。这样对内存不友好。最好把增长因子设为(1,2)

 对比可以发现采用采用成倍方式扩容，可以保证常数的时间复杂度，而增加指定大小的容量只能达到O(n)的时间复杂度，因此，使用成倍的方式扩容。

**如何释放空间：**

由于vector的内存占用空间只增不减，比如你首先分配了10,000个字节，然后erase掉后面9,999个，留下一个有效元素，但是内存占用仍为10,000个。所有内存空间是在vector析构时候才能被系统回收。empty()用来检测容器是否为空的，clear()可以清空所有元素。但是即使clear()，vector所占用的内存空间依然如故，无法保证内存的回收。

如果需要空间动态缩小，可以考虑使用deque。如果vector，可以用swap()来帮助你释放内存。

~~~cpp
vector(Vec).swap(Vec); // 将Vec的内存空洞清除
vector().swap(Vec);    // 清空Vec的内存
~~~

### STL迭代器如何实现

1. 迭代器是一种抽象的设计理念，通过迭代器可以在不了解容器内部原理的情况下遍历容器，除此之外，STL中迭代器一个最重要的作用就是作为容器与STL算法的粘合剂。

2. 迭代器的作用就是提供一个遍历容器内部所有元素的接口，因此迭代器内部必须保存一个与容器相关联的指针，然后重载各种运算操作来遍历，其中最重要的是*运算符与->运算符，以及++、--等可能需要重载的运算符重载。这和C++中的智能指针很像，智能指针也是将一个指针封装，然后通过引用计数或是其他方法完成自动释放内存的功能。

3. 最常用的迭代器的相应型别有五种：value type、difference type、pointer、reference、iterator catagoly;


### STL中unordered_map和map的区别

- unordered_map和map类似，都是存储的key-value的值，可以通过key快速索引到value。不同的是unordered_map不会根据key的大小进行排序，
- 存储时是根据key的hash值判断元素是否相同，即unordered_map内部元素是无序的，而map中的元素是按照二叉搜索树存储，进行中序遍历会得到有序遍历。
- 所以使用时map的key需要定义operator<。而unordered_map需要定义hash_value函数并且重载operator==。但是很多系统内置的数据类型都自带这些，
- 那么如果是自定义类型，那么就需要自己重载operator<或者hash_value()了。
- 如果需要内部元素自动排序，使用map，不需要排序使用unordered_map
- unordered_map的底层实现是hash_table;
- hash_map底层使用的是hash_table，而hash_table使用的开链法进行冲突避免，所有hash_map采用开链法进行冲突解决。

**什么时候扩容：**当向容器添加元素的时候，会判断当前容器的元素个数，如果大于等于阈值，即当前数组的长度乘以加载因子的值的时候，就要自动扩容。

### map中[]与find的区别？

1) map的下标运算符[]的作用是：将关键码作为下标去执行查找，并返回对应的值；如果不存在这个关键码，就将一个具有该关键码和值类型的默认值的项插入这个map。

2) map的find函数：用关键码执行查找，找到了返回该位置的迭代器；如果不存在这个关键码，就返回尾迭代器。

### STL每种容器对应的迭代器

| 容器                                   | 迭代器         |
| -------------------------------------- | -------------- |
| vector、deque                          | 随机访问迭代器 |
| stack、queue、priority_queue           | 无             |
| list、(multi)set/map                   | 双向迭代器     |
| unordered_(multi)set/map、forward_list | 前向迭代器     |


***

## 四、C++程序内存模型

***

### 内存分区，堆，栈

C++中的内存分区，分别是堆、栈、自由存储区、全局/静态存储区、常量存储区和代码区。如下图所示：

![image-20211001081139555](https://gitee.com/duycc/picgo/raw/master/20211001081141.png)

**栈**：在执行函数时，函数内局部变量的存储单元都可以在栈上创建，函数执行结束时这些存储单元自动被释放。栈内存分配运算内置于处理器的指令集中，效率很高，但是分配的内存容量有限

**堆**：就是那些由 `new`分配的内存块，他们的释放编译器不去管，由我们的应用程序去控制，一般一个`new`就要对应一个 `delete`。如果程序员没有释放掉，那么在程序结束后，操作系统会自动回收

**自由存储区**：就是那些由`malloc`等分配的内存块，它和堆是十分相似的，不过它是用`free`来结束自己的生命的

**全局/静态存储区**：全局变量和静态变量被分配到同一块内存中，在以前的C语言中，全局变量和静态变量又分为初始化的和未初始化的，在C++里面没有这个区分了，它们共同占用同一块内存区，在该区定义的变量若没有初始化，则会被自动初始化，例如int型变量自动初始为0

**常量存储区**：这是一块比较特殊的存储区，这里面存放的是常量，不允许修改

**代码区**：存放函数体的二进制代码

**区别：**

- 申请方式不同。

  - 栈由系统自动分配。

- 堆是自己申请和释放的。

- 申请大小限制不同。

  - 栈顶和栈底是之前预设好的，栈是向栈底扩展，大小固定，可以通过ulimit -a查看，由ulimit -s修改。

  - 堆向高地址扩展，是不连续的内存区域，大小可以灵活调整。

- 申请效率不同。

  - 栈由系统分配，速度快，不会有碎片。

  - 堆由程序员分配，速度慢，且会有碎片。


   栈空间默认是4M, 堆区一般是 1G - 4G 

|                  | 堆                                                           | 栈                                                           |
| :--------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| **管理方式**     | 堆中资源由程序员控制（容易产生memory leak）                  | 栈资源由编译器自动管理，无需手工控制                         |
| **内存管理机制** | 系统有一个记录空闲内存地址的链表，当系统收到程序申请时，遍历该链表，寻找第一个空间大于申请空间的堆结点，删除空闲结点链表中的该结点，并将该结点空间分配给程序（大多数系统会在这块内存空间首地址记录本次分配的大小，这样delete才能正确释放本内存空间，另外系统会将多余的部分重新放入空闲链表中） | 只要栈的剩余空间大于所申请空间，系统为程序提供内存，否则报异常提示栈溢出。 |
| **空间大小**     | 堆是不连续的内存区域（因为系统是用链表来存储空闲内存地址，自然不是连续的），堆大小受限于计算机系统中有效的虚拟内存（32bit  系统理论上是4G），所以堆的空间比较灵活，比较大 | 栈是一块连续的内存区域，大小是操作系统预定好的，windows下栈大小是2M（也有是1M，在  编译时确定，VC中可设置） |
| **碎片问题**     | 对于堆，频繁的new/delete会造成大量碎片，使程序效率降低       | 对于栈，它是有点类似于数据结构上的一个先进后出的栈，进出一一对应，不会产生碎片。 |
| **生长方向**     | 堆向上，向高地址方向增长。                                   | 栈向下，向低地址方向增长。                                   |
| **分配方式**     | 堆都是动态分配（没有静态分配的堆）                           | 栈有静态分配和动态分配，静态分配由编译器完成（如局部变量分配），动态分配由malloc函数分配，但栈的动态分配的资源由编译器进行释放，无需程序员实现。 |
| **分配效率**     | 堆由C/C++函数库提供，机制很复杂。所以堆的效率比栈低很多。    | 栈是其系统提供的数据结构，计算机在底层对栈提供支持，分配专门寄存器存放栈地址，栈操作有专门指令。 |

**“段错误（segment fault）” 或 “非法操作，该内存地址不能 read/write”**

典型的非法指针解引用造成的错误。当指针指向一个不允许读写的内存地址，而程序却试图利用指针来读或写该地址时，会出现这个错误。例如：

* 将指针初始化为 NULL，之后没有给它一个合理的值就开始使用指针
* 没用初始化栈中的指针，指针的值一般会是随机数，之后就直接开始使用指针

### C++程序的编译链接机制

1. **预处理：**主要处理源代码文件中以“#”开头的预编译指令。生成 `.i` 或 `.ii` 文件

   * 删除#definde，展开宏定义
   * 处理条件编译指令，如“#if ，#endif，#ifdef，#else”等
   * 处理“#include”指令，展开所有头文件，递归进行
   * 删除所有的注释
   * 保留“#pragma”指令，编译器需要用到
   * 添加行号和文件标识，便于编译器产生调试用的行号信息

2. **编译：**生成 `.s` 文件

   * 词法分析，类似于“有限状态机”算法，将源代码输入到扫描机中，将其中的字符序列分割成一系列的记号
   * 语法分析，语法分析器对由扫描器产生的记号进行语法分析，生成语法树
   * 语义分析，语法分析器只是完成了对表达式语法层面的分析，语义分析器则对表达式是否有意义进行判断，其分析的语义是静态语义
   * 优化，源代码级别的一个优化过程
   * 目标代码生成，由代码生成器将中间代码转换成目标机器代码，生成一系列的代码序列 - 汇编码
   * 目标代码优化，对上述生成的目标机器代码进行优化，寻找合适的寻址方式，使用移位代替乘法运算，删除多余的指令等

3. **汇编：**将汇编代码转换成机器可以执行的指令（机器码）。由汇编器as完成，生成 `.o` 文件

4. **链接：**将不同的源文件产生的目标文件进行链接，生成一个可执行程序。分为静态链接和动态链接：

   * **静态链接：**函数和数据被编译成一个二进制文件。在使用静态库的情况下，在编译链接可执行程序时，链接器从库中复制这些函数和数据并把它们和应用程序的其它模块组合起来创建最终的可执行程序。

     **缺点：**

     * 空间浪费，每个可执行程序对所需要的目标文件都有一份拷贝
     * 更新困难，库函数代码更新，则需要重新编译链接生成可执行程序

     **优点：**

     * 运行速度快，可执行程序中已经具备了所有执行程序的需要的任何东西，所以运行速度更快

   * **动态链接：**将程序划分为多个独立的模块，在程序运行时才将它们链接在一起形成一个完成的程序，而不像静态链接一样把所有的程序模块都链接程一个单独的可执行文件。在使用动态库时，库是共享的，不需要在内存中存在多份拷贝，而是多个程序在执行时共享同一个副本。

     **缺点：**

     * 性能较低，将链接阶段推迟到了程序运行阶段，所以每次执行程序都需要进行链接过程，所以性能有一定损失

     **优点：**

     * 更新方便，更新时只需要替换掉原来的目标文件，无需将所有的程序都链接一遍。当程序下一次运行时，新版的目标文件会被自动加载到内存并进行链接，程序就完成了升级的目标
     * 节省空间

### [C++静态库和动态库详解](https://blog.csdn.net/weixin_42482896/article/details/95654355)

