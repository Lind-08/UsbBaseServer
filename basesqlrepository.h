#pragma once
#include <irepository.h>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QVariant>
#include "dbfacade.h"
#include <stdexcept>

template <class T>
class BaseSqlRepository : public IRepository<T>
{
protected:
    const QString GET_ID_QUERY = "SELECT * FROM %1";

    virtual QString getInsertQuery(T *object) = 0;
    virtual QString getUpdateQuery(T *object) = 0;
    virtual QString getDeleteQuery(T *object) = 0;
    virtual QString getQueryForID() = 0;

    void execQuery(QString queryString);

    void create(T *object);
    int getIdAfterInsert();

    void update(T *object);
    void remove(T *object);

public:
    explicit BaseSqlRepository();
};

template<class T>
BaseSqlRepository<T>::BaseSqlRepository()
{

}

template<class T>
void BaseSqlRepository<T>::execQuery(QString queryString)
{
    auto db = DbFacade::Instance();
    QSqlQuery *query = db->CreateQuery();
    if(!query->exec(queryString))
    {
        throw std::runtime_error(query->lastError().text().toStdString());
    }
}

template<class T>
void BaseSqlRepository<T>::create(T *object)
{
    QString queryString = getInsertQuery(object);
    execQuery(queryString);
}

template<class T>
int BaseSqlRepository<T>::getIdAfterInsert()
{
    auto db = DbFacade::Instance();
    QSqlQuery *query = db->CreateQuery();
    QString queryString = getQueryForID();
    if (query->exec(queryString))
    {
       query->last();
       int result = query->value(0).toInt();
       return result;
    }
    else
    {
        QString error = query->lastError().text();
        delete query;
        throw std::runtime_error(error.toStdString());
    }
}

template<class T>
void BaseSqlRepository<T>::update(T *object)
{
    QString queryString = getUpdateQuery(object);
    execQuery(queryString);
}

template<class T>
void BaseSqlRepository<T>::remove(T *object)
{
    QString queryString = getDeleteQuery(object);
    execQuery(queryString);
}
