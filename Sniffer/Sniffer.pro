#-------------------------------------------------
#
# Project created by QtCreator 2018-08-11T13:47:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Sniffer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    filter.cpp \
    analyzer.cpp \
    socket.cpp \
    filemanager.cpp \
    statistic.cpp \
    stopwatch.cpp \
    message.cpp

HEADERS  += mainwindow.h \
    filter.h \
    analyzer.h \
    socket.h \
    filemanager.h \
    errors.h \
    flag_struct.h \
    packet_header.h \
    statistic.h \
    stopwatch.h \
    message.h

FORMS    += mainwindow.ui


win32 {
    LIBS += -lws2_32
    RC_FILE = Sniffer.rc
}
