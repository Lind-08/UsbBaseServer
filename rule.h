#ifndef RULE_H
#define RULE_H

#include <QObject>

class Rule : public QObject
{
    Q_OBJECT
public:
    explicit Rule(QObject *parent = 0);

signals:

public slots:
};

#endif // RULE_H