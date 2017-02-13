
#include "clienthandler.h"
#include <QTcpSocket>
#include "usbbaseserver.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>
#include <QMutex>
#include "hostrepository.h"
#include "host.h"
#include "rulerepository.h"
#include "rule.h"
#include "usbrepository.h"
#include "usb.h"


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
        if (host->Status())
        {
            answer["code"] = tr("ERROR_AUTH");
            answer["msg"] = tr("Host already connected");
        }
        else
            answer["code"] = tr("SUCCES");
    }
}

QJsonObject ClientHandler::getRule(QJsonObject request)
{
    //TODO: Добавить методы в репозитории для получения объектов данных
    QJsonObject answer;
    auto repUsb = UsbRepository::Instance();
    auto usb = repUsb->GetByVIDandPID(request["VID"], request["PID"]);
    if (usb->ID() == Usb::INVALID_ID)
    {
        answer["code"] = tr("ERROR_USB");
        answer["msg"] = tr("Can't find usb");
        answer["value"] = false;
        return answer;
    }
<<<<<<< Updated upstream
=======
    auto repRule = RuleRepository::Instance();
    auto rule = repRule->GetByHostAndUsb(host, usb);
    if (rule->ID() == Rule::INVALID_ID)
    {
        answer["code"] = tr("ERROR_RULE");
        answer["msg"] = tr("Can't find rule");
        answer["value"] = false;
        return answer;
    }
    answer["code"] = tr("SUCCES");
    answer["value"] = rule->Value();
>>>>>>> Stashed changes
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
        anwer == getRule(request);
    }
    else
    {
        answer["code"] = tr("ERROR_REQ");
    }
    sendClient(answer);
}
