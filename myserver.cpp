#include "myserver.h"
#include <stdexcept>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTextStream>

MyServer::MyServer(quint16 port, QObject *parent) : QObject(parent)
{
    listener = new QTcpServer(this);
    port = port;
    isWorked = false;
}

void MyServer::setPort(quint16 port)
{
    if (isWorked)
        throw std::runtime_error("You can not change the port number where the server is running.");
    else
        port = port;
}

void MyServer::StartWork()
{
    if (!listener->listen(QHostAddress::AnyIPv4, port) && !isWorked)
    {
        QString msg = tr("Unable to start the server: %1.").arg(listener->errorString());
        emit logMessage(msg);
        throw std::runtime_error(msg.toStdString());
    }
    else
    {
        connect(listener, SIGNAL(newConnection()), this, SLOT(NewConnection()));
        isWorked = true;
        emit logMessage("Server start listening.");
        emit changeStatus(isWorked);
    }
}

void MyServer::StopWork()
{
    listener->close();
    isWorked = false;
    emit logMessage("Server stop listening.");
    emit changeStatus(isWorked);
}

void MyServer::NewConnection()
{
    QTcpSocket *newClient = listener->nextPendingConnection();
    emit logMessage("Client connected.");
    int id = newClient->socketDescriptor();
    _clients[id] = newClient;
    connect(newClient, SIGNAL(readyRead()), this, SLOT(ReadClient()));
    connect(newClient, SIGNAL(disconnected()), this, SLOT(DisconnectClient()));
}

void MyServer::DisconnectClient()
{
    QTcpSocket *clientSocket = (QTcpSocket*)sender();
    int id = clientSocket->socketDescriptor();
    _clients.remove(id);
}

void MyServer::ReadClient()
{
    QString message = recieveMessage((QTcpSocket*)sender());
    emit logMessage("Message recieved");
    emit recievedMessage(message);
}

void MyServer::sendToClient(QTcpSocket *clientSocket, const QString &message)
{
    QTextStream stream(clientSocket);
    stream << message;
}

QString MyServer::recieveMessage(QTcpSocket *clientSocket)
{
    QTextStream stream(clientSocket);
    QString message = stream.readAll();
    return message;
}

