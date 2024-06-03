#include "bmr.h"

BMR::BMR() {}

double BMR::calculateBMRForMen(double weight, double height, int age)
{
    return 66.47 + (13.75 * weight) + (5.003 * height * 100) - (6.755 * age);
}

double BMR::calculateBMRForWomen(double weight, double height, int age)
{
    return 655.1 + (9.563 * weight) + (1.85 * height * 100) - (4.676 * age);
}

std::vector<double> BMR::calculateCalorieNeeds(double bmr)
{
    std::vector<double> calorieNeeds;
    calorieNeeds.push_back(bmr * 1.2);
    calorieNeeds.push_back(bmr * 1.375);
    calorieNeeds.push_back(bmr * 1.55);
    calorieNeeds.push_back(bmr * 1.725);
    calorieNeeds.push_back(bmr * 1.9);
    return calorieNeeds;
}
