#ifndef FILTER_H
#define FILTER_H

#include <QString>
#include <QStringList>
#include "packet_header.h"
#include "flag_struct.h"
#include "errors.h"

class Filter
{
    Flag flags_;
    bool is_init_;
    IPAddress ip_destination_;
    IPAddress ip_source_;
    QString file_name_;
    QString dev_if_name_;
    bool ip_dest_set_;
    bool ip_src_set_;
    bool write_data_dump_;
    bool write_ip_header_;

    void SetDataDump(bool);
    void SetIPHeader(bool);

public:
    Filter();

    bool GetTCP();
    bool GetUDP();
    bool GetICMP();
    bool GetIGMP();
    bool GetInit();

    void SetTCP(bool changed);
    void SetUDP(bool changed);
    void SetICMP(bool changed);
    void SetIGMP(bool changed);

    IPAddress GetIPSrc();
    IPAddress GetIPDest();
    bool GetSrcSet();
    bool GetDestSet();
    void SetFileSettings(bool data, bool ip);
    void SetFileName(QString);
    int SetFilter(Flag f, QString ip_dest, QString ip_src);

    void SetInterface(QString if_name);
    QString GetInterface();
};

#endif // FILTER_H
