
#include "clienthandler.h"
#include <QTcpSocket>
#include "usbbaseserver.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>
#include "hostrepository.h"
#include "host.h"
#include "rulerepository.h"
#include "rule.h"
#include "usbrepository.h"
#include "usb.h"
#include <QCryptographicHash>


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
    /*if (host->Status())
    {
        answer["code"] = tr("ERROR_AUTH");
        answer["msg"] = tr("Host already connected");
    }
    else*/
    {
        machine = host;
        host->setStatus(true);
        rep->Save(host);
        answer["code"] = tr("SUCCES");
    }
    return answer;
}

QJsonObject ClientHandler::getRule(QJsonObject request)
{
    QJsonObject answer;
    auto repUsb = UsbRepository::Instance();
    auto usb = repUsb->GetByVIDandPID(request["VID"].toString(), request["PID"].toString());
    if (usb->ID() == Usb::INVALID_ID)
    {
        answer["code"] = tr("ERROR_USB");
        answer["msg"] = tr("Can't find usb");
        answer["value"] = false;
        return answer;
    }
    auto repRule = RuleRepository::Instance();
    auto rule = repRule->GetByHostAndUsb(machine, usb);
    if (rule->ID() == Rule::INVALID_ID)
    {
        answer["code"] = tr("ERROR_RULE");
        answer["msg"] = tr("Can't find rule");
        answer["value"] = false;
        return answer;
    }
    answer["code"] = tr("SUCCES");
    answer["value"] = rule->Value();
    answer["rules_hash"] = calculateRulesHash(machine);
    return answer;
}

QJsonObject ClientHandler::getRulesHash()
{
    QJsonObject answer;
    answer["code"] = "SUCCES";
    answer["rules_hash"] = calculateRulesHash(machine);
    return answer;
}

QString ClientHandler::calculateRulesHash(Host *host)
{
    auto rep = RuleRepository::Instance();
    auto rules = rep->GetByHost(host);
    QCryptographicHash hash(QCryptographicHash::Md5);
    if (!rules.empty())
    {
        for(auto rule: rules)
        {
            QByteArray array;
            array.append(rule->ID());
            array.append(rule->Host_ID());
            array.append(rule->Usb_ID());
            array.append(rule->Value());
            hash.addData(array);
        }
    }
    return QString(hash.result());
}

void ClientHandler::processRequest(QJsonObject request)
{
    QJsonObject answer;
    bool needDisconnect = false;
    answer["id"] = tr("server");
    QString code = request["code"].toString();
    if (code == "HELLO")
    {
        answer = authentiate(request);
        if (answer["code"].toString() != tr("SUCCES"))
        {
            sendClient(answer);
            needDisconnect = true;
        }
    }
    else
    if (code == "GET_RULE")
    {
        answer = getRule(request);
    }
    else
    if (code == "GET_RULES_HASH")
    {
        answer = getRulesHash();
    }
    else
    if (code == "BYE")
    {
        answer["code"] = "SEE_YOU";
        needDisconnect = true;
    }
    else
    {
        answer["code"] = tr("ERROR_REQ");
    }
    sendClient(answer);
    if (needDisconnect)
        emit clientDisconnected();
}
