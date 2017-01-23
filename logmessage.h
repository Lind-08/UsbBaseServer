#pragma once
class QObject;
class QString;
class QDateTime;

class LogMessage : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString Message READ Message)
    Q_PROPERTY(QDateTime Timestamp READ Timestamp)

    QString message;
    QDateTime timestamp;

    explicit LogMessage(QString Message, QDateTime timestamp, QObject *parent = 0);

public:
    static LogMessage Create(QString Message);

    inline QString Message()
    {
        return message;
    }

    inline QDateTime Timestamp()
    {
        return timestamp;
    }
};
