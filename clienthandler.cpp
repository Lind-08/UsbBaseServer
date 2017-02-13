#include "clienthandler.h"
#include <QTcpSocket>
#include "usbbaseserver.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>
#include <QMutex>
#include "hostrepository.h"
#include "host.h"


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

QJsonObject ClientHandler::authentiate(QJsonObject request)
{
    QJsonObject answer;
    auto rep = HostRepository::Instance();
    auto host = rep->GetBySecret(request["secret"].toString());
    if (host->ID() == Host::INVALID_ID)
    {
        answer["code"] = tr("ERROR_AUTH");
        answer["msg"] = tr("Unknown host");
    }
    else
    if (host->Status())
    {
        answer["code"] = tr("ERROR_AUTH");
        answer["msg"] = tr("Host already connected");
    }
    else
    {
        answer["code"] = tr("SUCCES");
    }
    return answer;
}

void ClientHandler::processRequest(QJsonObject request)
{
    QJsonObject answer;
    answer["id"] = tr("server");
    if (request["code"] == "HELLO")
    {
        answer = authentiate(request);
        if (answer["code"] != tr("SUCCES"))
        {
            sendClient(answer);
            emit clientDisconnected();
        }
    }
    else
    if (request["code"] == "GET_RULE")
    {

    }
    else
    {
        answer["code"] = tr("ERROR_REQ");
    }
    sendClient(answer);
}
