#include "usbinfo.h"


UsbInfo::UsbInfo(QObject *parent) : QObject(parent)
{

}

UsbInfo* UsbInfo::Create(QObject *parent)
{
    UsbInfo *info = new UsbInfo(parent);
    return info;
}

void UsbInfo::setVID(const QString VID)
{
    vid = VID;
}

void UsbInfo::setPID(const QString PID)
{
    pid = PID;
}

void UsbInfo::setSerial(const QString Serial)
{
    serial = Serial;
}

void UsbInfo::setName(const QString Name)
{
    name = Name;
}

