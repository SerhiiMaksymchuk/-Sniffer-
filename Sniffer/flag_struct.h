#ifndef FLAG_STRUCT_H
#define FLAG_STRUCT_H

struct Flag
{
    bool is_tcp_checked_;
    bool is_udp_checked_;
    bool is_icmp_checked_;
    bool is_igmp_checked_;
};

#endif // FLAG_STRUCT_H
