#include "bmi.h"

BMI::BMI() {}

double BMI::calculateBMI(double mass, double height)
{
    return mass / (height * height);
}

int BMI::getBMICategory(double bmi)
{
    if (bmi < 16)
    {
        return static_cast<int>(BMIOptions::SevereThinness);
    }
    else if (bmi >= 16 && bmi < 17)
    {
        return static_cast<int>(BMIOptions::ModerateThinness);
    }
    else if (bmi >= 17 && bmi < 18.5)
    {
        return static_cast<int>(BMIOptions::MildThinness);
    }
    else if (bmi >= 18.5 && bmi < 25)
    {
        return static_cast<int>(BMIOptions::Normal);
    }
    else if (bmi >= 25 && bmi < 30)
    {
        return static_cast<int>(BMIOptions::Overweight);
    }
    else if (bmi >= 30 && bmi < 35)
    {
        return static_cast<int>(BMIOptions::ObeseClassI);
    }
    else if (bmi >= 35 && bmi < 40)
    {
        return static_cast<int>(BMIOptions::ObeseClassII);
    }
    else
    {
        return static_cast<int>(BMIOptions::ObeseClassIII);
    }
}
