#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "authorization.h"
#include "registration.h"
#include <QtDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_Main(new Ui::MainWindow)
{
    this->nutritionTrackerList = new NutritionTracker();
    this->activityTrackerList = new ActivityTracker();

    user_counter = 0;
    m_loginSuccesfull = false;
    connect(&ui_Auth, SIGNAL(login_button_clicked()),
            this, SLOT(authorizeUser()));
    connect(&ui_Auth,SIGNAL(destroyed()),
            this, SLOT(show()));
    connect(&ui_Auth,SIGNAL(register_button_clicked()),
            this,SLOT(registerWindowShow()));
    connect(&ui_Reg,SIGNAL(register_button_clicked2()),
            this,SLOT(registerUser()));
    connect(&ui_Reg,SIGNAL(destroyed()),
            &ui_Auth, SLOT(show()));
    if(!connectDB())
    {
        qDebug() << "Failed to connect DB";
    }

    QSqlQuery query;

    db_input = "CREATE TABLE userlist ( "
               "number INTEGER PRIMARY KEY NOT NULL, "
               "name VARCHAR(20), "
               "pass VARCHAR(12));";
    if (!query.exec(db_input))
    {
        qDebug() << "Unable to create a table" << query.lastError();
    }

    db_input = "CREATE TABLE food_data ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "user_id INTEGER, "
               "date DATE, "
               "food_list TEXT, "
               "servings INTEGER, "
               "total_calories INTEGER);";
    if (!query.exec(db_input))
    {
        qDebug() << "Unable to create food_data table" << query.lastError();
    }

    db_input = "CREATE TABLE activity_data ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "user_id INTEGER, "
               "date DATE, "
               "activity_type TEXT, "
               "activity_time INTEGER, "
               "calories_burned REAL);";
    if (!query.exec(db_input))
    {
        qDebug() << "Unable to create activity_data table" << query.lastError();
    }

    ui_Main->setupUi(this);

    this->setMinimumSize(907, 580);
    this->setMaximumSize(907, 580);
}

MainWindow::~MainWindow()
{
    mw_db.close();
    QSqlDatabase::removeDatabase("authorisation.db");
    qDebug() << "MainWindow Destroyed";
    delete ui_Main;
    delete nutritionTrackerList;
    delete activityTrackerList;
}

void MainWindow::authorizeUser()
{
    m_username = ui_Auth.getLogin();
    m_userpass = ui_Auth.getPass();

    QString str_t = "SELECT * FROM userlist WHERE name = '%1'";
    QString username = "";
    QString userpass = "";

    db_input = str_t.arg(m_username);

    QSqlQuery query;
    QSqlRecord rec;

    if (!query.exec(db_input))
    {
        qDebug() << "Unable to execute query - exiting" << query.lastError() << " : " << query.lastQuery();
        return;
    }

    if (!query.next())
    {
        QMessageBox::information(this, "Authorization", "The account does not exist yet, register");
        m_loginSuccesfull = false;
        return;
    }

    rec = query.record();

    user_counter = query.value(rec.indexOf("number")).toInt();
    username = query.value(rec.indexOf("name")).toString();
    userpass = query.value(rec.indexOf("pass")).toString();

    if (m_username != username || m_userpass != userpass)
    {
        QMessageBox::warning(this, "Authorization", "The password does not match, try again");
        qDebug() << "Password mismatch" << username << " " << userpass;
        m_loginSuccesfull = false;
    }
    else
    {
        m_loginSuccesfull = true;
        ui_Auth.close();
        ui_Reg.close();
        this->show();
    }
}

void MainWindow::registerWindowShow()
{
    int ret = QMessageBox::question(this, tr("Registration"), tr("Are you sure you want to register?"), QMessageBox::Yes | QMessageBox::No);

    if (ret == QMessageBox::Yes)
    {
        ui_Auth.hide();
        ui_Reg.show();
    }
    else
    {
        ui_Reg.hide();
        ui_Auth.show();
    }
}

void MainWindow::registerUser()
{
    QString name = ui_Reg.getName();
    QString pass = ui_Reg.getPass();
    QString confirmation = ui_Reg.getConfirmation();

    if (name.isEmpty() || pass.isEmpty() || confirmation.isEmpty())
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr("Error"), tr("None entered. Do you want to return to registration?"),
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            return;
        }
        else {
            ui_Auth.show();
            ui_Reg.hide();
            return;
        }
    }

    if (!ui_Reg.checkPass())
    {
        QMessageBox::warning(this, tr("Error"), tr("The confirmation does not match the password"));
        return;
    }

    QSqlQuery query;
    QString str_t = "SELECT * FROM userlist WHERE name = '%1'";
    db_input = str_t.arg(ui_Reg.getName());

    if (!query.exec(db_input))
    {
        qDebug() << "Unable to execute query - exiting" << query.lastError() << " : " << query.lastQuery();
        return;
    }

    if (query.next())
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle(tr("Registration"));
        msgBox.setText(tr("Such an account already exists."));
        msgBox.setInformativeText(tr("Return to authorization?"));
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int ret = msgBox.exec();

        if (ret == QMessageBox::Yes)
        {
            ui_Reg.hide();
            ui_Auth.show();
        }
        else
        {
            ui_Reg.clearPasswordFields();
        }

        return;
    }

    QSqlRecord rec;
    str_t = "SELECT COUNT(*) FROM userlist;";
    db_input = str_t;
    if (!query.exec(db_input))
    {
        qDebug() << "Unable to get number " << query.lastError() << " : " << query.lastQuery();
        return;
    }
    else
    {
        query.next();
        rec = query.record();
        user_counter = rec.value(0).toInt();
    }

    m_username = name;
    m_userpass = pass;

    user_counter++;
    str_t = "INSERT INTO userlist(number, name, pass) VALUES(%1, '%2', '%3');";
    db_input = str_t.arg(user_counter).arg(m_username).arg(m_userpass);

    if (!query.exec(db_input))
    {
        qDebug() << "Unable to insert data" << query.lastError() << " : " << query.lastQuery();
    }
    else
    {
        ui_Reg.hide();
        ui_Auth.show();
    }
}

void MainWindow::display()
{
    ui_Auth.show();
}

bool MainWindow::connectDB()
{
    mw_db = QSqlDatabase::addDatabase("QSQLITE");
    mw_db.setDatabaseName("authorisation.db");
    if(!mw_db.open())
    {
        qDebug() << "Cannot open database: " << mw_db.lastError();
        return false;
    }

    return true;
}

void MainWindow::on_homePushButton_clicked()
{
    ui_Main->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_nutritionTrackerPushButton_clicked()
{
    ui_Main->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_sportPushButton_clicked()
{
    ui_Main->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_personalOverviewPushButton_clicked()
{
    ui_Main->stackedWidget->setCurrentIndex(3);
}

//NUTRITION
void MainWindow::on_addButton_clicked()
{
    QString currentFoodItem = ui_Main->foodComboBox->currentText();
    int servingSize = ui_Main->servingComboBox->currentText().toInt();
    std::vector<NutritionTracker::FoodData> foodItems = nutritionTrackerList->getFoodMapItems(nutritionTrackerList->getFoodType());//

    for (const auto& item : foodItems)
    {
        if (currentFoodItem.toStdString() == item.descrip)
        {
            totalCals += item.cal * servingSize;
            break;
        }
    }

    ui_Main->foodListWidget->addItem(currentFoodItem);
    ui_Main->servingListWidget->addItem(ui_Main->servingComboBox->currentText());
    ui_Main->totalCaloriesLabel->setText(QString::number(totalCals));

    QStringList productInfo = nutritionTrackerList->getProductInfo(currentFoodItem);//

    for (int i = 0; i < productInfo.size(); i++)
    {
        ui_Main->foodCharacteristicsTableWidget->setItem(0, i, new QTableWidgetItem(productInfo[i]));
    }
    ui_Main->foodCharacteristicsTableWidget->resizeRowsToContents();
    ui_Main->foodCharacteristicsTableWidget->resizeColumnsToContents();
}

void MainWindow::on_clearButton_clicked()
{
    totalCals = 0;
    ui_Main->totalCaloriesLabel->setText(QString::number(0));
    ui_Main->foodListWidget->clear();
    ui_Main->servingListWidget->clear();
}

void MainWindow::on_clearOneElementButton_clicked()
{
    int foodItemCount = ui_Main->foodListWidget->count();
    int servingItemCount = ui_Main->servingListWidget->count();

    if (foodItemCount > 0 && servingItemCount > 0)
    {
        QString servingSize = ui_Main->servingListWidget->item(servingItemCount - 1)->text();
        int serving = servingSize.toInt();
        QString productName = ui_Main->foodListWidget->item(foodItemCount - 1)->text();
        int caloriesToRemove = 0;

        for (const auto& item : nutritionTrackerList->getFoodMapItems(nutritionTrackerList->getFoodType()))//
        {
            if (productName.toStdString() == item.descrip)
            {
                caloriesToRemove = item.cal * serving;
                break;
            }
        }

        delete ui_Main->foodListWidget->item(foodItemCount - 1);
        delete ui_Main->servingListWidget->item(servingItemCount - 1);

        totalCals -= caloriesToRemove;
        if (totalCals < 0)
        {
            totalCals = 0;
        }
        ui_Main->totalCaloriesLabel->setText(QString::number(totalCals));

        if (ui_Main->foodListWidget->count() > 0)
        {
            QString lastProductName = ui_Main->foodListWidget->item(ui_Main->foodListWidget->count() - 1)->text();
            QStringList productInfo = nutritionTrackerList->getProductInfo(lastProductName);

            ui_Main->foodCharacteristicsTableWidget->clearContents();
            for (int i = 0; i < productInfo.size(); ++i)
            {
                ui_Main->foodCharacteristicsTableWidget->setItem(0, i, new QTableWidgetItem(productInfo[i]));
            }
        }
        else
        {
            ui_Main->foodCharacteristicsTableWidget->clearContents();
        }
    }
    else
    {
        totalCals = 0;
        ui_Main->totalCaloriesLabel->setText(QString::number(totalCals));
        ui_Main->foodCharacteristicsTableWidget->clearContents();
    }
}

void MainWindow::updateFoodComboBox(NutritionTracker::FoodOptions foodType)
{
    ui_Main->foodComboBox->clear();
    ui_Main->foodComboBox->addItems(nutritionTrackerList->getFoodList(foodType));
    nutritionTrackerList->setFoodType(foodType);
}

void MainWindow::on_meatButton_clicked()
{
    updateFoodComboBox(NutritionTracker::FoodOptions::Meat);
}

void MainWindow::on_dairyButton_clicked()
{
    updateFoodComboBox(NutritionTracker::FoodOptions::Dairy);
}

void MainWindow::on_carbsButton_clicked()
{
    updateFoodComboBox(NutritionTracker::FoodOptions::Carbs);
}

void MainWindow::on_vegAndFruitButton_clicked()
{
    updateFoodComboBox(NutritionTracker::FoodOptions::Veg);
}

void MainWindow::on_otherButton_clicked()
{
    updateFoodComboBox(NutritionTracker::FoodOptions::Other);
}

void MainWindow::on_addToDBNutPushButton_clicked()
{
    int foodItemCount = ui_Main->foodListWidget->count();
    int servingItemCount = ui_Main->servingListWidget->count();

    if (foodItemCount == 0 || servingItemCount == 0)
    {
        QMessageBox::warning(this, "Input Error", "No items in food list or serving list.");
        return;
    }

    if (foodItemCount != servingItemCount)
    {
        QMessageBox::warning(this, "Input Error", "Mismatch between food items and serving items count.");
        return;
    }

    QString currentDate = QDate::currentDate().toString("yyyy-MM-dd");

    FoodDataManager foodDataManager;

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation", "Are you sure you want to add data?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::No)
    {
        return;
    }

    for (int i = 0; i < foodItemCount; i++)
    {
        QString foodList = ui_Main->foodListWidget->item(i)->text();
        int servings = ui_Main->servingListWidget->item(i)->text().toInt();
        int caloriesPerServing = nutritionTrackerList->getCaloriesForFood(foodList);
        int totalCalories = caloriesPerServing * servings;

        QVariantList data;
        data << user_counter << currentDate << foodList << totalCalories << servings;

        if (!foodDataManager.addRecord(data))
        {
            QMessageBox::warning(this, "Database Error", "Error adding food data to database.");
            return;
        }
    }

    QMessageBox::information(this, "Success", "All items added to database successfully.");
}


void MainWindow::on_viewDataNutPushButton_clicked()
{
    FoodDataManager foodDataManager;
    QSqlQuery query = foodDataManager.fetchRecords(user_counter);

    if (!query.exec()) {
        qDebug() << "Error fetching nutrition data:" << query.lastError().text();
        return;
    }

    ui_Main->nutritionDBTableWidget->setRowCount(0);

    QString lastDate;
    int spanRow = 0;

    while (query.next())
    {
        QString date = query.value(0).toString();
        QString foodList = query.value(1).toString();
        int servings = query.value(2).toInt();
        int totalCalories = query.value(3).toInt();

        int row = ui_Main->nutritionDBTableWidget->rowCount();
        ui_Main->nutritionDBTableWidget->insertRow(row);
        ui_Main->nutritionDBTableWidget->setItem(row, 0, new QTableWidgetItem(date));
        ui_Main->nutritionDBTableWidget->setItem(row, 1, new QTableWidgetItem(foodList));
        ui_Main->nutritionDBTableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(servings)));
        ui_Main->nutritionDBTableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(totalCalories)));

        if (date != lastDate)
        {
            if (lastDate != "")
            {
                ui_Main->nutritionDBTableWidget->setSpan(spanRow, 0, row - spanRow, 1);
            }
            spanRow = row;
            lastDate = date;
        }
    }

    if (lastDate != "")
    {
        ui_Main->nutritionDBTableWidget->setSpan(spanRow, 0, ui_Main->nutritionDBTableWidget->rowCount() - spanRow, 1);
    }

    ui_Main->nutritionDBTableWidget->resizeRowsToContents();
    ui_Main->nutritionDBTableWidget->resizeColumnsToContents();
}

void MainWindow::on_deleteDataNutpushButton_clicked()
{
    QList<QTableWidgetItem *> selectedItems = ui_Main->nutritionDBTableWidget->selectedItems();

    if (selectedItems.isEmpty())
    {
        QMessageBox::warning(this, "No Selection", "No items selected for deletion.");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation", "Are you sure you want to delete the data?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::No)
    {
        return;
    }

    QList<int> rowsToDelete;
    for (QTableWidgetItem *item : selectedItems)
    {
        int row = item->row();
        if (!rowsToDelete.contains(row))
        {
            rowsToDelete.append(row);
        }
    }

    QList<QVariantList> recordsToDelete;
    for (int row : rowsToDelete)
    {
        QString date = ui_Main->nutritionDBTableWidget->item(row, 0)->text();
        QVariantList record;
        record << user_counter << date;
        recordsToDelete.append(record);
    }

    FoodDataManager foodDataManager;
    for (const QVariantList &record : recordsToDelete)
    {
        if (!foodDataManager.deleteRecord(record))
        {
            qDebug() << "Error deleting record for user_id:" << record[0].toInt() << "date:" << record[1].toString();
        }
    }

    std::sort(rowsToDelete.begin(), rowsToDelete.end(), std::greater<int>());
    for (int row : rowsToDelete)
    {
        ui_Main->nutritionDBTableWidget->removeRow(row);
    }

    QMessageBox::information(this, "Success", "Data deleted successfully.");
}

//ACTIVITY
void MainWindow::updateActivityComboBox(ActivityTracker::ActivityOptions activityType)
{
    ui_Main->activityComboBox->clear();
    QStringList activities = activityTrackerList->getActivityList(activityType);
    ui_Main->activityComboBox->addItems(activities);
    activityTrackerList->setActivityType(activityType);
}

void MainWindow::on_wjrPushButton_clicked()
{
    updateActivityComboBox(ActivityTracker::ActivityOptions::WJR);
}

void MainWindow::on_hoPushButton_clicked()
{
    updateActivityComboBox(ActivityTracker::ActivityOptions::HO);
}

void MainWindow::on_lsPushButton_clicked()
{
    updateActivityComboBox(ActivityTracker::ActivityOptions::LS);
}

void MainWindow::on_calculatePushButton_clicked()
{
    QString activityType = ui_Main->activityComboBox->currentText();
    if (activityType.isEmpty())
    {
        QMessageBox::warning(this, "Input Error", "Activity type is not selected.");
        return;
    }

    ActivityTracker::ActivityOptions selectedActivity = activityTrackerList->getActivityType();
    std::vector<ActivityTracker::ActivityData> activityData = activityTrackerList->getActivityMapItems(selectedActivity);

    double metLevel = 0.0;
    if (!activityData.empty())
    {
        metLevel = activityData[0].met;
    }
    else
    {
        QMessageBox::warning(this, "Input Error", "No activity data available for the selected activity type.");
        return;
    }

    QString weightStr = ui_Main->weightLineEdit->text();
    if (weightStr.isEmpty())
    {
        QMessageBox::warning(this, "Input Error", "Weight is not provided.");
        return;
    }

    QRegularExpression reWeight("^[0-9,.]*$");
    if (!reWeight.match(weightStr).hasMatch())
    {
        QMessageBox::warning(this, "Input Error", "Weight must be a valid number.");
        return;
    }

    weightStr.replace(",", ".");
    double weightKg = weightStr.toDouble();

    QString hoursStr = ui_Main->hourDLineEdit->text();
    QString minutesStr = ui_Main->minDLineEdit->text();

    int hours = hoursStr.isEmpty() ? 0 : hoursStr.toInt();
    int minutes = minutesStr.isEmpty() ? 0 : minutesStr.toInt();

    QRegularExpression reDuration("^[0-9]*$");
    if ((!hoursStr.isEmpty() && !reDuration.match(hoursStr).hasMatch()) ||
        (!minutesStr.isEmpty() && !reDuration.match(minutesStr).hasMatch()))
    {
        QMessageBox::warning(this, "Input Error", "Duration must be valid numbers.");
        return;
    }

    if (hours == 0 && minutes == 0)
    {
        QMessageBox::warning(this, "Input Error", "No duration of activity provided.");
        return;
    }

    int totalMinutes = hours * 60 + minutes;
    QString exerciseCalories = activityTrackerList->calculateExerciseCalories(weightKg, totalMinutes, metLevel);

    ui_Main->totalCalorieActivityLabel->setText(exerciseCalories);
}

void MainWindow::on_addToDBActPushButton_clicked()
{
    QString activityType = ui_Main->activityComboBox->currentText();
    QString hourStr = ui_Main->hourDLineEdit->text();
    QString minStr = ui_Main->minDLineEdit->text();
    double caloriesBurned = ui_Main->totalCalorieActivityLabel->text().toDouble();

    if (activityType.isEmpty())
    {
        QMessageBox::warning(this, "Input Error", "Activity type is empty");
        return;
    }

    QRegularExpression reDuration("^[0-9]*$");
    if (!hourStr.isEmpty() && !reDuration.match(hourStr).hasMatch())
    {
        QMessageBox::warning(this, "Input Error", "Hour field must contain only numbers.");
        return;
    }

    if (!minStr.isEmpty() && !reDuration.match(minStr).hasMatch())
    {
        QMessageBox::warning(this, "Input Error", "Minute field must contain only numbers.");
        return;
    }

    int hours = hourStr.isEmpty() ? 0 : hourStr.toInt();
    int minutes = minStr.isEmpty() ? 0 : minStr.toInt();

    QString activityTime = QString("%1:%2:00").arg(hours, 2, 10, QChar('0')).arg(minutes, 2, 10, QChar('0'));
    QString currentDate = QDate::currentDate().toString("yyyy-MM-dd");

    QVariantList data;
    data << user_counter << currentDate << activityType << activityTime << caloriesBurned;

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation", "Are you sure you want to add data?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::No)
    {
        return;
    }

    if (!activityDataManager.addRecord(data))
    {
        QMessageBox::warning(this, "Database Error", "Error adding activity data to database.");
        return;
    }

    QMessageBox::information(this, "Success", "Activity data added to database successfully.");
}

void MainWindow::on_viewDataActPushButton_clicked()
{
    QSqlQuery query = activityDataManager.fetchRecords(user_counter);

    if (!query.isActive())
    {
        qDebug() << "Error fetching activity data:" << query.lastError().text();
        return;
    }

    ui_Main->activityDBTableWidget->setRowCount(0);

    QString lastDate;
    int spanRow = 0;

    while (query.next())
    {
        QString date = query.value(0).toString();
        QString activityType = query.value(1).toString();
        QString activityTime = query.value(2).toString();
        double caloriesBurned = query.value(3).toDouble();

        int row = ui_Main->activityDBTableWidget->rowCount();
        ui_Main->activityDBTableWidget->insertRow(row);
        ui_Main->activityDBTableWidget->setItem(row, 0, new QTableWidgetItem(date));
        ui_Main->activityDBTableWidget->setItem(row, 1, new QTableWidgetItem(activityType));
        ui_Main->activityDBTableWidget->setItem(row, 2, new QTableWidgetItem(activityTime));
        ui_Main->activityDBTableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(caloriesBurned)));

        if (date != lastDate)
        {
            if (lastDate != "")
            {
                ui_Main->activityDBTableWidget->setSpan(spanRow, 0, row - spanRow, 1);
            }
            spanRow = row;
            lastDate = date;
        }
    }

    if (lastDate != "")
    {
        ui_Main->activityDBTableWidget->setSpan(spanRow, 0, ui_Main->activityDBTableWidget->rowCount() - spanRow, 1);
    }

    ui_Main->activityDBTableWidget->resizeRowsToContents();
    ui_Main->activityDBTableWidget->resizeColumnsToContents();
}

void MainWindow::on_deleteDataActPushButton_clicked()
{
    QList<QTableWidgetItem *> selectedItems = ui_Main->activityDBTableWidget->selectedItems();

    QList<int> rowsToDelete;
    for (QTableWidgetItem *item : selectedItems)
    {
        int row = item->row();
        if (!rowsToDelete.contains(row))
        {
            rowsToDelete.append(row);
        }
    }

    QList<QString> datesToDelete;
    QList<QString> activityTypesToDelete;
    QList<QString> activityTimesToDelete;
    for (int row : rowsToDelete)
    {
        QString date = ui_Main->activityDBTableWidget->item(row, 0)->text();
        QString activityType = ui_Main->activityDBTableWidget->item(row, 1)->text();
        QString activityTime = ui_Main->activityDBTableWidget->item(row, 2)->text();
        datesToDelete.append(date);
        activityTypesToDelete.append(activityType);
        activityTimesToDelete.append(activityTime);
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation", "Are you sure you want to delete the data?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::No) {
        return;
    }

    for (int i = 0; i < datesToDelete.size(); i++)
    {
        QVariantList data;
        data << user_counter << datesToDelete[i] << activityTypesToDelete[i] << activityTimesToDelete[i];
        if (!activityDataManager.deleteRecord(data))
        {
            qDebug() << "Error deleting activity data.";
        }
    }

    std::sort(rowsToDelete.begin(), rowsToDelete.end(), std::greater<int>());
    for (int row : rowsToDelete)
    {
        ui_Main->activityDBTableWidget->removeRow(row);
    }

    QMessageBox::information(this, "Success", "Activity data deleted successfully.");
}


void MainWindow::on_viewProgressActivity_clicked()
{
    QSqlQuery query;
    query.prepare("SELECT date, SUM(calories_burned) as total_calories FROM activity_data WHERE user_id = :user_id GROUP BY date ORDER BY date ASC");
    query.bindValue(":user_id", user_counter);

    if (!query.exec()) {
        QMessageBox::warning(this, "Database Error", "Error fetching activity data: " + query.lastError().text());
        return;
    }

    QLineSeries *series = new QLineSeries();

    QDateTime minDate = QDateTime::currentDateTime();
    QDateTime maxDate = QDateTime::currentDateTime();

    while (query.next()) {
        QString dateStr = query.value(0).toString();
        QDateTime date = QDateTime::fromString(dateStr, "yyyy-MM-dd");
        if (!date.isValid()) {
            QMessageBox::warning(this, "Data Error", "Invalid date format: " + dateStr);
            continue;
        }
        double caloriesBurned = query.value(1).toDouble();
        series->append(date.toMSecsSinceEpoch(), caloriesBurned);

        if (date < minDate)
            minDate = date;
        if (date > maxDate)
            maxDate = date;
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Activity Progress");

    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setFormat("yyyy-MM-dd");
    axisX->setTitleText("Date");
    axisX->setMin(minDate);
    axisX->setMax(maxDate);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText("Calories Burned");
    axisY->setMin(0);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QFont titleFont("Arial Black", 12, QFont::Bold);
    chart->setTitleFont(titleFont);

    QFont axisTitleFont("Arial Black", 12, QFont::Bold);
    QFont axisLabelFont("Arial", 7);

    axisX->setLabelsFont(axisLabelFont);
    axisX->setTitleFont(axisTitleFont);
    axisY->setLabelsFont(axisLabelFont);
    axisY->setTitleFont(axisTitleFont);

    QPen axisPen(QRgb(0xd18952));
    axisPen.setWidth(2);
    axisX->setLinePen(axisPen);
    axisY->setLinePen(axisPen);

    QBrush axisBrush(Qt::black);
    axisX->setLabelsBrush(axisBrush);
    axisY->setLabelsBrush(axisBrush);

    axisX->setGridLineVisible(true);
    axisY->setGridLineVisible(true);

    chart->setAnimationOptions(QChart::AllAnimations);
    chart->legend()->hide();
    chart->layout()->setContentsMargins(0, 0, 0, 0);
    chart->setBackgroundRoundness(0);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    chartView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    if (QLayout *layout = ui_Main->activityProgressGraphicsView->layout())
    {
        QLayoutItem *item;
        while ((item = layout->takeAt(0)) != nullptr)
        {
            delete item->widget();
            delete item;
        }
        delete layout;
    }

    chart->setMinimumSize(ui_Main->activityProgressGraphicsView->width(), ui_Main->activityProgressGraphicsView->height());
    chart->setPreferredSize(ui_Main->activityProgressGraphicsView->width(), ui_Main->activityProgressGraphicsView->height());
    chartView->resize(ui_Main->activityProgressGraphicsView->width(), ui_Main->activityProgressGraphicsView->height());

    QVBoxLayout *newLayout = new QVBoxLayout(ui_Main->activityProgressGraphicsView);
    newLayout->addWidget(chartView);
    ui_Main->activityProgressGraphicsView->setLayout(newLayout);
}


//BMR/BMI
void MainWindow::on_calculateBMI_RPushButton_clicked()
{
    double height = ui_Main->heightDoubleSpinBox->value();
    QString weightStr = ui_Main->weightForBMI_RLineEdit->text();
    QString ageStr = ui_Main->ageComboBox->currentText();

    if (height == 0 || weightStr.isEmpty() || ageStr.isEmpty() ||
        (!ui_Main->maleRadioButton->isChecked() && !ui_Main->femaleRadioButton->isChecked()))
    {
        QMessageBox::warning(this, "Input Error", "Fields are empty or some data is missing");
        return;
    }

    QRegularExpression re("^[0-9,.]*$");
    if (!re.match(weightStr).hasMatch())
    {
        QMessageBox::warning(this, "Input Error", "Weight must be a valid number");
        return;
    }

    weightStr.replace(",", ".");

    double weight = weightStr.toDouble();
    int age = ageStr.toInt();

    if (weight == 0)
    {
        QMessageBox::warning(this, "Input Error", "Weight must be a valid number");
        return;
    }

    double bmi = bmiAccess.calculateBMI(weight, height);

    if (!std::isfinite(bmi))
    {
        QMessageBox::warning(this, "Calculation Error", "BMI calculation resulted in an invalid number");
        return;
    }

    ui_Main->totalBMILabel->setText(QString::number(bmi, 'f', 2));

    int category = bmiAccess.getBMICategory(bmi) + 1;
    ui_Main->classificationBMIStackedWidget->setCurrentIndex(category);

    double bmr;
    if (ui_Main->maleRadioButton->isChecked())
    {
        bmr = bmrAccess.calculateBMRForMen(weight, height, age);
    } else if (ui_Main->femaleRadioButton->isChecked())
    {
        bmr = bmrAccess.calculateBMRForWomen(weight, height, age);
    }

    if (!std::isfinite(bmr))
    {
        QMessageBox::warning(this, "Calculation Error", "BMR calculation resulted in an invalid number");
        return;
    }

    ui_Main->totalBMRLabel->setText(QString::number(bmr, 'f', 2));

    std::vector<double> calorieNeeds = bmrAccess.calculateCalorieNeeds(bmr);

    ui_Main->caloriesDailyTableWidget->setItem(0, 0, new QTableWidgetItem(QString::number(calorieNeeds[0], 'f', 2)));
    ui_Main->caloriesDailyTableWidget->setItem(1, 0, new QTableWidgetItem(QString::number(calorieNeeds[1], 'f', 2)));
    ui_Main->caloriesDailyTableWidget->setItem(2, 0, new QTableWidgetItem(QString::number(calorieNeeds[2], 'f', 2)));
    ui_Main->caloriesDailyTableWidget->setItem(3, 0, new QTableWidgetItem(QString::number(calorieNeeds[3], 'f', 2)));
    ui_Main->caloriesDailyTableWidget->setItem(4, 0, new QTableWidgetItem(QString::number(calorieNeeds[4], 'f', 2)));

    ui_Main->caloriesDailyTableWidget->resizeRowsToContents();
    ui_Main->caloriesDailyTableWidget->resizeColumnsToContents();
}

