#pragma once
#include <QObject>
#include "irepository.h"
class UsbInfo;

class UsbInfoRepository : public QObject, IRepository<UsbInfo>
{
    Q_OBJECT

    static UsbInfoRepository *instance;
//    void create();
//    void update();
//    void remove();
protected:
    explicit UsbInfoRepository(QObject *parent = 0);

public:
    UsbInfoRepository *Instance();
    QList<UsbInfo*> GetAll();
    void Save(UsbInfo *object);
    void Delete(UsbInfo *object);
signals:

public slots:
};

