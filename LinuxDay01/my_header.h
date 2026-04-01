#ifndef __MY_HEADER_H__
#define __MY_HEADER_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <dirent.h>
#include <syslog.h>
#include <ctype.h>
#include <stdbool.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/select.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <sys/sendfile.h>
#include <signal.h>
#include <pthread.h>

// 检查命令行参数数量是否符合预期
#define ARGS_CHECK(args, excepted) \
    do{ \
        if((args) != (excepted)) \
        { \
            fprintf(stderr, "args num error"); \
            exit(1); \
        } \
    }while(0);

// 检查返回值是否是错误标记,若是则打印msg和错误信息
#define ERROR_CHECK(ret, error_flag, msg) \
    do { \
        if((ret) == (error_flag)) { \
            perror(msg); \
            exit(1); \
        } \
    }while(0);

#define THREAD_ERROR_CHECK(ret, msg) \
    do { \
	 if(0 != ret) \
	 { \
	     fprintf(stderr, "%s:%s\n", msg, strerror(ret)); \
	 } \	
     } while(0);

#endif

