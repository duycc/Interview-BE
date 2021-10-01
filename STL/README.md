### STL中vector的实现

vector是一种序列式容器，其数据安排以及操作方式与array非常类似，两者的唯一差别就是对于空间运用的灵活性，众所周知，array占用的是静态空间，一旦配置了就不可以改变大小，如果遇到空间不足的情况还要自行创建更大的空间，并手动将数据拷贝到新的空间中，再把原来的空间释放。vector则使用灵活的动态空间配置，维护一块**连续的线性空间**，在空间不足时，可以自动扩展空间容纳新元素，做到按需供给。其在扩充空间的过程中仍然需要经历：**重新配置空间，移动数据，释放原空间**等操作。这里需要说明一下动态扩容的规则：以原大小的两倍配置另外一块较大的空间（或者旧长度+新增元素的个数），源码：

```C++
const size_type len  = old_size + max(old_size, n);
```

 Vector扩容倍数与平台有关，在Win +  VS 下是 1.5倍，在 Linux + GCC 下是 2 倍 

测试代码：

```C++
int main() {
  // 在Linux + GCC下
  vector<int> res(2, 0);
  cout << res.capacity() << endl; // 2
  res.push_back(1);
  cout << res.capacity() << endl; // 4
  res.push_back(2);
  res.push_back(3);
  cout << res.capacity() << endl; // 8
  return 0;

  // 在 win 10 + clang++ 下
  vector<int> res(2, 0);
  cout << res.capacity() << endl; // 2
  res.push_back(1);
  cout << res.capacity() << endl; // 3
  res.push_back(2);
  res.push_back(3);
  cout << res.capacity() << endl; // 6
}
```

运行上述代码，一开始配置了一块长度为2的空间，接下来插入一个数据，长度变为原来的两倍，为4，此时已占用的长度为3，再继续两个数据，此时长度变为8，可以清晰的看到空间的变化过程

### STL中forward_list的实现

list是双向链表，而forward_list是单向链表，它们的主要区别在于：前者的迭代器是双向的Bidirectional iterator，后者的迭代器属于单向的Forward iterator。虽然forward_list的很多功能不如list灵活，但是其所耗用的空间更小，操作更快。

根据STL的习惯，插入操作会将新元素插入到指定位置之前，而非之后，然而forward_list是不能回头的，只能往后走，因此在forward_list的其他位置插入或者移除元素是十分不明智的，但是在forward_list开头却是可取的，forward_list特别提供了insert_after()和erase_after供灵活应用。考虑到效率问题，forward_list只提供push_front()操作，元素插入到forward_list后，存储的次序和输入的次序是相反的

forward_list的单向迭代器如下图所示：

![](https://gitee.com/duycc/picgo/raw/master/20210331192136.png)

forward_list默认采用alloc空间配置器配置节点的空间，其数据结构主要代码如下

```C++
template <class T, class Allco = alloc>
class slist {
private:
  static list_node *create_node(const value_type &x) {} // 配置空间、构造元素
  static void destroy_node(list_node *node) {}          // 析构函数、释放空间
private:
  list_node_base head; // 头部
public:
  iterator begin() {}
  iterator end() {}
  size_type size() {}
  bool empty() {}
  void swap(slist &L) {}             // 交换两个slist，只需要换head即可
  reference front() {}               // 取头部元素
  void push_front(const value &x) {} // 头部插入元素
  void pop_front() {}                // 从头部取走元素
}
```

举个例子：

```C++
#include <forward_list>
#include <algorithm>
#include <iostream>

using namespace std;

int main() {
  forward_list<int> fl;
  fl.push_front(1);
  fl.push_front(3);
  fl.push_front(2);
  fl.push_front(6);
  fl.push_front(5);

  forward_list<int>::iterator ite1 = fl.begin();
  forward_list<int>::iterator ite2 = fl.end();
  for (; ite1 != ite2; ++ite1) {
    cout << *ite1 << " "; // 5 6 2 3 1
  }
  cout << endl;

  ite1 = find(fl.begin(), fl.end(), 2); // 寻找2的位置

  if (ite1 != ite2)
    fl.insert_after(ite1, 99);
  for (auto it : fl) {
    cout << it << " "; // 5 6 2 99 3 1
  }
  cout << endl;

  ite1 = find(fl.begin(), fl.end(), 6); // 寻找6的位置
  if (ite1 != ite2)
    fl.erase_after(ite1);
  for (auto it : fl) {
    cout << it << " "; // 5 6 99 3 1
  }
  cout << endl;
  return 0;
}
```

### STL中list的实现

相比于vector的连续线型空间，list显得复杂许多，但是它的好处在于插入或删除都只作用于一个元素空间，因此list对空间的运用是十分精准的，对任何位置元素的插入和删除都是常数时间。list不能保证节点在存储空间中连续存储，也拥有迭代器，迭代器的“++”、“--”操作对于的是指针的操作，list提供的迭代器类型是双向迭代器：Bidirectional iterators。

list节点的结构见如下源码：

```C++
template <class T>
struct __list_node {
  typedef void *void_pointer;
  void_pointer prev;
  void_pointer next;
  T data;
}
```

从源码可看出list显然是一个双向链表。list与vector的另一个区别是，在插入和接合操作之后，都不会造成原迭代器失效，而vector可能因为空间重新配置导致迭代器失效。

此外list也是一个环形链表，因此只要一个指针便能完整表现整个链表。list中node节点指针始终指向尾端的一个空白节点，因此是一种“前闭后开”的区间结构

list的空间管理默认采用alloc作为空间配置器，为了方便的以节点大小为配置单位，还定义一个list_node_allocator函数可一次性配置多个节点空间

由于list的双向特性，其支持在头部（front)和尾部（back)两个方向进行push和pop操作，当然还支持erase，splice，sort，merge，reverse，sort等操作，这里不再详细阐述。

### STL中的deque的实现

vector是单向开口（尾部）的连续线性空间，deque则是一种双向开口的连续线性空间，虽然vector也可以在头尾进行元素操作，但是其头部操作的效率十分低下（主要是涉及到整体的移动）

![](https://gitee.com/duycc/picgo/raw/master/20210331192214.png)

deque和vector的最大差异一个是deque运行在常数时间内对头端进行元素操作，二是deque没有容量的概念，它是动态地以分段连续空间组合而成，可以随时增加一段新的空间并链接起来

deque虽然也提供随机访问的迭代器，但是其迭代器并不是普通的指针，其复杂程度比vector高很多，因此除非必要，否则一般使用vector而非deque。如果需要对deque排序，可以先将deque中的元素复制到vector中，利用sort对vector排序，再将结果复制回deque

deque由一段一段的定量连续空间组成，一旦需要增加新的空间，只要配置一段定量连续空间拼接在头部或尾部即可，因此deque的最大任务是如何维护这个整体的连续性

deque的数据结构如下：

```C++
class deque {
protected:
  typedef pointer *map_pointer; // 指向map指针的指针
  map_pointer map;              // 指向map
  size_type map_size;           // map的大小
public:
  iterator begin();
  itertator end();
}
```

![](https://gitee.com/duycc/picgo/raw/master/20210331192221.png)

deque内部有一个指针指向map，map是一小块连续空间，其中的每个元素称为一个节点，node，每个node都是一个指针，指向另一段较大的连续空间，称为缓冲区，这里就是deque中实际存放数据的区域，默认大小512bytes。整体结构如上图所示。

deque的迭代器数据结构如下：

```C++
struct __deque_iterator {
  T *cur;           // 迭代器所指缓冲区当前的元素
  T *first;         // 迭代器所指缓冲区第一个元素
  T *last;          // 迭代器所指缓冲区最后一个元素
  map_pointer node; // 指向map中的node
}
```

从deque的迭代器数据结构可以看出，为了保持与容器联结，迭代器主要包含上述4个元素

![](https://gitee.com/duycc/picgo/raw/master/20210331192232.png)

deque迭代器的“++”、“--”操作是远比vector迭代器繁琐，其主要工作在于缓冲区边界，如何从当前缓冲区跳到另一个缓冲区，当然deque内部在插入元素时，如果map中node数量全部使用完，且node指向的缓冲区也没有多余的空间，这时会配置新的map（2倍于当前+2的数量）来容纳更多的node，也就是可以指向更多的缓冲区。在deque删除元素时，也提供了元素的析构和空闲缓冲区空间的释放等机制。

### STL中stack和queue的实现

**stack**

stack（栈）是一种先进后出（First In Last Out）的数据结构，只有一个入口和出口，那就是栈顶，除了获取栈顶元素外，没有其他方法可以获取到内部的其他元素，其结构图如下：

![](https://gitee.com/duycc/picgo/raw/master/20210331192318.png)

stack这种单向开口的数据结构很容易由**双向开口的deque和list**形成，只需要根据stack的性质对应移除某些接口即可实现，stack的源码如下：

```C++
template <class T, class Sequence = deque<T>>
class stack {
protected:
  Sequence c;

public:
  bool empty() { return c.empty(); }
  size_type size() const { return c.size(); }
  reference top() const { return c.back(); }
  const_reference top() const { return c.back(); }
  void push(const value_type &x) { c.push_back(x); }
  void pop() { c.pop_back(); }
};
```

从stack的数据结构可以看出，其所有操作都是围绕Sequence完成，而Sequence默认是deque数据结构。stack这种“修改某种接口，形成另一种风貌”的行为，成为adapter(配接器)。常将其归类为container adapter而非container

stack除了默认使用deque作为其底层容器之外，也可以使用双向开口的list，只需要在初始化stack时，将list作为第二个参数即可。由于stack只能操作顶端的元素，因此其内部元素无法被访问，也不提供迭代器。

**queue**

queue（队列）是一种先进先出（First In First Out）的数据结构，只有一个入口和一个出口，分别位于最底端和最顶端，出口元素外，没有其他方法可以获取到内部的其他元素，其结构图如下：

![](https://gitee.com/duycc/picgo/raw/master/20210331192408.png)

类似的，queue这种“先进先出”的数据结构很容易由双向开口的deque和list形成，只需要根据queue的性质对应移除某些接口即可实现，queue的源码如下：

```C++
template <class T, class Sequence = deque<T>>
class queue {
protected:
  Sequence c;

public:
  bool empty() { return c.empty(); }
  size_type size() const { return c.size(); }
  reference front() const { return c.front(); }
  const_reference front() const { return c.front(); }
  void push(const value_type &x) { c.push_back(x); }
  void pop() { c.pop_front(); }
};
```

从queue的数据结构可以看出，其所有操作都也都是是围绕Sequence完成，Sequence默认也是deque数据结构。queue也是一类container adapter。

同样，queue也可以使用list作为底层容器，不具有遍历功能，没有迭代器。

### STL中的heap的实现

heap（堆）并不是STL的容器组件，是priority_queue（优先队列）的底层实现机制，因为binary max heap（大根堆）总是最大值位于堆的根部，优先级最高。

binary heap本质是一种complete binary tree（完全二叉树），整棵binary tree除了最底层的叶节点之外，都是填满的，但是叶节点从左到右不会出现空隙，如下图所示就是一颗完全二叉树

![](https://gitee.com/duycc/picgo/raw/master/20210331192453.png)

完全二叉树内没有任何节点漏洞，是非常紧凑的，这样的一个好处是可以使用array来存储所有的节点，因为当其中某个节点位于$i$处，其左节点必定位于$2i$处，右节点位于$2i+1$处，父节点位于$i/2$（向下取整）处。这种以array表示tree的方式称为隐式表述法。

因此我们可以使用一个array和一组heap算法来实现max heap（每个节点的值大于等于其子节点的值）和min heap（每个节点的值小于等于其子节点的值）。由于array不能动态的改变空间大小，用vector代替array是一个不错的选择。

那heap算法有哪些？常见有的插入、弹出、排序和构造算法，下面一一进行描述。

**push_heap插入算法**

由于完全二叉树的性质，新插入的元素一定是位于树的最底层作为叶子节点，并填补由左至右的第一个空格。事实上，在刚执行插入操作时，新元素位于底层vector的end()处，之后是一个称为percolate up（上溯）的过程，举个例子如下图：

![](https://gitee.com/duycc/picgo/raw/master/20210331192547.png)

新元素50在插入堆中后，先放在vector的end()存着，之后执行上溯过程，调整其根结点的位置，以便满足max heap的性质，如果了解大根堆的话，这个原理跟大根堆的调整过程是一样的。

**pop_heap算法**

heap的pop操作实际弹出的是根节点吗，但在heap内部执行pop_heap时，只是将其移动到vector的最后位置，然后再为这个被挤走的元素找到一个合适的安放位置，使整颗树满足完全二叉树的条件。这个被挤掉的元素首先会与根结点的两个子节点比较，并与较大的子节点更换位置，如此一直往下，直到这个被挤掉的元素大于左右两个子节点，或者下放到叶节点为止，这个过程称为percolate down（下溯）。举个例子：

![image-20211001110106790](https://gitee.com/duycc/picgo/raw/master/20211001110108.png)

根节点68被pop之后，移到了vector的最底部，将24挤出，24被迫从根节点开始与其子节点进行比较，直到找到合适的位置安身，需要注意的是pop之后元素并没有被移走，如果要将其移走，可以使用pop_back()。

**sort算法**

一言以蔽之，因为pop_heap可以将当前heap中的最大值置于底层容器vector的末尾，heap范围减1，那么不断的执行pop_heap直到树为空，即可得到一个递增序列。

**make_heap算法**

将一段数据转化为heap，一个一个数据插入，调用上面说的两种percolate算法即可。

代码实测：

```C++
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
  vector<int> v = {0, 1, 2, 3, 4, 5, 6};
  make_heap(v.begin(), v.end()); // 以vector为底层容器
  for (auto i : v) {
    cout << i << " "; // 6 4 5 3 1 0 2
  }
  cout << endl;
  v.push_back(7);
  push_heap(v.begin(), v.end());
  for (auto i : v) {
    cout << i << " "; // 7 6 5 4 1 0 2 3
  }
  cout << endl;
  pop_heap(v.begin(), v.end());
  cout << v.back() << endl; // 7
  v.pop_back();
  for (auto i : v) {
    cout << i << " "; // 6 4 5 3 1 0 2
  }
  cout << endl;
  sort_heap(v.begin(), v.end());
  for (auto i : v) {
    cout << i << " "; // 0 1 2 3 4 5 6
  }
  return 0;
}
```

### STL中的priority_queue的实现

priority_queue，优先队列，是一个拥有权值观念的queue，它跟queue一样是顶部入口，底部出口，在插入元素时，元素并非按照插入次序排列，它会自动根据权值（通常是元素的实值）排列，权值最高，排在最前面，如下图所示。

![](https://gitee.com/duycc/picgo/raw/master/20210331192944.png)

默认情况下，priority_queue使用一个max-heap完成，底层容器使用的是一般为vector为底层容器，堆heap为处理规则来管理底层容器实现 。priority_queue的这种实现机制导致其不被归为容器，而是一种容器配接器。关键的源码如下：

```C++
template <class T, class Squence = vector<T>, class Compare = less<typename Sequence::value_tyoe>>
class priority_queue {
protected:
  Sequence c;
  Compare comp;

public:
  bool empty() const { return c.empty(); }
  size_type size() const { return c.size(); }
  const_reference top() const { return c.front() }
  void push(const value_type &x) {
    c.push_heap(x);
    push_heap(c.begin(), c.end(), comp);
  }
  void pop() {
    pop_heap(c.begin(), c.end(), comp);
    c.pop_back();
  }
};
```

priority_queue的所有元素，进出都有一定的规则，只有queue顶端的元素（权值最高者），才有机会被外界取用，它没有遍历功能，也不提供迭代器

举个例子：

```C++
#include <queue>
#include <iostream>
using namespace std;

int main() {
  int ia[9] = {0, 4, 1, 2, 3, 6, 5, 8, 7};
  priority_queue<int> pq(ia, ia + 9);
  cout << pq.size() << endl; // 9
  for (int i = 0; i < pq.size(); i++) {
    cout << pq.top() << " "; // 8 8 8 8 8 8 8 8 8
  }
  cout << endl;
  while (!pq.empty()) {
    cout << pq.top() << ' '; // 8 7 6 5 4 3 2 1 0
    pq.pop();
  }
  return 0;
}
```

### STL中set的实现

STL中的容器可分为序列式容器（sequence）和关联式容器（associative），set属于关联式容器。

set的特性是，所有元素都会根据元素的值自动被排序（默认升序），set元素的键值就是实值，实值就是键值，set不允许有两个相同的键值

set不允许迭代器修改元素的值，其迭代器是一种constance iterators

标准的STL set以RB-tree（红黑树）作为底层机制，几乎所有的set操作行为都是转调用RB-tree的操作行为

举个例子：

```C++
#include <set>
#include <iostream>
using namespace std;

int main() {
  int i;
  int ia[5] = {1, 2, 3, 4, 5};
  set<int> s(ia, ia + 5);
  cout << s.size() << endl;    // 5
  cout << s.count(3) << endl;  // 1
  cout << s.count(10) << endl; // 0

  s.insert(3);                // 再插入一个3
  cout << s.size() << endl;   // 5
  cout << s.count(3) << endl; // 1

  s.erase(1);
  cout << s.size() << endl; // 4

  set<int>::iterator b = s.begin();
  set<int>::iterator e = s.end();
  for (; b != e; ++b)
    cout << *b << " "; // 2 3 4 5
  cout << endl;

  b = find(s.begin(), s.end(), 5);
  if (b != s.end())
    cout << "5 found" << endl; // 5 found

  b = s.find(2);
  if (b != s.end())
    cout << "2 found" << endl; // 2 found

  b = s.find(1);
  if (b == s.end())
    cout << "1 not found" << endl; // 1 not found
  return 0;
}
```

关联式容器尽量使用其自身提供的find()函数查找指定的元素，效率更高，因为STL提供的find()函数是一种顺序搜索算法。

### STL中map的实现

map的特性是所有元素会根据键值进行自动排序。map中所有的元素都是pair，拥有键值(key)和实值(value)两个部分，并且不允许元素有相同的key，一旦map的key确定了，那么是无法修改的，但是可以修改这个key对应的value，因此map的迭代器既不是constant iterator，也不是mutable iterator

标准STL map的底层机制是RB-tree（红黑树），另一种以hash table为底层机制实现的称为hash_map。map的架构如下图所示

![](https://gitee.com/duycc/picgo/raw/master/20210331193732.png)

map的在构造时缺省采用递增排序key，也使用alloc配置器配置空间大小，需要注意的是在插入元素时，调用的是红黑树中的insert_unique()方法，而非insert_euqal()（multimap使用）

举个例子：

```C++
#include <map>
#include <iostream>
#include <string>
using namespace std;

int main() {
  map<string, int> maps;
  // 插入若干元素
  maps["jack"] = 1;
  maps["jane"] = 2;
  maps["july"] = 3;
  // 以pair形式插入
  pair<string, int> p("david", 4);
  maps.insert(p);
  // 迭代输出元素
  map<string, int>::iterator iter = maps.begin();
  for (; iter != maps.end(); ++iter) {
    cout << iter->first << " ";
    cout << iter->second << "--"; // david 4--jack 1--jane 2--july 3--
  }
  cout << endl;
  // 使用subscipt操作取实值
  int num = maps["july"];
  cout << num << endl; // 3
  //查找某key
  iter = maps.find("jane");
  if (iter != maps.end())
    cout << iter->second << endl; // 2
                                  // 修改实值
  iter->second = 100;
  int num2 = maps["jane"]; // 100
  cout << num2 << endl;

  return 0;
}
```

需要注意的是subscript（下标）操作既可以作为左值运用（修改内容）也可以作为右值运用（获取实值）。例如：

```C++
maps["abc"] = 1;       // 左值运用
int num = masp["abd"]; // 右值运用
```

无论如何，subscript操作符都会先根据键值找出实值，源码如下：

```C++
T &operator[](const key_type &k) { return (*((insert(value_type(k, T()))).first)).second; }
```

代码运行过程是：首先根据键值和实值做出一个元素，这个元素的实值未知，因此产生一个与实值型别相同的临时对象替代：

```C++
value_type(k, T());
```

再将这个对象插入到map中，并返回一个pair：

```C++
pair<iterator,bool> insert(value_type(k, T()));
```

pair第一个元素是迭代器，指向当前插入的新元素，如果插入成功返回true，此时对应左值运用，根据键值插入实值。插入失败（重复插入）返回false，此时返回的是已经存在的元素，则可以取到它的实值

```C++
(insert(value_type(k, T()))).first;             // 迭代器
*((insert(value_type(k, T()))).first);          // 解引用
(*((insert(value_type(k, T()))).first)).second; // 取出实值
```

由于这个实值是以引用方式传递，因此作为左值或者右值都可以

