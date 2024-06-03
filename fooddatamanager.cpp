#include "fooddatamanager.h"

FoodDataManager::FoodDataManager() {}

bool FoodDataManager::addRecord(const QVariantList &data)
{
    QSqlQuery query;
    query.prepare("INSERT INTO food_data (user_id, date, food_list, total_calories, servings) "
                  "VALUES (:user_id, :date, :food_list, :total_calories, :servings)");

    for (const QVariant &value : data)
    {
        query.addBindValue(value);
    }

    return query.exec();
}

bool FoodDataManager::deleteRecord(const QVariant &primaryKey)
{
    if (!primaryKey.canConvert<QVariantList>()) {
        return false;
    }

    QVariantList keyList = primaryKey.toList();
    if (keyList.size() != 2) { // user_id, date
        return false;
    }

    int userId = keyList[0].toInt();
    QString date = keyList[1].toString();

    QSqlQuery query;
    query.prepare("SELECT id FROM food_data WHERE user_id = :user_id AND date = :date");
    query.bindValue(":user_id", userId);
    query.bindValue(":date", date);

    if (query.exec() && query.next()) {
        int recordId = query.value(0).toInt();
        query.prepare("DELETE FROM food_data WHERE id = :id");
        query.bindValue(":id", recordId);
        return query.exec();
    }

    return false;
}

QSqlQuery FoodDataManager::fetchRecords(int userId)
{
    QSqlQuery query;
    query.prepare("SELECT date, food_list, servings, total_calories FROM food_data WHERE user_id = :user_id ORDER BY date ASC");
    query.addBindValue(userId);
    query.exec();
    return query;
}
