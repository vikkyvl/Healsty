#ifndef ACTIVITYDATAMANAGER_H
#define ACTIVITYDATAMANAGER_H

#include "databasemanager.h"
#include <QtSql>

class ActivityDataManager : public DatabaseManager
{
    Q_OBJECT
public:
    ActivityDataManager();

    bool addRecord(const QVariantList &data) override;
    bool deleteRecord(const QVariant &primaryKey) override;
    QSqlQuery fetchRecords(int userId) override;
};

#endif // ACTIVITYDATAMANAGER_H
