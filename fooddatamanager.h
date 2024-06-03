#ifndef FOODDATAMANAGER_H
#define FOODDATAMANAGER_H

#include "databasemanager.h"
#include <QtSql>

class FoodDataManager : public DatabaseManager
{
    Q_OBJECT
public:
    explicit FoodDataManager();

    bool addRecord(const QVariantList &data) override;
    bool deleteRecord(const QVariant &primaryKey) override;
    QSqlQuery fetchRecords(int userId) override;
};

#endif // FOODDATAMANAGER_H
