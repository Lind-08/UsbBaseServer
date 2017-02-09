#include "hostrepository.h"
#include "host.h"

HostRepository* HostRepository::instance = nullptr;

HostRepository::HostRepository(QObject *parent) :
    QObject(parent),
    Parent()
{

}

HostRepository *HostRepository::Instance()
{
    if (instance == nullptr)
        instance = new HostRepository();
    return instance;
}

QString HostRepository::getInsertQuery(Host *object)
{
    return INSERT_QUERY_STRING.arg(TABLE_NAME).arg(object->Secret()).arg(object->Name());
}

QString HostRepository::getUpdateQuery(Host *object)
{
    return UPDATE_QUERY_STRING.arg(TABLE_NAME).arg(object->Secret()).arg(object->Name()).arg(object->ID());
}

QString HostRepository::getDeleteQuery(Host *object)
{
    return DELETE_QUERY_STRING.arg(TABLE_NAME).arg(object->ID());
}

QString HostRepository::getQueryForID()
{
    return Parent::GET_ID_QUERY.arg(TABLE_NAME);
}

QList<Host *> HostRepository::GetAll()
{
    auto db = DbFacade::Instance();
    QSqlQuery *query = db->CreateQuery();
    if (query->exec(getQueryForID()))
        throw std::runtime_error(query->lastError().text().toStdString());
    QList<Host*> result;
    do
    {
        Host *obj = Host::Create();
        obj->setID(query->value(0).toInt());
        obj->setSecret(query->value(1).toString());
        obj->setName(query->value(2).toString());
        result.push_back(obj);
    } while(query->next());
    return result;
}

void HostRepository::Save(Host *object)
{
    if (object->ID() == Host::INVALID_ID)
    {
        create(object);
        object->setID(getIdAfterInsert());
    }
    else
    {
        update(object);
    }
}

void HostRepository::Delete(Host *object)
{
    if (object->ID() != Host::INVALID_ID)
        remove(object);
}
