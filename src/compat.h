#ifndef BITCOIN_COMPAT_H
#define BITCOIN_COMPAT_H

#include <sys/fcntl.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <net/if.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <limits.h>
#include <netdb.h>
#include <unistd.h>

typedef u_int SOCKET;
#include "errno.h"
#define WSAGetLastError()   errno
#define WSAEINVAL           EINVAL
#define WSAEALREADY         EALREADY
#define WSAEWOULDBLOCK      EWOULDBLOCK
#define WSAEMSGSIZE         EMSGSIZE
#define WSAEINTR            EINTR
#define WSAEINPROGRESS      EINPROGRESS
#define WSAEADDRINUSE       EADDRINUSE
#define WSAENOTSOCK         EBADF
#define INVALID_SOCKET      (SOCKET)(~0)
#define SOCKET_ERROR        -1

#define MAX_PATH            1024

// As Solaris does not have the MSG_NOSIGNAL flag for send(2) syscall, it is defined as 0
#if !defined(HAVE_MSG_NOSIGNAL) && !defined(MSG_NOSIGNAL)
#define MSG_NOSIGNAL 0
#endif

// PRIO_MAX is not defined on Solaris
#ifndef PRIO_MAX
#define PRIO_MAX 20
#endif
#define THREAD_PRIORITY_LOWEST          PRIO_MAX
#define THREAD_PRIORITY_BELOW_NORMAL    2
#define THREAD_PRIORITY_NORMAL          0
#define THREAD_PRIORITY_ABOVE_NORMAL    (-2)

bool static inline IsSelectableSocket(SOCKET s) {
    return (s < FD_SETSIZE);
}

#endif // BITCOIN_COMPAT_H
