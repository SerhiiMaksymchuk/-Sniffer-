#include "message.h"

Message::Message()
{

}

void Message::ShowInfo(int error)
{
    QMessageBox msgBox;

    switch (error)
    {
    case ERROR_SOCKET:
        msgBox.setText("Error socket initilazation.");
        msgBox.setDetailedText("Check your permissions. To work property need"
                               " root/admin permissions.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
        break;

    case ERROR_BIND:
        msgBox.setText("Socket error.");
        msgBox.setDetailedText("Check availeble interface or your permission.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
        break;

    case ERROR_FILE:
        msgBox.setText("Error with file.");
        msgBox.setDetailedText("Check path and name. Can't open/create file.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
        break;

    case ERROR_PROMISCUOS:
        msgBox.setText("Error to enable Promiscuos mode!");
        msgBox.setDetailedText("You need administrator privilege");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
        break;

    case ERROR_FILTER_NOT_SET:
        msgBox.setText("Error: filter not set!");
        msgBox.setDetailedText("Apply your filter first");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
        break;

    case ERROR_FILE_NOT_SET:
        msgBox.setText("Error: file not set!");
        msgBox.setDetailedText("Apply your file configuration!");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
        break;

    case ERROR_ALREADY_RUNNING:
        msgBox.setText("Sniffer already running!");
        msgBox.setDetailedText("You already start the sniffer. If you wanna "
                               "restart it, just press stop button and then push"
                               " start button.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
        break;

    default:
        msgBox.setText("Error");
        msgBox.exec();
        break;
    }

}
