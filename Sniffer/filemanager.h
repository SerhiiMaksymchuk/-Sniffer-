#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QFile>
#include <QTextStream>
#include <iomanip>
#ifndef _WIN32
#include <netinet/ip_icmp.h>	//Provides declarations for icmp header
#include <netinet/udp.h>	//Provides declarations for udp header
#include <netinet/tcp.h>	//Provides declarations for tcp header
#include <netinet/ip.h>	//Provides declarations for ip header
#include <netinet/if_ether.h>	//For ETH_P_ALL
#include<net/ethernet.h>	//For ether_header
#include<arpa/inet.h>
#else
#include <winsock2.h>
#include <windows.h>
#endif

#include "filter.h"
#include "packet_header.h"
#include "errors.h"

class FileManager
{
    QString name_;
    bool is_init_;
    Filter *filter_;

    void PrintEthernetHeader(unsigned char* Buffer, int Size);
    void PrintIpHeader(unsigned char* , int);
    void PrintTcpPacket(unsigned char * , int );
    void PrintUdpPacket(unsigned char * , int );
    void PrintIcmpPacket(unsigned char* , int );
    void PrintData (unsigned char* , int);
public:

    FILE *logfile;
    sockaddr_in source,dest;
    int tcp=0;
    int udp=0;
    int icmp=0;
    int others=0;
    int igmp=0;
    int total=0;

    FileManager(Filter *fl);
    void ProcessPacket(unsigned char* , int);
    bool Initialize(QString file_name, bool append);

    bool GetInit();
};

#endif // FILEMANAGER_H
