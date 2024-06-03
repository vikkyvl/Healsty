#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include <QtCharts>
#include <QtSql/QtSql>
#include "authorization.h"
#include "registration.h"
#include "nutritiontracker.h"
#include "activitytracker.h"
#include "fooddatamanager.h"
#include "activitydatamanager.h"
#include "databasemanager.h"
#include "bmi.h"
#include "bmr.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void display();
    bool connectDB();

private:
    Ui::MainWindow *ui_Main;

    Authorization ui_Auth;
    Registration ui_Reg;

    QString m_username;
    QString m_userpass;

    QString db_input;

    QSqlDatabase mw_db;

    int user_counter;
    bool m_loginSuccesfull;

    ActivityTracker *activityTrackerList;
    NutritionTracker *nutritionTrackerList;

    BMI bmiAccess;
    BMR bmrAccess;

    int totalCals = 0;
    void updateFoodComboBox(NutritionTracker::FoodOptions foodType);
    void updateActivityComboBox(ActivityTracker::ActivityOptions activityType);

    ActivityDataManager activityDataManager;

private slots:
    //AUTIRIZATION/REGISTRATION
    void authorizeUser();
    void registerWindowShow();
    void registerUser();

    //SELECT WINDOW
    void on_homePushButton_clicked();
    void on_nutritionTrackerPushButton_clicked();
    void on_sportPushButton_clicked();
    void on_personalOverviewPushButton_clicked();

    //NUTRITION
    void on_addButton_clicked();
    void on_clearButton_clicked();
    void on_clearOneElementButton_clicked();
    void on_meatButton_clicked();
    void on_dairyButton_clicked();
    void on_carbsButton_clicked();
    void on_vegAndFruitButton_clicked();
    void on_otherButton_clicked();

    void on_addToDBNutPushButton_clicked();
    void on_viewDataNutPushButton_clicked();
    void on_deleteDataNutpushButton_clicked();

    //ACTIVITY
    void on_wjrPushButton_clicked();
    void on_hoPushButton_clicked();
    void on_lsPushButton_clicked();
    void on_calculatePushButton_clicked();

    void on_addToDBActPushButton_clicked();
    void on_viewDataActPushButton_clicked();
    void on_deleteDataActPushButton_clicked();
    void on_viewProgressActivity_clicked();

    //BMR/BMI
    void on_calculateBMI_RPushButton_clicked();
};
#endif // MAINWINDOW_H
