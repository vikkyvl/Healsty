#include "nutritionmainmanager.h"
#include <QStringList>

NutritionMainManager::NutritionMainManager(Ui::MainWindow* ui) : ui_Main(ui) {this->nutritionTrackerList = new NutritionTracker();}

void NutritionMainManager::addInformation()
{
    QString currentFoodItem = ui_Main->foodComboBox->currentText();
    int servingSize = ui_Main->servingComboBox->currentText().toInt();
    std::vector<NutritionTracker::FoodData> foodItems = nutritionTrackerList->getFoodMapItems(nutritionTrackerList->getFoodType());

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

    QStringList productInfo = nutritionTrackerList->getProductInfo(currentFoodItem);

    for (int i = 0; i < productInfo.size(); ++i)
    {
        ui_Main->foodCharacteristicsTableWidget->setItem(0, i, new QTableWidgetItem(productInfo[i]));
    }
    ui_Main->foodCharacteristicsTableWidget->resizeRowsToContents();
    ui_Main->foodCharacteristicsTableWidget->resizeColumnsToContents();
}
