#pragma once
#include <QObject>
#include "irepository.h"
class Usb;

class UsbRepository : public QObject, IRepository<Usb>
{
    Q_OBJECT

    const QString TABLE_NAME = "usb";

    const QString INSERT_QUERY_STRING = "INSERT INTO %1 (VID, PID, serial, name) VALUES ('%2','%3', '%4', '%5');";
    const QString UPDATE_QUERY_STRING = "UPDATE %1 SET VID='%2', PID='%3', serial='%4', name='%5' where id=%6;";
    const QString DELETE_QUERY_STRING = "DELETE FROM %1 WHERE id=%2;";

    static UsbRepository *instance;
    void execQuery(QString queryString);

    int getIdAfterInsert();
    void create(Usb *object);
    void update(Usb *object);
    void remove(Usb *object);
protected:
    explicit UsbRepository(QObject *parent = 0);

public:
    static UsbRepository *Instance();
    QList<Usb*> GetAll();
    void Save(Usb *object);
    void Delete(Usb *object);
signals:

public slots:
};

