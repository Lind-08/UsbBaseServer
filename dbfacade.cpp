#include "dbfacade.h"
#include <QSqlQuery>
#include <QSqlDatabase>
#include <stdexcept>

DbFacade *DbFacade::instance = nullptr;

DbFacade::DbFacade( QString Driver, QString DbName, QObject *parent) :
    QObject(parent),
    driver(Driver),
    dbName(DbName)
{
    db = QSqlDatabase::addDatabase(driver, dbName);
    if (!db.open())
        throw std::runtime_error("Can't open db.");
}

void DbFacade::InitDbFacade(QString Driver, QString DbName)
{
    instance = new DbFacade(Driver, DbName);
}

DbFacade *DbFacade::Instance()
{
    if (instance == nullptr)
        throw std::runtime_error("Not initialized dbfacade");
    else
        return instance;
}

QSqlQuery *DbFacade::CreateQuery()
{
    QSqlQuery *query = new QSqlQuery(db);
    return query;
}
