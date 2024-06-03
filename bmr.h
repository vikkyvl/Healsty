#ifndef BMR_H
#define BMR_H

#include <vector>

class BMR
{
public:
    BMR();

    double calculateBMRForMen(double weight, double height, int age);
    double calculateBMRForWomen(double weight, double height, int age);
    std::vector<double> calculateCalorieNeeds(double bmr);
};

#endif // BMR_H
