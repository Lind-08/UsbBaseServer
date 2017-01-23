#pragma once
#include <QObject>
#include "ilogmessagescreator.h"

class QTcpSocket;
enum class ClientState;

class ClientHandler : public QObject, public ILogMessagesCreator
{
    Q_OBJECT
    QTcpSocket *clientSocket;
    ClientState state;

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
