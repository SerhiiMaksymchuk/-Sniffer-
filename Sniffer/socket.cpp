#include "socket.h"

Socket::Socket()
{

}

int Socket::Init()
{
#ifdef _WIN32
    WSAStartup(MAKEWORD(2, 2), &wsadata_);

    CHAR host_name[16];
    gethostname(host_name, sizeof host_name);

    HOSTENT *pointer_host = gethostbyname(host_name);

    raw_socket_ = socket(AF_INET, SOCK_RAW, IPPROTO_IP);
    if (raw_socket_ == INVALID_SOCKET)
    {
        qDebug() << "Can't create socket" << endl;
        return ERROR_SOCKET;
    }


    socket_addr_.sin_family = AF_INET;
    socket_addr_.sin_addr.s_addr = ((struct in_addr*)pointer_host->h_addr_list[0])->s_addr;

    int res_bind = bind(raw_socket_, (SOCKADDR*)&socket_addr_, sizeof(SOCKADDR));

    if (res_bind != 0)
    {
       qDebug() << "Cant bind" << endl;
       return ERROR_BIND;
    }
    else
    {
       qDebug() << "Bind succes" << endl;
    }

    // promiscuos mode
    DWORD flag = TRUE;
    ioctlsocket(raw_socket_, SIO_RCVALL, &flag); //promiscuos mode

    if(ioctlsocket(raw_socket_, SIO_RCVALL, &flag) == SOCKET_ERROR)
    {
       qDebug() << "Can't turn on promiscuous" << endl;
       return ERROR_PROMISCUOS;
    }
    else
    {
       qDebug() << "Promiscuous turned on" << endl;
    }
#else
    raw_socket_ = socket(AF_PACKET, SOCK_RAW , htons(ETH_P_ALL)) ;
    if (raw_socket_ < 0)
    {
        return ERROR_SOCKET;
    }

#endif


    return OK;
}

int Socket::Recv(char* buffer, int length, int flags)
{
#ifdef _WIN32
    return recv(this->raw_socket_, buffer, length, flags);
#else
    int sock_addr_size = sizeof(sockaddr);
    return recvfrom(this->raw_socket_, buffer, length, flags, (sockaddr*)&socket_addr_, (socklen_t*)&sock_addr_size);
#endif
}

Socket::~Socket()
{
#ifdef _WIN32
    closesocket(raw_socket_);
#endif
}
