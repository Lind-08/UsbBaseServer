#include <QCoreApplication>
#include "usbbaseserver.h"
#include "consoleoutlogger.h"
#include <QThread>
#include "dbfacade.h"
#include "usbinforepository.h"
#include "usbinfo.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ConsoleOutLogger *logger = new ConsoleOutLogger;
    UsbBaseServer *server = new UsbBaseServer(20000);
    QObject::connect(server, &UsbBaseServer::logMessage, logger, &ConsoleOutLogger::onLogMessage);
    try
    {
        DbFacade::InitDbFacade("QSQLITE", "usb_db.sqlite");
    }
    catch (std::exception &e)
    {
        qDebug << QString(e.what());
        return a.exec();
    }
    auto info = UsbInfo::Create();
    info->setVID("testVID");
    info->setPID("testPID");
    info->setSerial("testSerial");
    info->setName("testName");
    auto info1 = UsbInfo::Create();
    info->setVID("testVID1");
    info->setPID("testPID1");
    info->setSerial("testSerial1");
    info->setName("testName1");
    auto rep = UsbInfoRepository::Instance();
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
