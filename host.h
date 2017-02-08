#ifndef HOST_H
#define HOST_H

#include <QObject>

class Host : public QObject
{
    Q_OBJECT
public:
    explicit Host(QObject *parent = 0);

signals:

public slots:
};

#endif // HOST_H