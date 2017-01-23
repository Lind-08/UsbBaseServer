#ifndef CONSOLEOUTLOGGER_H
#define CONSOLEOUTLOGGER_H

#include <QObject>

class ConsoleOutLogger : public QObject
{
    Q_OBJECT
public:
    explicit ConsoleOutLogger(QObject *parent = 0);

signals:

public slots:
};

#endif // CONSOLEOUTLOGGER_H