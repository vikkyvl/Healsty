/********************************************************************************
** Form generated from reading UI file 'registration.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTRATION_H
#define UI_REGISTRATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Registration
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label_image;
    QGridLayout *gridLayout;
    QLineEdit *passwordLineEdit;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *confirmLineEdit;
    QPushButton *registerPushButton;
    QLabel *label_5;
    QLineEdit *nameLineEdit;
    QLabel *label_name_app;
    QLabel *label_reg;

    void setupUi(QWidget *Registration)
    {
        if (Registration->objectName().isEmpty())
            Registration->setObjectName("Registration");
        Registration->resize(500, 400);
        Registration->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        verticalLayout = new QVBoxLayout(Registration);
        verticalLayout->setObjectName("verticalLayout");
        label_image = new QLabel(Registration);
        label_image->setObjectName("label_image");
        label_image->setStyleSheet(QString::fromUtf8("image: url(:/resource/1_vNh7aYr63tZY_aOLSY0XEw.png);"));

        verticalLayout->addWidget(label_image);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        passwordLineEdit = new QLineEdit(Registration);
        passwordLineEdit->setObjectName("passwordLineEdit");
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        font.setPointSize(9);
        font.setBold(false);
        font.setItalic(false);
        passwordLineEdit->setFont(font);
        passwordLineEdit->setStyleSheet(QString::fromUtf8("border: 2px solid gray;\n"
"border-radius: 5px;\n"
"padding: 5px;\n"
"font: 9pt \"Arial\";\n"
"font-size: 1.2em;\n"
"color: black;\n"
"text-shadow: #454545 0 0 2px;"));
        passwordLineEdit->setEchoMode(QLineEdit::PasswordEchoOnEdit);

        gridLayout->addWidget(passwordLineEdit, 3, 1, 1, 1);

        label_3 = new QLabel(Registration);
        label_3->setObjectName("label_3");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Arial Black")});
        font1.setBold(true);
        label_3->setFont(font1);

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        label_4 = new QLabel(Registration);
        label_4->setObjectName("label_4");
        label_4->setFont(font1);

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        confirmLineEdit = new QLineEdit(Registration);
        confirmLineEdit->setObjectName("confirmLineEdit");
        confirmLineEdit->setFont(font);
        confirmLineEdit->setStyleSheet(QString::fromUtf8("border: 2px solid gray;\n"
"border-radius: 5px;\n"
"padding: 5px;\n"
"font: 9pt \"Arial\";\n"
"font-size: 1.2em;\n"
"color: black;\n"
"text-shadow: #454545 0 0 2px;"));
        confirmLineEdit->setEchoMode(QLineEdit::PasswordEchoOnEdit);

        gridLayout->addWidget(confirmLineEdit, 4, 1, 1, 1);

        registerPushButton = new QPushButton(Registration);
        registerPushButton->setObjectName("registerPushButton");
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Arial Black")});
        font2.setPointSize(9);
        font2.setWeight(QFont::Black);
        font2.setItalic(false);
        registerPushButton->setFont(font2);
        registerPushButton->setStyleSheet(QString::fromUtf8("QPushButton#registerPushButton {\n"
"float: right;\n"
"border-bottom: 4px solid rgb(218, 218, 218);\n"
"font: 900 9pt \"Arial Black\";\n"
"margin-right: 3%;\n"
"margin-top: 5px;\n"
"border-radius: 5px;\n"
"-moz-border-radius: 5px;\n"
"-webkit-border-radius: 5px;\n"
"padding: 5px 9px;\n"
"font-size: 1.2em;\n"
"background-color: rgb(246, 246, 246);\n"
"text-shadow: #454545 0 0 2px;\n"
"color: black;\n"
"}\n"
"QPushButton#registerPushButton:pressed {\n"
"background-color: rgb(218, 218, 218);\n"
"border-style: inset;\n"
"}"));

        gridLayout->addWidget(registerPushButton, 5, 1, 1, 1);

        label_5 = new QLabel(Registration);
        label_5->setObjectName("label_5");
        label_5->setFont(font1);

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        nameLineEdit = new QLineEdit(Registration);
        nameLineEdit->setObjectName("nameLineEdit");
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Arial")});
        font3.setPointSize(9);
        font3.setBold(false);
        font3.setItalic(false);
        font3.setStyleStrategy(QFont::PreferDefault);
        font3.setHintingPreference(QFont::PreferDefaultHinting);
        nameLineEdit->setFont(font3);
        nameLineEdit->setStyleSheet(QString::fromUtf8("border: 2px solid gray;\n"
"border-radius: 5px;\n"
"padding: 5px;\n"
"font: 9pt \"Arial\";\n"
"font-size: 1.2em;\n"
"color: black;\n"
"text-shadow: #454545 0 0 2px;"));
        nameLineEdit->setEchoMode(QLineEdit::Normal);
        nameLineEdit->setCursorMoveStyle(Qt::LogicalMoveStyle);

        gridLayout->addWidget(nameLineEdit, 2, 1, 1, 1);

        label_name_app = new QLabel(Registration);
        label_name_app->setObjectName("label_name_app");
        QFont font4;
        font4.setFamilies({QString::fromUtf8("Arial Black")});
        font4.setPointSize(16);
        font4.setBold(true);
        label_name_app->setFont(font4);

        gridLayout->addWidget(label_name_app, 0, 0, 1, 2);

        label_reg = new QLabel(Registration);
        label_reg->setObjectName("label_reg");
        label_reg->setEnabled(true);
        label_reg->setFont(font1);
        label_reg->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_reg, 1, 0, 1, 2);


        verticalLayout->addLayout(gridLayout);


        retranslateUi(Registration);

        QMetaObject::connectSlotsByName(Registration);
    } // setupUi

    void retranslateUi(QWidget *Registration)
    {
        Registration->setWindowTitle(QCoreApplication::translate("Registration", "Registration", nullptr));
        label_image->setText(QString());
        label_3->setText(QCoreApplication::translate("Registration", "Name:", nullptr));
        label_4->setText(QCoreApplication::translate("Registration", "Password:", nullptr));
        registerPushButton->setText(QCoreApplication::translate("Registration", "REGISTER", nullptr));
        label_5->setText(QCoreApplication::translate("Registration", "Confirm:", nullptr));
        label_name_app->setText(QCoreApplication::translate("Registration", "<html><head/><body><p align=\"center\">HEALSTY</p></body></html>", nullptr));
#if QT_CONFIG(tooltip)
        label_reg->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        label_reg->setText(QCoreApplication::translate("Registration", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Arial Black'; font-size:9pt; font-weight:700; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Register yourself</p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Registration: public Ui_Registration {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTRATION_H
