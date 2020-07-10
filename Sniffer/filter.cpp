#include "filter.h"

Filter::Filter()
{
    is_init_= false;
    flags_.is_tcp_checked_ = false;
    flags_.is_udp_checked_ = false;
    flags_.is_icmp_checked_ = false;
    flags_.is_igmp_checked_ = false;
    ip_dest_set_ = false;
    ip_src_set_ =false;
    file_name_ = "log.txt";
    dev_if_name_ = "All interfaces";
}

void Filter::SetFileName(QString temp)
{
    file_name_ = temp;
}

bool Filter::GetTCP()
{
    return flags_.is_tcp_checked_;
}

bool Filter::GetUDP()
{
    return flags_.is_udp_checked_;
}

bool Filter::GetICMP()
{
    return flags_.is_icmp_checked_;
}

bool Filter::GetIGMP()
{
    return flags_.is_igmp_checked_;
}

bool Filter::GetInit()
{
    return is_init_;
}

IPAddress Filter::GetIPDest()
{
    return ip_destination_;
}

bool Filter::GetDestSet()
{
    return ip_dest_set_;
}

IPAddress Filter::GetIPSrc()
{
    return ip_source_;
}

bool Filter::GetSrcSet()
{
    return ip_src_set_;
}

int Filter::SetFilter(Flag f, QString ip_dest, QString ip_src)
{
    flags_ = f;
    is_init_ = true;

    if (!ip_dest.isEmpty())
    {
        QStringList ip_bytes = ip_dest.split(".");
        QString temp;
        if (ip_bytes.size() >= 4)
        {
            for (int i = 0; i < 4; ++i)
            {
                temp = ip_bytes.at(i);
                ip_destination_.address[i] = static_cast<char>(temp.toInt());
            }
            ip_dest_set_ = true;
        }
        else
           return ERROR_SET_FILTER;
    }

    if (!ip_src.isEmpty())
    {
        QStringList ip_bytes = ip_src.split(".");
        QString temp;
        if (ip_bytes.size() >= 4)
        {
            for (int i = 0; i < 4; ++i)
            {
                temp = ip_bytes.at(i);
                ip_source_.address[i] = static_cast<char>(temp.toInt());
            }
            ip_src_set_ = true;
        }
        else
           return ERROR_SET_FILTER;
    }
    return OK;

}

void Filter::SetDataDump(bool flag)
{
    write_data_dump_ = flag;
}



void Filter::SetIPHeader(bool flag)
{
    write_ip_header_ = flag;
}

void Filter::SetFileSettings(bool data, bool ip)
{
    SetDataDump(data);
    SetIPHeader(ip);
}

void Filter::SetTCP(bool changed)
{
    flags_.is_tcp_checked_ = changed;
}

void Filter::SetUDP(bool changed)
{
    flags_.is_udp_checked_ = changed;
}

void Filter::SetICMP(bool changed)
{
    flags_.is_icmp_checked_ = changed;
}

void Filter::SetIGMP(bool changed)
{
    flags_.is_igmp_checked_ = changed;
}

void Filter::SetInterface(QString if_name)
{
    dev_if_name_ = if_name;
}

QString Filter::GetInterface()
{
    return dev_if_name_;
}
