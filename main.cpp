#include <QCoreApplication>
#include "usbbaseserver.h"
#include "consoleoutlogger.h"
#include <QThread>
#include "dbfacade.h"
#include "usbrepository.h"
#include "usb.h"
#include "host.h"
#include "hostrepository.h"
#include <QDebug>
#include <stdexcept>
#include <QTextStream>
#include <QFile>
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ConsoleOutLogger *logger = new ConsoleOutLogger;
    UsbBaseServer *server = new UsbBaseServer(20000);
    QObject::connect(server, &UsbBaseServer::logMessage, logger, &ConsoleOutLogger::onLogMessage);
    try
    {
        if (QFile::exists("usb_db.sqlite"))
            DbFacade::InitDbFacade("QSQLITE", "usb_db.sqlite");
        else
        {
            qDebug() << QObject::tr("Не найден файл базы данных");
            return 0;
        }
    }
    catch (std::exception &e)
    {
        qDebug() << QString(e.what());
        return a.exec();
    }
    server->StartWorking();
    return a.exec();
}
