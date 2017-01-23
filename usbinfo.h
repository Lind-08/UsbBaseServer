#ifndef USBINFO_H
#define USBINFO_H

#include <QObject>

class UsbInfo : public QObject
{
    Q_OBJECT
public:
    explicit UsbInfo(QObject *parent = 0);

signals:

public slots:
};

#endif // USBINFO_H