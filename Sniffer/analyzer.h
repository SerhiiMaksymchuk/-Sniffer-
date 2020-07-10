#ifndef ANALYZER_H
#define ANALYZER_H

#include "filter.h"
#include "packet_header.h"
#include "filemanager.h"
#include "statistic.h"
#include "message.h"

class Analyzer
{
    bool is_running_;
    Filter* filter_;
    FileManager* file_manager;
    Statistic* statistic_;
    void SetRunning(bool);

public:
    Analyzer(Statistic* stat);
    void Start(QString file_name);
    void Stop();
    int SetFilter(Filter*);
    int SetLog(FileManager*);
    bool IsRunning();
    void Filtering(IPHeader* ip_header, int packet_size);
    virtual ~Analyzer();
};

#endif // ANALYZER_H
