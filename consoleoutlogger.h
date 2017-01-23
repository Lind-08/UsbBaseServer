#ifndef CONSOLEOUTLOGGER_H
#define CONSOLEOUTLOGGER_H

#include <QObject>
#include "ilogmessagesreciever.h"
#include <QTextStream>

class ConsoleOutLogger : public QObject, public ILogMessagesReciever
{
    Q_OBJECT
    QTextStream *out;

public:
    explicit ConsoleOutLogger(QObject *parent = 0);

public slots:
    void onLogMessage(LogMessage message);
};

#endif // CONSOLEOUTLOGGER_H
