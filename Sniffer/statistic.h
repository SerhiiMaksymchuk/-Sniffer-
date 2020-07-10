#ifndef STATISTIC_H
#define STATISTIC_H

#include <QLabel>

class Statistic
{
private:
    unsigned int count_all_;
    unsigned int tcp_;
    unsigned int udp_;
    unsigned int icmp_;
    unsigned int igmp_;
    unsigned int other_;
    QLabel* label_total_;
    QLabel* label_tcp_;
    QLabel* label_udp_;
    QLabel* label_icmp_;
    QLabel* label_igmp_;
    QLabel* label_other_;

public:
    Statistic();
    void IncreaseTCP();
    void IncreaseUDP();
    void IncreaseICMP();
    void IncreaseIGMP();
    void Increase();
    void SetLabels(
            QLabel* total,
            QLabel* tcp,
            QLabel* udp,
            QLabel* icmp,
            QLabel* igmp,
            QLabel* oth
                  );
};

#endif // STATISTIC_H
