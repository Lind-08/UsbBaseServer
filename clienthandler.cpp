#include "clienthandler.h"
#include <QTcpSocket>
#include "usbbaseserver.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>
#include <QMutex>


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
    QJsonObject request = recieveMessage(clientSocket);
    emit logMessage(LogMessage::Create(tr("Message recieved")));
    processRequest(request);
}

QJsonObject ClientHandler::recieveMessage(QTcpSocket *clientSocket)
{
    QTextStream stream(clientSocket);
    QString message = stream.readAll();
    return getJson(message);
}

QJsonObject ClientHandler::getJson(QString rawMessage)
{
    return QJsonDocument::fromJson(rawMessage.toUtf8()).object();
}

void ClientHandler::sendClient(QJsonObject answer)
{
    QTextStream stream(clientSocket);
    QJsonDocument doc(answer);
    stream << doc.toJson();
}

void ClientHandler::processRequest(QJsonObject request)
{
    QJsonObject answer;
    answer["id"] = tr("server");
    if (request["code"] == "HELLO")
    {
        answer["code"] = tr("SUCCESS");
    }
    else
    {
        answer["code"] = tr("ERROR_REQ");
    }
    sendClient(answer);
}
