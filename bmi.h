#ifndef BMI_H
#define BMI_H

#include <QMainWindow>

class BMI : public QMainWindow
{
public:
    BMI();

    enum class BMIOptions { SevereThinness,
                            ModerateThinness,
                            MildThinness,
                            Normal,
                            Overweight,
                            ObeseClassI,
                            ObeseClassII,
                            ObeseClassIII };
    double calculateBMI(double mass, double height);
    int getBMICategory(double bmi);
};

#endif // BMI_H
