# QT += core gui sql

QT += core gui sql charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CODECFORTR = UTF-8

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    activitydatamanager.cpp \
    activitytracker.cpp \
    authorization.cpp \
    bmi.cpp \
    bmr.cpp \
    fooddatamanager.cpp \
    main.cpp \
    mainwindow.cpp \
    nutritiontracker.cpp \
    registration.cpp

HEADERS += \
    activitydatamanager.h \
    activitytracker.h \
    authorization.h \
    bmi.h \
    bmr.h \
    databasemanager.h \
    fooddatamanager.h \
    mainwindow.h \
    nutritiontracker.h \
    registration.h

FORMS += \
    authorization.ui \
    mainwindow.ui \
    registration.ui

win32:RC_FILE = icon_healthapp.rc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    things.qrc

DISTFILES += \
    data/bmiPercentileDataMale.txt \
    data/exercisesData.csv \
    data/exercisesData.txt \
    data/foodData.csv
