#pragma once
#include <QObject>
#include "ilogmessagescreator.h"

class QTcpSocket;
class QJsonObject;
class Host;
enum class ClientState;

class ClientHandler : public QObject, public ILogMessagesCreator
{
    Q_OBJECT
    QTcpSocket *clientSocket;
    ClientState state;
    Host *machine;
    QString clientID;

    QJsonObject recieveMessage(QTcpSocket *clientSocket);
    QJsonObject getJson(QString rawMessage);
    void processRequest(QJsonObject request);

    void sendClient(QJsonObject answer);

    QJsonObject authentiate(QJsonObject request);
    QJsonObject getRule(QJsonObject request);
    QJsonObject getRulesHash();

    QString calculateRulesHash(Host *host);

private slots:
    void readyRead();

public:
    explicit ClientHandler(QTcpSocket *ClientSocket, QObject *parent = 0);
    void Close();

public slots:

signals:
    void clientDisconnected();
    void logMessage(LogMessage);
};
