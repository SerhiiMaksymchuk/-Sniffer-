#include "statistic.h"

Statistic::Statistic()
{
    count_all_ = 0;
    tcp_ = 0;
    udp_ = 0;
    icmp_ = 0;
    igmp_ = 0;
    other_ = 0;
}

void Statistic::SetLabels(QLabel* total, QLabel* tcp, QLabel* udp, QLabel* icmp,
                          QLabel* igmp, QLabel* oth)
{
    label_total_ = total;
    label_tcp_ = tcp;
    label_udp_ = udp;
    label_icmp_ = icmp;
    label_igmp_ = igmp;
    label_other_ = oth;
}

void Statistic::IncreaseTCP()
{
    ++count_all_;
    ++tcp_;
    label_total_->setText(QString::number(count_all_));
    label_tcp_->setText(QString::number(tcp_));
}

void Statistic::IncreaseUDP()
{
    ++count_all_;
    ++udp_;
    label_total_->setText(QString::number(count_all_));
    label_udp_->setText(QString::number(udp_));
}

void Statistic::IncreaseICMP()
{
    ++count_all_;
    ++icmp_;
    label_total_->setText(QString::number(count_all_));
    label_icmp_->setText(QString::number(icmp_));
}

void Statistic::IncreaseIGMP()
{
    ++count_all_;
    ++igmp_;
    label_total_->setText(QString::number(count_all_));
    label_igmp_->setText(QString::number(igmp_));
}

void Statistic::Increase()
{
    ++count_all_;
    ++other_;
    label_total_->setText(QString::number(count_all_));
    label_other_->setText(QString::number(other_));
}
