#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QTime>
#include <QLabel>
#include <thread>
#include <chrono>

class Stopwatch
{
    QTime time_;
    bool is_running_;
    QLabel* output_;
public:
    Stopwatch(QLabel*);
    void Start();
    void Stop();
};

#endif // STOPWATCH_H
