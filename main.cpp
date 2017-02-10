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

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ConsoleOutLogger *logger = new ConsoleOutLogger;
    UsbBaseServer *server = new UsbBaseServer(20000);
    QObject::connect(server, &UsbBaseServer::logMessage, logger, &ConsoleOutLogger::onLogMessage);
    try
    {
        DbFacade::InitDbFacade("QSQLITE", "D:\\test\\usb_db.sqlite");
    }
    catch (std::exception &e)
    {
        qDebug() << QString(e.what());
        return a.exec();
    }
    Usb *usb = Usb::Create();
    usb->setVID("testVID");
    usb->setPID("testPID");
    usb->setSerial("testSerial");
    usb->setName("testName");
    auto rep = UsbRepository::Instance();
    rep->Save(usb);
    Usb *usb1 = Usb::Create();
    usb1->setVID("testVID1");
    usb1->setPID("testPID1");
    usb1->setSerial("testSerial1");
    usb1->setName("testName1");
    rep->Save(usb1);
    auto list = rep->GetAll();
    QTextStream stream(stdout);
    foreach (auto usb, list)
    {
        stream << usb->ID() << ":" << usb->VID() << endl;
    }
    return a.exec();
}
