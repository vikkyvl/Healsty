#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QtSql>

class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    virtual ~DatabaseManager() = default;

    virtual bool addRecord(const QVariantList &data) = 0;
    virtual bool deleteRecord(const QVariant &primaryKey) = 0;
    virtual QSqlQuery fetchRecords(int userId) = 0;
};

#endif // DATABASEMANAGER_H
