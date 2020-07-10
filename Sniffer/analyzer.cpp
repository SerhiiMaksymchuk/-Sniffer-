#ifndef _WIN32
#include <netinet/ip_icmp.h>	//Provides declarations for icmp header
#include <netinet/udp.h>	//Provides declarations for udp header
#include <netinet/tcp.h>	//Provides declarations for tcp header
#include <netinet/ip.h>	//Provides declarations for ip header
#include <netinet/if_ether.h>	//For ETH_P_ALL
#include <net/ethernet.h>	//For ether_header
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#else
#include <windows.h>

#endif


#include <sys/types.h>
#include <unistd.h>
#include "analyzer.h"

#define IP_HDR_LEN 65536

Analyzer::Analyzer(Statistic* stat)
{
    is_running_ = false;
    statistic_ = stat;
}

int Analyzer::SetFilter(Filter* p_filter)
{
    filter_ = p_filter;

    return OK;
}

void Analyzer::Start(QString file_name)
{
    int saddr_size, data_size;
    struct sockaddr saddr;
    this->SetRunning(true);
    FileManager fm(filter_);
    QByteArray ba = filter_->GetInterface().toLatin1();

    if (!fm.Initialize(file_name, 0))
    {
        Message::ShowInfo(ERROR_FILE);

        return;
    }

    unsigned char *buffer = (unsigned char *) malloc(IP_HDR_LEN); //Its Big!

#ifndef _WIN32

    int sock_raw = socket(AF_PACKET , SOCK_RAW , htons(ETH_P_ALL)) ;
    /* for interface feature */

    if (strcmp(ba.data(), "All interfaces"))
    {
        if (setsockopt(sock_raw , SOL_SOCKET , SO_BINDTODEVICE , ba.data(),
                       strlen( ba.data() ) ))
        {
            perror("Socket Error");
        }
    }

    if (sock_raw < 0)
    {
        is_running_ = false;
        //Print the error with proper message
        perror("Socket Error");
        Message::ShowInfo(ERROR_SOCKET);

        /* XXX
         * messageBox: operation not permitted */
        return;
    }
#else
    WSADATA wsadata;
    WSAStartup(MAKEWORD(2, 2), &wsadata);

    u_long flag = 1;
    #define SIO_RCVALL 0x98000001
    SOCKET sock_raw;


    ioctlsocket(sock_raw, SIO_RCVALL, &flag);
    sock_raw = socket(AF_INET, SOCK_RAW, IPPROTO_IP);
#endif
    while(this->is_running_)
    {
        saddr_size = sizeof saddr;
        //Receive a packet
        /* XXX Make defines*/
        data_size = recvfrom(sock_raw , buffer, IP_HDR_LEN, 0, &saddr,
                             &saddr_size);

        if (data_size < 0)
        {
            printf("Recvfrom error, failed to get packets\n");
            return;
        }
        //Now process the packet
        fm.ProcessPacket(buffer , data_size);
    }

    close(sock_raw);
}

void Analyzer::Stop()
{
    this->SetRunning(false);
}

void Analyzer::SetRunning(bool running)
{
    is_running_ = running;
}

bool Analyzer::IsRunning()
{
    return is_running_;
}

Analyzer::~Analyzer()
{
}
