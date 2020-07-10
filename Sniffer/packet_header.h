#ifndef PACKET_HEADER_H
#define PACKET_HEADER_H

struct IPHeader {
    unsigned char iph_verlen;
    unsigned char iph_tos;
    unsigned short iph_length;
    unsigned short iph_id;
    unsigned short iph_offset;
    unsigned char iph_ttl;
    unsigned char iph_protocol;
    unsigned short iph_xsum;
    unsigned long iph_src;
    unsigned long iph_dest;
};

struct TCPHeader
{
    unsigned short src_port;
    unsigned short dest_port;
    unsigned long seq_num;
    unsigned long ack_num;
    unsigned short data_offset_flags;
    unsigned short window_size;
    unsigned short tcp_checksum;
    unsigned short tcp_urgent_ptr;
};

struct UDPHeader
{
    unsigned short src_port;
    unsigned short dest_port;
    unsigned short length;
    unsigned short checksum;
};

struct ICMPHeader
{
    unsigned char type;
    unsigned char code;
    unsigned short checksum;
    unsigned int rest_of_header;
};

struct IGMPHeader
{
    unsigned char type;
    unsigned char max_response_time;
    unsigned short checksum;
    unsigned int group_address;
};

struct IPAddress{
    unsigned char address[4];
};

#endif // PACKET_HEADER_H
