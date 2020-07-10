#ifndef SOCKET_H
#define SOCKET_H

#include <QDebug>

#ifdef _WIN32
#include <winsock2.h>
#include <in6addr.h>
#include <Mstcpip.h>

#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>
#include <string.h>
#include <net/ethernet.h>
#include <netinet/ip.h>
#define SOCKET int

#endif

#include "errors.h"

class Socket
{
#ifdef _WIN32
    WSADATA wsadata_;
#endif
    SOCKET raw_socket_;
    sockaddr_in socket_addr_;

public:
    Socket();
    ~Socket();
    int Init();
    int Recv(char* buf, int len, int flags);
};

#endif // SOCKET_H
