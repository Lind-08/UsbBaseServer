#pragma once
#include <QObject>
class LogMessage;

class ILogMessagesCreator
{
    Q_SIGNAL virtual void logMessage(LogMessage message) = 0;
};
