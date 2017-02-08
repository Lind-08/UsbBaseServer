#ifndef HOSTREPOSITORY_H
#define HOSTREPOSITORY_H

#include <QObject>

class HostRepository : public QObject
{
    Q_OBJECT
public:
    explicit HostRepository(QObject *parent = 0);

signals:

public slots:
};

#endif // HOSTREPOSITORY_H