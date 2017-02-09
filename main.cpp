#include <QCoreApplication>
#include "usbbaseserver.h"
#include "consoleoutlogger.h"
#include <QThread>
#include "dbfacade.h"
#include "usbrepository.h"
#include "usb.h"
#include <QDebug>
#include <stdexcept>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ConsoleOutLogger *logger = new ConsoleOutLogger;
    UsbBaseServer *server = new UsbBaseServer(20000);
    QObject::connect(server, &UsbBaseServer::logMessage, logger, &ConsoleOutLogger::onLogMessage);
    try
    {
        DbFacade::InitDbFacade("QSQLITE", "E:\\test\\usb_db.sqlite");
    }
    catch (std::exception &e)
    {
        qDebug() << QString(e.what());
        return a.exec();
    }
    auto info = Usb::Create();
    info->setVID("testVID");
    info->setPID("testPID");
    info->setSerial("testSerial");
    info->setName("testName");
    auto info1 = Usb::Create();
    info1->setVID("testVID1");
    info1->setPID("testPID1");
    info1->setSerial("testSerial1");
    info1->setName("testName1");
    auto rep = UsbRepository::Instance();
    rep->Save(info);
    rep->Save(info1);
    info->setVID("test_VID_after_update");
    rep->Save(info);
    rep->Delete(info1);
    server->StartWorking();
    QThread::sleep(10);
    server->StopWorking();
    return a.exec();
}
