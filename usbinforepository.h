#ifndef USBINFOREPOSITORY_H
#define USBINFOREPOSITORY_H

#include <QObject>

class UsbInfoRepository : public QObject
{
    Q_OBJECT
public:
    explicit UsbInfoRepository(QObject *parent = 0);

signals:

public slots:
};

#endif // USBINFOREPOSITORY_H