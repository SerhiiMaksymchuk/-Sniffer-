#include "stopwatch.h"

Stopwatch::Stopwatch(QLabel* out)
{
    output_ = out;
    is_running_ = false;
}

void Stopwatch::Start()
{
    is_running_ = true;
    time_.restart();
    int hours = 0;
    int minuts = 0;
    int seconds = 0;
    int temp = 0;
    while (is_running_)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        temp = time_.elapsed();
        seconds = temp / 1000;
        minuts = temp / 60000;
        hours = temp / 3600000;
        QTime tvalue(hours, minuts, seconds);
        output_->setText(tvalue.toString("hh:mm::ss"));
    }
}

void Stopwatch::Stop()
{
    is_running_ = false;
}
