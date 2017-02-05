#include "usbinforepository.h"
#include "usbinfo.h"

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

QList<UsbInfo> UsbInfoRepository::GetAll()
{

}

void UsbInfoRepository::Save(UsbInfo *object)
{

}

void UsbInfoRepository::Delete(UsbInfo *object)
{

}
