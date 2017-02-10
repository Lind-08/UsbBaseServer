#include "usbrepository.h"
#include "usb.h"
#include "dbfacade.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QException>
#include <QVariant>
#include <stdexcept>
#include <QSqlRecord>
#include "usb.h"

UsbRepository* UsbRepository::instance = nullptr;

UsbRepository::UsbRepository(QObject *parent) :
    QObject(parent),
    Parent()
{

}

QString UsbRepository::getInsertQuery(Usb *object)
{
    return INSERT_QUERY_STRING.arg(TABLE_NAME).arg(object->VID()).arg(object->PID()).arg(object->Serial()).arg(object->Name());
}

QString UsbRepository::getUpdateQuery(Usb *object)
{
    return UPDATE_QUERY_STRING.arg(TABLE_NAME).arg(object->VID()).arg(object->PID()).arg(object->Serial()).arg(object->Name()).arg(object->ID());
}

QString UsbRepository::getDeleteQuery(Usb *object)
{
    return DELETE_QUERY_STRING.arg(TABLE_NAME).arg(object->ID());
}

QString UsbRepository::getQueryForID()
{
    return Parent::GET_ID_QUERY.arg(TABLE_NAME);
}


UsbRepository *UsbRepository::Instance()
{
    if (instance == nullptr)
        instance = new UsbRepository();
    return instance;
}

/*void UsbRepository::execQuery(QString queryString)
{
    auto db = DbFacade::Instance();
    QSqlQuery *query = db->CreateQuery();
    if(!query->exec(queryString))
    {
        throw std::runtime_error(query->lastError().text().toStdString());
    }
}*/

/*void UsbRepository::create(Usb *object)
{
    execQuery(INSERT_QUERY_STRING.arg(TABLE_NAME).arg(object->VID()).arg(object->PID()).arg(object->Serial()).arg(object->Name()));

}*/

/*void UsbRepository::update(Usb *object)
{
    execQuery(UPDATE_QUERY_STRING.arg(TABLE_NAME).arg(object->VID()).arg(object->PID()).arg(object->Serial()).arg(object->Name()).arg(object->ID()));
}*/

/*int UsbRepository::getIdAfterInsert()
{
    auto db = DbFacade::Instance();
    QSqlQuery *query = db->CreateQuery();
    QString queryString = QString("SELECT id FROM %1;").arg(TABLE_NAME);
    if (!query->exec(queryString))
    {
       query->last();
       auto rec = query->record();
       return query->value(rec.indexOf("id")).toInt();
    }
    else
    {
        throw std::runtime_error(query->lastError().text().toStdString());
    }
}*/


QList<Usb *> UsbRepository::GetAll()
{
    auto db = DbFacade::Instance();
    QSqlQuery *query = db->CreateQuery();
    if (!query->exec(getQueryForID()))
        throw std::runtime_error(query->lastError().text().toStdString());
    QList<Usb*> result;
    do
    {
        Usb *obj = Usb::Create();
        obj->setID(query->value(0).toInt());
        obj->setVID(query->value(1).toString());
        obj->setPID(query->value(2).toString());
        obj->setSerial(query->value(3).toString());
        obj->setName(query->value(4).toString());
        if (obj->ID() != 0)
        {
            result.push_back(obj);
        }
    } while(query->next());
    return result;
}

void UsbRepository::Save(Usb *object)
{
    if (object->ID() == Usb::INVALID_ID)
    {
        create(object);
        object->setID(getIdAfterInsert());
    }
    else
    {
        update(object);
    }
}

void UsbRepository::Delete(Usb *object)
{
    if (object->ID() != Usb::INVALID_ID)
        remove(object);
}
