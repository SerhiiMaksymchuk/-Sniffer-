#include <QRegExpValidator>

#include "mainwindow.h"
#include <sys/types.h>
#ifndef _WIN32
#include <ifaddrs.h>
#endif

#include "ui_mainwindow.h"
#include "flag_struct.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
#ifndef _WIN32
    ifaddrs *addrs,*tmp;
#endif
    ui->setupUi(this);
    filter_ = new Filter;
    statistic_ = new Statistic;
    statistic_->SetLabels(
                ui->label_Total,
                ui->label_TCP,
                ui->label_UDP,
                ui->label_ICMP,
                ui->label_IGMP,
                ui->label_other
                );
    analyzer_ = new Analyzer(statistic_);
    analyzer_->SetFilter(filter_);
    ui->file_path->setText("log.txt");
    stopwatch_ = new Stopwatch(ui->label_time);
    QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    QRegExp ipRegex ("^" + ipRange
                         + "\\." + ipRange
                         + "\\." + ipRange
                         + "\\." + ipRange + "$");

    QRegExpValidator *ipValidator = new QRegExpValidator(ipRegex, this);
    ui->lineEditIP_dest->setValidator(ipValidator);
    ui->lineEditIP_src->setValidator(ipValidator);
#ifndef _WIN32

    getifaddrs(&addrs);
    tmp = addrs;
    ui->dev_id_list->addItem("All interfaces");
    while (tmp)
    {
        if (tmp->ifa_addr && tmp->ifa_addr->sa_family == AF_PACKET)
            ui->dev_id_list->addItem(tmp->ifa_name);

        tmp = tmp->ifa_next;
    }

    freeifaddrs(addrs);
#endif
}

MainWindow::~MainWindow()
{
    delete filter_;
    delete analyzer_;
    delete stopwatch_;
    delete statistic_;
    delete ui;
}

void MainWindow::on_set_filter_button_clicked()
{
    Flag temp = {
        ui->check_tcp->isChecked(),
        ui->check_udp->isChecked(),
        ui->check_icmp->isChecked(),
        ui->check_igmp->isChecked()
    };
    filter_->SetFilter(temp, ui->lineEditIP_dest->text(),
                       ui->lineEditIP_src->text());
}

void MainWindow::on_start_button_clicked()
{
    if (!analyzer_->IsRunning())
    {
        sniffing_thread_ = new std::thread(&Analyzer::Start, analyzer_,
                                           ui->file_path->text());
        ui->status->setText("Enabled");
        stopwatch_thread_ = new std::thread(&Stopwatch::Start, stopwatch_);
    }
    else
    {
        Message::ShowInfo(ERROR_ALREADY_RUNNING);
    }

}

void MainWindow::on_stop_button_clicked()
{
    if (analyzer_->IsRunning())
    {
        analyzer_->Stop();
        sniffing_thread_->join();
        ui->status->setText("Disabled");
        stopwatch_->Stop();
        stopwatch_thread_->join();
    }
}

void MainWindow::on_set_file_name_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                "log.txt",
                                tr("Text file (*.txt)"));

    ui->file_path->setText(fileName);
    filter_->SetFileName(fileName);
}

void MainWindow::on_check_tcp_stateChanged(int arg1)
{
    filter_->SetTCP(arg1);
}

void MainWindow::on_check_udp_clicked()
{
    filter_->SetTCP(ui->check_tcp->isChecked());
}

void MainWindow::on_check_udp_stateChanged(int arg1)
{
    filter_->SetUDP(arg1);
}

void MainWindow::on_check_icmp_stateChanged(int arg1)
{
    filter_->SetICMP(arg1);
}

void MainWindow::on_check_igmp_stateChanged(int arg1)
{
    filter_->SetIGMP(arg1);
}

void MainWindow::on_dev_id_list_currentIndexChanged(const QString &arg1)
{
    filter_->SetInterface(arg1);
}
