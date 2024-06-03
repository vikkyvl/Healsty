#ifndef NUTRITIONTRACKER_H
#define NUTRITIONTRACKER_H

#include <QMainWindow>
#include <QString>
#include <QStringList>
#include <map>
#include <string>
#include <vector>

class NutritionTracker : public QMainWindow
{
    Q_OBJECT
public:
    enum class FoodOptions{Meat,
                             Dairy,
                             Carbs,
                             Veg,
                             Other};
    const std::string FOOD_DATA_FILENAME = "D:\\HealthApp\\foodData.csv";
    const int LEN = 11;

    struct FoodData
    {
        std::string descrip,
            measurement;
        int cal,
            sodium,
            calcium;
        double carb,
            prot,
            sugar,
            satFat,
            totalFat;
    };

    NutritionTracker();
    QStringList getFoodList (FoodOptions);
    FoodOptions getFoodType ();
    std::vector<FoodData> getFoodMapItems(FoodOptions);
    void setFoodType(FoodOptions);
    void readFoodData ();
    QStringList getProductInfo(const QString& productName);
    int getCaloriesForFood(const QString &food);

private:
    FoodOptions foodTypes;
    std::map<FoodOptions,std::vector<FoodData>> foodList;
};

#endif // NUTRITIONTRACKER_H


