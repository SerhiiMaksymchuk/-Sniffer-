#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <thread>

#include "filter.h"
#include "analyzer.h"
#include "filemanager.h"
#include "stopwatch.h"
#include "statistic.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_set_filter_button_clicked();

    void on_start_button_clicked();

    void on_stop_button_clicked();

    void on_set_file_name_clicked();

    void on_check_tcp_stateChanged(int arg1);

    void on_check_udp_clicked();

    void on_check_udp_stateChanged(int arg1);

    void on_check_icmp_stateChanged(int arg1);

    void on_check_igmp_stateChanged(int arg1);

    void on_dev_id_list_currentIndexChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    Filter* filter_;
    Analyzer* analyzer_;
    std::thread* sniffing_thread_;
    std::thread* stopwatch_thread_;
    Stopwatch* stopwatch_;
    Statistic* statistic_;
};

#endif // MAINWINDOW_H
