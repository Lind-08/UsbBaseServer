#include "usbinfo.h"


UsbInfo::UsbInfo(QObject *parent) : QObject(parent)
{

}

UsbInfo* UsbInfo::Create(QObject *parent)
{
    UsbInfo *info = new UsbInfo(parent);
    info->id = UsbInfo::INVALID_ID;
    return info;
}

void UsbInfo::setID(const qint32 ID)
{
    id = ID;
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

