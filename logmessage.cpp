#include "logmessage.h"
#include <QDateTime>

LogMessage LogMessage::Create(QString Message)
{
    return LogMessage(Message, QDateTime::currentDateTime());
}

LogMessage::LogMessage(QString Message, QDateTime Timestamp, QObject *parent)
{
    message = Message;
    timestamp = Timestamp;
}

