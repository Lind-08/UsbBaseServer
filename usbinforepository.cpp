#include "usbinforepository.h"
#include "usbinfo.h"
#include "dbfacade.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QException>

UsbInfoRepository* UsbInfoRepository::instance = nullptr;

UsbInfoRepository::UsbInfoRepository(QObject *parent) : QObject(parent)
{

}

UsbInfoRepository *UsbInfoRepository::Instance()
{
    if (instance == nullptr)
        instance = new UsbInfoRepository();
    return instance;
}

QList<UsbInfo *> UsbInfoRepository::GetAll()
{
    auto db = DbFacade::Instance();
    QSqlQuery *query = db->CreateQuery();
    if (query->exec("Select * from usb;"))
        throw QException(query->lastError().text());
    QList<UsbInfo*> result;
    do
    {
        UsbInfo *obj = UsbInfo::Create();
        obj->setID(query->value(0));
        obj->setVID(query->value(1));
        obj->setPID(query->value(2));
        obj->setSerial(query->value(3));
        obj->setName(query->value(4));
        result.push_back(obj);
    } while(query->next());
    return result;
}

void UsbInfoRepository::Save(UsbInfo *object)
{
    auto db = DbFacade::Instance();
    QSqlQuery *query = db->CreateQuery();
    QString queryString;
    if (object->ID() == INVALID_ID)
    {
        queryString = QString("INSERT INTO %1 (VID, PID, serial, name,) VALUES('%2','%3', '%4', '%5');")\
            .arg(TABLE_NAME).arg(object->VID()).arg(object->PID()).arg(object->Serial()).arg(object->Name());
    }
    else
    {
        queryString = QString("UPDATE %1 SET VID='%2', PID='%3', serial='%4', name='%5' where id=%6;")\
            .arg(TABLE_NAME).arg(object->VID()).arg(object->PID()).arg(object->Serial()).arg(object->Name()).arg(object->ID());
    }
    if (query->exec(queryString))
        throw QException(query->lastError().text());
}

void UsbInfoRepository::Delete(UsbInfo *object)
{
    auto db = DbFacade::Instance();
    QSqlQuery *query = db->CreateQuery();
    QString queryString = QString("DELET FROM %1 WHERE id=%2;")\
            .arg(TABLE_NAME).arg(object->ID());
    if (query->exec(queryString))
        throw QException(query->lastError().text());
}
