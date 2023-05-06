# 网络接口

网络接口被封装为三个库，下面依次说明其中提供的全部公有接口的作用及其调用方式。对私有方法的实现与作用感兴趣的同学可自行查阅源代码探索。
另外，我们并没有完全封装，有一些重要的功能你要直接使用基类函数，比如 `NetworkServer::listen`，这意味着你们需要在结合 demo 阅读的同时用好 Qt 的 F1 文档
来理解我们没有提到的部分。

对应文件在目录 [src](../src/) 下

作者：[megaowier](https://blog.megaowier.cc/)

**注意：** 网络接口在 Qt6 下实现，不保证在更早版本的 Qt 上能正常使用。

> TCP 中必须是客户端向服务端连接，服务端可以同时被多个客户端连接，双方是不对等的。虽然本次对局是1对1，但在邀请阶段，也可能出现同时被多个客户端邀请的情况需要处理。

## `NetworkServer` 类

`NetworkServer` 类以 `public` 方式继承自 `QTcpServer` 类，在 `networkserver.{h, c}` 中声明与实现，封装了服务端所需要的网络功能。

### 公有方法

```cpp
explicit NetworkServer::NetworkServer(QObject* parent = nullptr);
```
构造函数。用于构造一个 `NetworkServer` 对象。

参数列表：

+ `parent`: 应传入一个指向与当前 `NetworkServer` 对象绑定的窗口的指针。默认值为 `nullprt`，即不与任何窗口绑定。

----------

```cpp
bool QTcpServer::listen(const QHostAddress &address = QHostAddress::Any, quint16 port = 0);
```

Tells the server to listen for incoming connections on address address and port port. If port is 0, a port is chosen automatically. If address is QHostAddress::Any, the server will listen on all network interfaces.

----------

```cpp
void NetworkServer::send(QTcpSocket* client, NetworkData data);
```
用于向指定机器发送信息。

参数列表：

+ `client`: 表示目标机器。
+ `data`: 表示需要发送的数据。

### 公有信号函数

```c++
void receive(QTcpSocket* client, NetworkData data);
```

当服务端收到客户端发来的消息并解析成功时发送 `receive` 信号。

参数列表：

+ `client`: 表示发送消息的客户端。
+ `data`: 表示接收到的数据。

----------

```c++
void parseError(const InvalidMessage& msg);
```

当服务端收到客户端发来的消息但解析失败时发送 `parseError` 信号。

参数列表：

+ `msg`: 表示错误信息。

----------

```c++
void leave(QTcpSocket *client);
```

当服务端旋开与某一客户端的连接时发送 `leave` 信号。

参数列表：

+ `client`: 表示被断开连接的客户端。

### 使用方法

每一个 `NetworkServer` 实例应与一个 `QObject` 比如服务端主窗口绑定，这个窗口的类型应该是一个你自定义的继承自 `QMainWindow` 的类。

你需要在这个类中新增一个 `NetworkServer *` 类型的成员变量 `server`，并在窗口类的构造函数中加入下列代码来完成初始化和信号与槽的连接：

```c++
this->server = new NetworkServer(this);

connect(this->server, &NetworkServer::receive, this, &ServerWindow::receiveData);
```

其中 `ServerWindow::receiveData` 是你实现的处理服务端接收到的信息的槽函数。

## `NetworkData` 类

`NetworkData` 类在 `networkdata.{h, c}` 中声明与实现，其主要功能是将需要发送和已经接收到的信息按照[通信协议](./protocol.md)表示出来。

### 公有方法

```cpp
NetworkData::NetworkData(OPCODE op, QString data1, QString data2);
```
构造函数。用于构造需要从本机发送出去的消息。

参数列表：

+ `op`: 当前操作的操作符。
	- 其类型 `OPCODE` 是一个枚举类，同样定义在 `networkdata.h` 中。
+ `data1`: 当前操作的第一个数据段。
+ `data2`: 当前操作的第二个数据段。

----------

```cpp
NetworkData::NetworkData(QByteArray message);
```
构造函数。用于构造从接受到的从远程传来的消息。

参数列表：

+ `message`: 当前接收到的消息。

异常：

+ 当传入参数无法解析时会抛出一个 `InvalidMessage` 异常。
	- 抓取到异常后可调用 `InvalidMessage::messageReceived()` 查看引发异常的消息。该方法的返回类型为 `QByteArray`。

----------

```cpp
QByteArray NetworkData::encode();
```
用于将当前对象所表示的信息编码为 `QByteArray` 方便后续进行其他操作（如发送等）。

## `NetworkSocket` 类

`NetworkSocket` 类以 `public` 方式继承自 `QObject` 类，在 `networksocket.{h, c}` 中声明与实现。用于表示本机与远程一台机器建立的连接，封装了客户端所需要的网络功能。

### 公有方法

```cpp
explicit NetworkSocket::NetworkSocket(QTcpSocket* socket, QObject* parent = nullptr);
```
构造函数。用于构造一个 `NetworkSocket` 对象。

参数列表：

+ `socket`: 表示当前窗口监听的套接字文件，正常情况下应当传入一个新的套接字。
 	- 如果你并不了解上面那句话的含义，在构造函数中简单地为这个参数传入 `new QTcpSocket()` 即可。
+ `parent`: 应传入一个指向与当前 `NetworkSocket` 对象绑定的窗口的指针。默认值为 `nullprt`，即不与任何窗口绑定。

----------

```cpp
void NetworkSocket::send(NetworkData data);
```
用于给当前对象表示的远程机器发送消息。

参数列表：

+ `data`: 需要发送的消息。

----------

```cpp
void NetworkSocket::hello(const QString& host, quint16 port);
```

用于与指定远程机器的指定端口建立网络连接。若当前对象已经与远程建立连接，则先断开它。

参数列表：

+ `host`: 远程机器的 IPv4 地址。
	- 除非你的电脑有专属的 IPv4 公网地址（通常情况下这不可能），否则你应该让所有客户端与服务端接入同一个局域网（如校园网），并在此传入内网地址。
+ `port`: 远程机器的端口号。

> "温馨提示": 如果你的设备接入的是 `RUC-Web`，你的内网地址大概率形如 `10.46.X.X`；实测，`RUC-Mobile` 似乎不能正常连上，所以最好都用 `RUC-Web`。
> 
> 连接建立成功时会发射成员变量 `socket` 的信号 `connected()`；反之，连接建立失败时会发射成员变量 `socket` 的信号 `errorOccurred()`。
>
> 另外，这是一个非阻塞的函数，见 `guidance/qt`

----------

```cpp
QTcpSocket* NetworkSocket::base() const;
```
返回原生 TCP 套接字（即成员变量 `socket`）。

### 公有信号函数

```c++
void receive(NetworkData data);
```

当前客户端收到来自服务端的消息时发送 `reveive` 信号。

参数列表：

+ `data`: 表示接收到的数据。

----------

```c++
void parseError(const InvalidMessage& msg);
```

当服务端收到客户端发来的消息但解析失败时发送 `parseError` 信号。

参数列表：

+ `msg`: 表示错误信息。

### 公有槽函数

```c++
void bye();
```

关闭当前客户端与服务端的连接。

### 使用方法

每一个 `NetworkSocket` 实例应与一个 `QObject` 比如客户端主窗口绑定，这个窗口的类型应该是一个你自定义的继承自 `QMainWindow` 的类。

你需要在这个类中新增一个 `NetworkSocket *` 类型的成员变量 `socket`，并在窗口类的构造函数中加入下列代码来完成初始化和信号与槽的连接：

```c++
this->socket = new NetworkSocket(new QTcpSocket(), this);

connect(socket, &NetworkSocket::receive, this, &ClientWindow::receive);
connect(socket->base(), &QAbstractSocket::disconnected, [=]() {
	QMessageBox::critical(this, tr("Connection lost"), tr("Connection to server has closed"));
});
```

特别地，如果你为方法 `socket->hello` 中发射的两个信号设计了处理函数，可以以如下方式连接

```c++
connect(socket->base(), &QAbstractSocket::errorOccurred, this, &ClientWindow::displayError);
connect(socket->base(), &QAbstractSocket::connected, this, &ClientWindow::connected);
```

其中 `ClientWindow::displayError` 和 `ClientWindow::connected` 分别是你实现的处理连接失败和连接成功的槽函数。
