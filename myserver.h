#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>
#include <QThread>
#include <QMap>
#include <QTcpSocket>
#include <QTcpServer>

class MyServer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool IsWorked READ IsWorked)
protected:
    QMap<int, QTcpSocket*> _clients;
    QTcpServer* listener;
    quint16 port;
    bool isWorked;
public:
    explicit MyServer(quint16 Port = 5554, QObject *parent = 0);

    inline bool IsWorked()
    {
        return isWorked;
    }

public slots:
    virtual void NewConnection();
    void DisconnectClient();
    void ReadClient();
    void StartWork();
    void StopWork();

signals:
    void recievedMessage(QString);
    void logMessage(QString);
    void changeStatus(bool);

protected:
    void sendToClient(QTcpSocket* pSocket, const QString& str);
    QString recieveMessage(QTcpSocket* clientSocket);
};

#endif // MYSERVER_H
