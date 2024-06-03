#include "activitydatamanager.h"

ActivityDataManager::ActivityDataManager() {}

bool ActivityDataManager::addRecord(const QVariantList &data)
{
    QSqlQuery query;
    query.prepare("INSERT INTO activity_data (user_id, date, activity_type, activity_time, calories_burned) "
                  "VALUES (:user_id, :date, :activity_type, :activity_time, :calories_burned)");

    for (const QVariant &value : data)
    {
        query.addBindValue(value);
    }

    return query.exec();
}

bool ActivityDataManager::deleteRecord(const QVariant &primaryKey)
{
    QSqlQuery query;
    query.prepare("DELETE FROM activity_data WHERE user_id = :user_id AND date = :date AND activity_type = :activity_type AND activity_time = :activity_time");

    QVariantList primaryKeyList = primaryKey.toList();
    for (const QVariant &value : primaryKeyList)
    {
        query.addBindValue(value);
    }
    return query.exec();
}

QSqlQuery ActivityDataManager::fetchRecords(int userId)
{
    QSqlQuery query;
    query.prepare("SELECT date, activity_type, activity_time, calories_burned FROM activity_data WHERE user_id = ? ORDER BY date ASC");
    query.addBindValue(userId);
    query.exec();
    return query;
}
