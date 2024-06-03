#include "activitytracker.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <QFile>

ActivityTracker::ActivityTracker()
{
    readActivityData();
}

QStringList ActivityTracker::getActivityList(ActivityOptions options)
{
    QStringList tempList;
    QString tempQString;
    tempList.clear();
    switch(options)
    {
    case ActivityOptions::WJR:
        for(unsigned int i = 0; i < activityList[ActivityOptions::WJR].size(); i++)
        {
            tempQString = QString::fromStdString(activityList[ActivityOptions::WJR].at(i).description);
            tempList.append(tempQString);
        }
        break;
    case ActivityOptions::HO:
        for(unsigned int i = 0; i < activityList[ActivityOptions::HO].size(); i++)
        {
            tempQString = QString::fromStdString(activityList[ActivityOptions::HO].at(i).description);
            tempList.append(tempQString);
        }
        break;
    case ActivityOptions::LS:
        for(unsigned int i = 0; i < activityList[ActivityOptions::LS].size(); i++)
        {
            tempQString = QString::fromStdString(activityList[ActivityOptions::LS].at(i).description);
            tempList.append(tempQString);
        }
        break;
    }
    return tempList;
}

ActivityTracker::ActivityOptions ActivityTracker::getActivityType()
{
    return activityTypes;
}

void ActivityTracker::setActivityType(ActivityTracker::ActivityOptions type)
{
    activityTypes = type;
}

std::vector<ActivityTracker::ActivityData> ActivityTracker::getActivityMapItems(ActivityTracker::ActivityOptions option)
{
    switch(option)
    {
    case ActivityOptions::WJR:
        return activityList[ActivityOptions::WJR];
    case ActivityOptions::HO:
        return activityList[ActivityOptions::HO];
    case ActivityOptions::LS:
        return activityList[ActivityOptions::LS];
    }

    return std::vector<ActivityTracker::ActivityData>();
}

void ActivityTracker::readActivityData()
{
    std::string currentLine;
    std::ifstream activityFile(ACTIVITY_DATA_FILENAME);

    if (!activityFile)
    {
        perror("Error: Unable to open activity data file");
        return;
    }

    getline(activityFile, currentLine);
    while (std::getline(activityFile, currentLine))
    {
        std::istringstream iss(currentLine);
        std::string token, tempCategory;
        ActivityData tempData;

        for (int i = 0; i < LEN + 1; i++)
        {
            if (i == LEN)
            {
                qDebug() << "Category: " << QString::fromStdString(tempCategory)
                         << ", Description: " << QString::fromStdString(tempData.description)
                         << ", MET: " << tempData.met;
                if (tempCategory == "Walking, jogging & running")
                {
                    activityList[ActivityOptions::WJR].push_back(tempData);
                }
                else if (tempCategory == "Household & occupation")
                {
                    activityList[ActivityOptions::HO].push_back(tempData);
                }
                else if (tempCategory == "Leisure time & sports")
                {
                    activityList[ActivityOptions::LS].push_back(tempData);
                }
            }
            else
            {
                std::getline(iss, token, ';');
                switch (i)
                {
                case 0:
                    tempCategory = token;
                    break;
                case 1:
                    tempData.description = token;
                    break;
                case 2:
                    tempData.met = std::stod(token);
                    break;
                }
            }
        }
    }
    activityFile.close();
}

QString ActivityTracker::calculateExerciseCalories(double weightKg, int totalMinutes, double metLevel)
{
    double exerciseCalories = (metLevel * 3.5 * weightKg * totalMinutes) / 200;

    return QString::number(exerciseCalories);
}







