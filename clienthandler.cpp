#include "clienthandler.h"
#include <QTcpSocket>
#include "usbbaseserver.h"


ClientHandler::ClientHandler(QTcpSocket *ClientSocket, QObject *parent):
    QObject(parent),
    clientSocket(ClientSocket)
{
    connect(clientSocket, &QTcpSocket::readyRead, this, &ClientHandler::readyRead);
}

void ClientHandler::Close()
{
    clientSocket->close();
    clientSocket->deleteLater();
}

void ClientHandler::readyRead()
{

}
