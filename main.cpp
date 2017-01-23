#include <QCoreApplication>
#include "usbbaseserver.h"
#include "consoleoutlogger.h"
#include <QThread>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ConsoleOutLogger *logger = new ConsoleOutLogger;
    UsbBaseServer *server = new UsbBaseServer(20000);
    QObject::connect(server, &UsbBaseServer::logMessage, logger, &ConsoleOutLogger::onLogMessage);
    server->StartWorking();
    QThread::sleep(10);
    server->StopWorking();
    return a.exec();
}
