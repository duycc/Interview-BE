## 一、Linux系统编程





## 二、Linux网络编程

### Socket通信机制

![Socket 客户端服务器通讯](images/socket客户端服务器通讯.jpg?raw=true)


#### Socket 中的 read()、write() 函数

```cpp
ssize_t read(int fd, void *buf, size_t count);
ssize_t write(int fd, const void *buf, size_t count);
```

##### read()

* read 函数是负责从 fd 中读取内容。
* 当读成功时，read 返回实际所读的字节数。
* 如果返回的值是 0 表示已经读到文件的结束了，小于 0 表示出现了错误。
* 如果错误为 EINTR 说明读是由中断引起的；如果是 ECONNREST 表示网络连接出了问题。

##### write()

* write 函数将 buf 中的 nbytes 字节内容写入文件描述符 fd。
* 成功时返回写的字节数。失败时返回 -1，并设置 errno 变量。
* 在网络程序中，当我们向套接字文件描述符写时有俩种可能。
* （1）write 的返回值大于 0，表示写了部分或者是全部的数据。
* （2）返回的值小于 0，此时出现了错误。
* 如果错误为 EINTR 表示在写的时候出现了中断错误；如果为 EPIPE 表示网络连接出现了问题（对方已经关闭了连接）。

#### Socket 中 TCP 的三次握手建立连接

我们知道 TCP 建立连接要进行 “三次握手”，即交换三个分组。大致流程如下：

1. 客户端向服务器发送一个 SYN J
2. 服务器向客户端响应一个 SYN K，并对 SYN J 进行确认 ACK J+1
3. 客户端再想服务器发一个确认 ACK K+1

只有就完了三次握手，但是这个三次握手发生在 Socket 的那几个函数中呢？请看下图：

![socket 中发送的 TCP 三次握手](http://images.cnblogs.com/cnblogs_com/skynet/201012/201012122157467258.png)

从图中可以看出：

1. 当客户端调用 connect 时，触发了连接请求，向服务器发送了 SYN J 包，这时 connect 进入阻塞状态；  
2. 服务器监听到连接请求，即收到 SYN J 包，调用 accept 函数接收请求向客户端发送 SYN K ，ACK J+1，这时 accept 进入阻塞状态；  
3. 客户端收到服务器的 SYN K ，ACK J+1 之后，这时 connect 返回，并对 SYN K 进行确认；  
4. 服务器收到 ACK K+1 时，accept 返回，至此三次握手完毕，连接建立。

#### Socket 中 TCP 的四次握手释放连接

上面介绍了 socket 中 TCP 的三次握手建立过程，及其涉及的 socket 函数。现在我们介绍 socket 中的四次握手释放连接的过程，请看下图：

![socket 中发送的 TCP 四次握手](http://images.cnblogs.com/cnblogs_com/skynet/201012/201012122157487616.png)

图示过程如下：

1. 某个应用进程首先调用 close 主动关闭连接，这时 TCP 发送一个 FIN M；
2. 另一端接收到 FIN M 之后，执行被动关闭，对这个 FIN 进行确认。它的接收也作为文件结束符传递给应用进程，因为 FIN 的接收意味着应用进程在相应的连接上再也接收不到额外数据；
3. 一段时间之后，接收到文件结束符的应用进程调用 close 关闭它的 socket。这导致它的 TCP 也发送一个 FIN N；
4. 接收到这个 FIN 的源发送端 TCP 对它进行确认。

这样每个方向上都有一个 FIN 和 ACK。