#ifndef MESSAGE_H
#define MESSAGE_H

#include <QMessageBox>
#include "errors.h"

class Message
{
public:
    Message();
    static void ShowInfo(int error);
};

#endif // MESSAGE_H
