#include "nutritiontracker.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <QFile>

NutritionTracker::NutritionTracker()
{
    readFoodData();
}

QStringList NutritionTracker::getFoodList(FoodOptions options)
{
    QStringList tempList;
    QString tempQString;
    tempList.clear();
    switch(options){
    case FoodOptions::Meat:
        for(unsigned int i = 0; i < foodList[FoodOptions::Meat].size(); i++)
        {
            tempQString = QString::fromStdString(foodList[FoodOptions::Meat].at(i).descrip);
            tempList.append(tempQString);
        }
        break;
    case FoodOptions::Dairy:
        for(unsigned int i = 0; i < foodList[FoodOptions::Dairy].size(); i++)
        {
            tempQString = QString::fromStdString(foodList[FoodOptions::Dairy].at(i).descrip);
            tempList.append(tempQString);
        }
        break;
    case FoodOptions::Carbs:
        for(unsigned int i = 0; i < foodList[FoodOptions::Carbs].size(); i++)
        {
            tempQString = QString::fromStdString(foodList[FoodOptions::Carbs].at(i).descrip);
            tempList.append(tempQString);
        }
        break;
    case FoodOptions::Veg:
        for(unsigned int i = 0; i < foodList[FoodOptions::Veg].size(); i++)
        {
            tempQString = QString::fromStdString(foodList[FoodOptions::Veg].at(i).descrip);
            tempList.append(tempQString);
        }
        break;
    case FoodOptions::Other:
        for(unsigned int i = 0; i < foodList[FoodOptions::Other].size(); i++)
        {
            tempQString = QString::fromStdString(foodList[FoodOptions::Other].at(i).descrip);
            tempList.append(tempQString);
        }
        break;
    }
    return tempList;
}

NutritionTracker::FoodOptions NutritionTracker::getFoodType()
{
    return foodTypes;
}

void NutritionTracker::setFoodType(NutritionTracker::FoodOptions type)
{
    foodTypes = type;
}

std::vector<NutritionTracker::FoodData> NutritionTracker::getFoodMapItems(NutritionTracker::FoodOptions option)
{
    switch(option){
    case FoodOptions::Meat:
        return NutritionTracker::foodList[FoodOptions::Meat];
    case FoodOptions::Dairy:
        return NutritionTracker::foodList[FoodOptions::Dairy];
    case FoodOptions::Carbs:
        return NutritionTracker::foodList[FoodOptions::Carbs];
    case FoodOptions::Veg:
        return NutritionTracker::foodList[FoodOptions::Veg];
    case FoodOptions::Other:
        return NutritionTracker::foodList[FoodOptions::Other];
    }

    return std::vector<NutritionTracker::FoodData>();
}

void NutritionTracker::readFoodData()
{
    std::string currentLine;
    std::ifstream foodFile;
    foodFile.open(FOOD_DATA_FILENAME);
    if (!foodFile)
    {
        perror("Text file for test data could not be opened!");
    }
    getline(foodFile, currentLine);
    while (std::getline(foodFile, currentLine))
    {
        std::istringstream iss(currentLine);

        std::string token,
            tempCategory;
        FoodData tempData;
        for (int i = 0; i < LEN + 1; i++)
        {
            if (i == LEN)
            {
                if (tempCategory == "Dairy")
                {
                    foodList[FoodOptions::Dairy].push_back(tempData);
                }
                else if (tempCategory == "Meat")
                {
                    foodList[FoodOptions::Meat].push_back(tempData);
                }
                else if (tempCategory == "Carbs")
                {
                    foodList[FoodOptions::Carbs].push_back(tempData);
                }
                else if (tempCategory == "Veg" || tempCategory == "Fruit")
                {
                    foodList[FoodOptions::Veg].push_back(tempData);
                }
                else
                {
                    foodList[FoodOptions::Other].push_back(tempData);
                }
            }
            else
            {
                std::getline(iss, token, ',');
                switch (i) {
                case 0:
                    tempCategory = token;
                    break;
                case 1:
                    tempData.descrip = token;
                    break;
                case 2:
                    tempData.carb = std::stod(token);
                    break;
                case 3:
                    tempData.cal = std::stoi(token);
                    break;
                case 4:
                    tempData.prot = std::stod(token);
                    break;
                case 5:
                    tempData.sugar = std::stod(token);
                    break;
                case 6:
                    tempData.satFat = std::stod(token);
                    break;
                case 7:
                    tempData.totalFat = std::stod(token);
                    break;
                case 8:
                    tempData.calcium = std::stoi(token);
                    break;
                case 9:
                    tempData.sodium = std::stoi(token);
                    break;
                case 10:
                    tempData.measurement = token;
                    break;
                }
            }
        }
    }
    foodFile.close();
}

QStringList NutritionTracker::getProductInfo(const QString& productName)
{
    QStringList productInfo;
    for (const auto& item : foodList)
    {
        for (const auto& food : item.second)
        {
            if (QString::fromStdString(food.descrip) == productName)
            {
                productInfo << QString::fromStdString(food.descrip)
                            << QString::number(food.carb)
                            << QString::number(food.cal)
                            << QString::number(food.prot)
                            << QString::number(food.sugar)
                            << QString::number(food.satFat)
                            << QString::number(food.totalFat)
                            << QString::number(food.calcium)
                            << QString::number(food.sodium)
                            << QString::fromStdString(food.measurement);
                break;
            }
        }
    }
    return productInfo;
}

int NutritionTracker::getCaloriesForFood(const QString &food)
{
    for (const auto& item : foodList)
    {
        for (const auto& foodData : item.second)
        {
            if (QString::fromStdString(foodData.descrip) == food)
            {
                return foodData.cal;
            }
        }
    }
    return 0;
}
