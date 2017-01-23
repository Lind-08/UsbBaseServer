#include "usbbaseserver.h"
#include "clienthandler.h"
#include <QTcpServer>

UsbBaseServer::UsbBaseServer(quint16 ServerPort, QObject *parent) : QObject(parent)
{
    serverPort = ServerPort;
    listener = new QTcpServer();
    handlers = new QList<ClientHandler*>();
    connect(listener, &QTcpServer::newConnection, this, &UsbBaseServer::onNewConnection);
}

void UsbBaseServer::StartWorking()
{
    if (!listener->listen(QHostAddress::Any, serverPort))
    {
        listener->close();
        throw listener->errorString();
    }
}

void UsbBaseServer::StopWorking()
{
    listener->close();
}

void UsbBaseServer::onNewConnection()
{
    QTcpSocket *client = reinterpret_cast<QTcpSocket*>(sender());
    ClientHandler *handler = new ClientHandler(client, this);
    handlers->push_back(handler);
    connect(handler, &ClientHandler::clientDisconnected, this, &UsbBaseServer::onClientDisconnected);
}
