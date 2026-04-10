# Linux Network Programming

> Linux网络编程学习项目 - 从基础到实战

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Platform](https://img.shields.io/badge/platform-Linux-green.svg)
![Language](https://img.shields.io/badge/language-C-orange.svg)

## 项目简介

这是一个系统性学习Linux网络编程的实战项目，涵盖了从进程信号处理、多线程编程到Socket网络通信的完整知识体系。通过循序渐进的学习路径，从基础示例到高性能服务器实现，帮助掌握Linux环境下的网络编程技能。

## 学习路径

```
Day01          → 开发环境与工具准备
Day02          → 信号处理 (Signal)
Day03          → 线程基础 (pthread_create/join)
Day04          → 线程控制 (cancel/exit/cleanup)
Day05          → 线程同步 (mutex/condition variable)
Day06          → 线程属性 (pthread_attr)
Day07          → 综合实践
Day08          → 网络字节序与地址转换
Day09          → TCP/UDP Socket编程基础
Day10          → IO多路复用 (select/poll/epoll)
```

## 核心知识点

### 信号处理 (Day02)
- `signal()` - 基础信号处理
- `sigaction()` - 可靠信号处理与标志位
- `sigprocmask()` - 信号屏蔽与集合操作
- `pause()/alarm()/setitimer()` - 信号与定时器结合

### 多线程编程 (Day03 - Day06)
| 主题 | 内容 |
|------|------|
| 线程创建 | `pthread_create` 参数传递、线程ID |
| 线程回收 | `pthread_join` 回收线程返回值 |
| 线程取消 | `pthread_cancel` 取消点概念 |
| 线程终止 | `pthread_exit` 返回值传递 |
| 互斥锁 | `pthread_mutex` 死锁与递归锁 |
| 条件变量 | `pthread_cond` 生产者消费者模型 |
| 线程属性 | 分离状态、栈大小、调度策略 |

### 网络编程 (Day08 - Day10)
| 主题 | 内容 |
|------|------|
| 字节序 | `htonl/ntohl/htons/ntohs` |
| 地址转换 | `inet_pton/inet_ntop` |
| TCP服务器 | 多客户端连接、端口复用 |
| UDP通信 | 无连接数据报socket |
| select | 批量IO就绪检测、聊天室实现 |
| poll | 更灵活的IO多路复用 |
| epoll | LT/ET模式、边缘触发高效模型 |

## 项目结构

```
linux_network_programming/
├── LinuxDay01/              # 开发环境准备
│   ├── my_header.h          # 公共头文件(宏定义、错误检查)
│   └── Makefile
├── LinuxDay02/              # 信号处理
│   ├── 01_signal.c ~ 20_setitimer.c
│   └── Makefile
├── LinuxDay03/              # 线程基础
│   ├── 01_pthread_create_while.c
│   ├── 10_pthread_join.c
│   ├── 17_pthread_exit.c
│   └── Makefile
├── LinuxDay04/              # 线程控制
│   ├── 04_pthread_cancel.c
│   ├── 08_cleanup.c
│   └── Makefile
├── LinuxDay05/              # 线程同步
│   ├── 03_pthread_mutex.c
│   ├── 11_pthread_cond_wait.c
│   ├── 1_homework/          # 课堂作业
│   └── Makefile
├── LinuxDay06/              # 线程属性
│   ├── 01_pthread_attr.c
│   └── Makefile
├── LinuxDay07/              # 综合实践
│   └── 1_homework/
├── LinuxDay08/              # 网络基础
│   ├── 01_htonl.c
│   ├── 02_inet.c
│   └── Makefile
├── LinuxDay09/              # Socket编程
│   ├── 01_server.c          # 基础TCP服务器
│   ├── 05_server.c          # 多客户端TCP服务器
│   ├── 06_server_udp.c       # UDP服务器
│   └── Makefile
├── LinuxDay10/              # IO多路复用
│   ├── 01_chat_server_select.c    # select聊天室服务器
│   ├── 02_server_epoll.c          # epoll服务器
│   ├── 03_epoll_lt.c              # LT模式
│   ├── 04_epoll_et.c              # ET模式
│   ├── 05_epoll_et_while.c        # ET+while循环
│   ├── 06_recv_server_dontwait.c  # 非阻塞接收
│   └── Makefile
└── README.md
```

## 快速开始

### 环境要求
- Linux操作系统
- GCC编译器
- POSIX线程库 (libpthread)

### 编译项目
```bash
# 进入任意章节目录
cd LinuxDay09

# 编译所有示例
make

# 或单独编译
gcc 01_server.c -o server -Wall -g
```

### 运行示例
```bash
# TCP服务器
./01_server

# TCP客户端 (另一个终端)
./01_client

# EPOLL服务器
./02_server_epoll
```

## 核心代码示例

### 自定义错误检查宏 (my_header.h)
```c
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define ERROR_CHECK(ret, error_flag, msg) \
    do { \
        if((ret) == (error_flag)) { \
            perror(msg); \
            exit(1); \
        } \
    }while(0);

#define THREAD_ERROR_CHECK(ret, msg) \
    do { \
        if(0 != ret) { \
            fprintf(stderr, "%s: %s\n", msg, strerror(ret)); \
        } \
    } while(0);
```

### TCP服务器模板
```c
#include "my_header.h"

int main(int argc, char *argv[])
{
    // 1. 创建socket
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(listen_fd, -1, "socket");

    // 2. 绑定地址
    struct sockaddr_in addr = {...};
    bind(listen_fd, (struct sockaddr *)&addr, sizeof(addr));

    // 3. 监听
    listen(listen_fd, 10);

    // 4. 接受连接
    int conn_fd = accept(listen_fd, NULL, NULL);
    
    // 5. 收发数据
    char buf[1024];
    recv(conn_fd, buf, sizeof(buf), 0);
    send(conn_fd, buf, strlen(buf), 0);

    close(conn_fd);
    close(listen_fd);
    return 0;
}
```

## 学习要点

### TCP服务器演进
| 版本 | 特性 | 限制 |
|------|------|------|
| v1 | 基础单次通信 | 只能一次收发 |
| v2 | 非阻塞通信 | 对方断开时死循环 |
| v3 | 优雅处理断开 | 只能单客户端 |
| v4 | 多客户端连接 | select/poll/epoll实现 |
| v5 | **IO多路复用** | select限制1024fd |

### EPOLL工作模式
- **LT (Level Trigger)** - 水平触发，默认模式，事件未处理会持续通知
- **ET (Edge Trigger)** - 边缘触发，高效模式，需循环读取所有数据

### 线程同步模式
- **互斥锁** - 保护共享资源
- **条件变量** - 线程间事件通知
- **死锁避免** - 按序加锁、trylock

## 常见问题

**Q: 为什么需要网络字节序转换？**
> 不同主机的字节序可能不同(大端/小端)，网络协议统一使用大端序。

**Q: select有fd数量限制吗？**
> 默认1024，可通过`ulimit -n`调整，但推荐使用epoll。

**Q: EPOLL的LT和ET如何选择？**
> LT简单但可能多次通知；ET高效但需循环处理直到EAGAIN。

## 参考资料

- [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/)
- [POSIX Thread Programming](https://computing.llnl.gov/tutorials/pthreads/)
- Linux Man Pages

## 许可证

本项目采用 [MIT License](LICENSE) 开源，欢迎学习和交流。

---

> **学习是一个循序渐进的过程，每一行代码都是成长的脚印。**
