#ifndef NUTRITIONMAINMANAGER_H
#define NUTRITIONMAINMANAGER_H

#include <QWidget>
#include <QString>
#include <vector>
#include "ui_mainwindow.h"
#include "nutritiontracker.h"

class NutritionMainManager
{
private:
    Ui::MainWindow* ui_Main;
    NutritionTracker *nutritionTrackerList;

public:
    NutritionMainManager(Ui::MainWindow* ui);
    void addInformation();
};

#endif // NUTRITIONMAINMANAGER_H
