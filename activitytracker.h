#ifndef ACTIVITYTRACKER_H
#define ACTIVITYTRACKER_H

#include <QMainWindow>
#include <QString>
#include <QStringList>
#include <map>
#include <string>
#include <vector>

class ActivityTracker : public QMainWindow
{
    Q_OBJECT
public:
    enum class ActivityOptions { WJR,
                                 HO,
                                 LS };
    const std::string ACTIVITY_DATA_FILENAME = "D:\\HealthApp\\exercisesData.csv";
    const int LEN = 3;

    struct ActivityData
    {
        std::string description;
        double met;
    };

    ActivityTracker();
    QStringList getActivityList(ActivityOptions);
    ActivityOptions getActivityType();
    std::vector<ActivityData> getActivityMapItems(ActivityOptions);
    void setActivityType(ActivityOptions);
    void readActivityData();
    QString calculateExerciseCalories(double weightKg, int totalMinutes, double metLevel);

private:
    ActivityOptions activityTypes;
    std::map<ActivityOptions, std::vector<ActivityData>> activityList;
};

#endif // ACTIVITYTRACKER_H


