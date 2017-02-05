#pragma once
#include <QObject>

class UsbInfo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString VID READ VID WRITE setVID)
    Q_PROPERTY(QString PID READ PID WRITE setPID)
    Q_PROPERTY(QString Serial READ Serial WRITE setSerial)
    Q_PROPERTY(QString Name READ Name WRITE setName)

    QString id;
    QString vid;
    QString pid;
    QString serial;
    QString name;

    explicit UsbInfo(QObject *parent = 0);
public:
    static UsbInfo* Create(QObject *parent = 0);

    void setVID(const QString VID);
    inline QString VID()
    {
        return vid;
    }

    void setPID(const QString PID);
    inline QString PID()
    {
        return pid;
    }

    void setSerial(const QString Serial);
    inline QString Serial()
    {
        return serial;
    }

    void setName(const QString Name);
    inline QString Name()
    {
        return name;
    }

signals:

public slots:
};


