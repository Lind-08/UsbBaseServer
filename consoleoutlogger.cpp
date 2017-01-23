#include "consoleoutlogger.h"

ConsoleOutLogger::ConsoleOutLogger(QObject *parent) : QObject(parent)
{
    out = new QTextStream(stdout);
}

void ConsoleOutLogger::onLogMessage(LogMessage message)
{
    (*out) << message.Timestamp().toString() << " : " << message.Message() << endl;
}
