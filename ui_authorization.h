/********************************************************************************
** Form generated from reading UI file 'authorization.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTHORIZATION_H
#define UI_AUTHORIZATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Authorization
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label_image;
    QGridLayout *gridLayout_2;
    QLineEdit *nameLineEdit;
    QLabel *label_password;
    QPushButton *loginPushButton;
    QLineEdit *passwordLineEdit;
    QLabel *label_name;
    QLabel *label_auth;
    QLabel *label_name_app;
    QPushButton *registerPushButton;

    void setupUi(QWidget *Authorization)
    {
        if (Authorization->objectName().isEmpty())
            Authorization->setObjectName("Authorization");
        Authorization->resize(500, 400);
        Authorization->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 227, 241);"));
        verticalLayout = new QVBoxLayout(Authorization);
        verticalLayout->setObjectName("verticalLayout");
        label_image = new QLabel(Authorization);
        label_image->setObjectName("label_image");
        label_image->setStyleSheet(QString::fromUtf8("image: url(:/resource/Healthy habit-bro (2).png);"));

        verticalLayout->addWidget(label_image);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName("gridLayout_2");
        nameLineEdit = new QLineEdit(Authorization);
        nameLineEdit->setObjectName("nameLineEdit");
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(255, 255, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        QBrush brush2(QColor(0, 0, 0, 128));
        brush2.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush2);
#endif
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush2);
#endif
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush2);
#endif
        nameLineEdit->setPalette(palette);
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        font.setPointSize(9);
        font.setBold(false);
        font.setItalic(false);
        nameLineEdit->setFont(font);
        nameLineEdit->setStyleSheet(QString::fromUtf8("border: 2px solid gray;\n"
"background-color: rgb(255, 255, 255);\n"
"border-radius: 5px;\n"
"padding: 5px;\n"
"font: 9pt \"Arial\";\n"
"font-size: 1.2em;\n"
"color: black;\n"
"text-shadow: #454545 0 0 2px;"));

        gridLayout_2->addWidget(nameLineEdit, 2, 1, 1, 1);

        label_password = new QLabel(Authorization);
        label_password->setObjectName("label_password");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Arial Black")});
        font1.setBold(true);
        label_password->setFont(font1);

        gridLayout_2->addWidget(label_password, 3, 0, 1, 1);

        loginPushButton = new QPushButton(Authorization);
        loginPushButton->setObjectName("loginPushButton");
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Arial Black")});
        font2.setPointSize(9);
        font2.setWeight(QFont::Black);
        font2.setItalic(false);
        loginPushButton->setFont(font2);
        loginPushButton->setStyleSheet(QString::fromUtf8("QPushButton#loginPushButton {\n"
"float: right;\n"
"border-bottom: 4px solid rgb(255, 100, 175);\n"
"font: 900 9pt \"Arial Black\";\n"
"margin-right: 3%;\n"
"margin-top: 5px;\n"
"border-radius: 5px;\n"
"-moz-border-radius: 5px;\n"
"-webkit-border-radius: 5px;\n"
"padding: 5px 9px;\n"
"font-size: 1.2em;\n"
"background-color: rgb(255, 151, 201);\n"
"text-shadow: #454545 0 0 2px;\n"
"color: white;\n"
"}\n"
"QPushButton#loginPushButton:pressed {\n"
"    background-color: rgb(255, 100, 175);\n"
"    border-style: inset;\n"
"}"));
        loginPushButton->setCheckable(false);
        loginPushButton->setChecked(false);

        gridLayout_2->addWidget(loginPushButton, 4, 1, 1, 1);

        passwordLineEdit = new QLineEdit(Authorization);
        passwordLineEdit->setObjectName("passwordLineEdit");
        passwordLineEdit->setFont(font);
        passwordLineEdit->setStyleSheet(QString::fromUtf8("border: 2px solid gray;\n"
"background-color: rgb(255, 255, 255);\n"
"border-radius: 5px;\n"
"padding: 5px;\n"
"font: 9pt \"Arial\";\n"
"font-size: 1.2em;\n"
"color: black;\n"
"text-shadow: #454545 0 0 2px;"));
        passwordLineEdit->setEchoMode(QLineEdit::Password);

        gridLayout_2->addWidget(passwordLineEdit, 3, 1, 1, 1);

        label_name = new QLabel(Authorization);
        label_name->setObjectName("label_name");
        label_name->setFont(font1);

        gridLayout_2->addWidget(label_name, 2, 0, 1, 1);

        label_auth = new QLabel(Authorization);
        label_auth->setObjectName("label_auth");
        label_auth->setFont(font1);

        gridLayout_2->addWidget(label_auth, 1, 0, 1, 2);

        label_name_app = new QLabel(Authorization);
        label_name_app->setObjectName("label_name_app");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_name_app->sizePolicy().hasHeightForWidth());
        label_name_app->setSizePolicy(sizePolicy);
        label_name_app->setMinimumSize(QSize(476, 50));
        label_name_app->setMaximumSize(QSize(16777215, 16777215));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Arial Black")});
        label_name_app->setFont(font3);
        label_name_app->setStyleSheet(QString::fromUtf8(""));

        gridLayout_2->addWidget(label_name_app, 0, 0, 1, 2);

        registerPushButton = new QPushButton(Authorization);
        registerPushButton->setObjectName("registerPushButton");
        registerPushButton->setFont(font2);
        registerPushButton->setStyleSheet(QString::fromUtf8("QPushButton#registerPushButton {\n"
"float: right;\n"
"border-bottom: 4px solid rgb(255, 100, 175);\n"
"font: 900 9pt \"Arial Black\";\n"
"margin-right: 3%;\n"
"margin-top: 5px;\n"
"border-radius: 5px;\n"
"-moz-border-radius: 5px;\n"
"-webkit-border-radius: 5px;\n"
"padding: 5px 9px;\n"
"font-size: 1.2em;\n"
"background-color: rgb(255, 151, 201);\n"
"text-shadow: #454545 0 0 2px;\n"
"color: white;\n"
"}\n"
"QPushButton#registerPushButton:pressed {\n"
"    background-color: rgb(255, 100, 175);\n"
"    border-style: inset;\n"
"}"));
        registerPushButton->setCheckable(false);
        registerPushButton->setChecked(false);
        registerPushButton->setAutoDefault(false);
        registerPushButton->setFlat(false);

        gridLayout_2->addWidget(registerPushButton, 5, 1, 1, 1);


        verticalLayout->addLayout(gridLayout_2);


        retranslateUi(Authorization);

        registerPushButton->setDefault(false);


        QMetaObject::connectSlotsByName(Authorization);
    } // setupUi

    void retranslateUi(QWidget *Authorization)
    {
        Authorization->setWindowTitle(QCoreApplication::translate("Authorization", "Authorization", nullptr));
        label_image->setText(QString());
        label_password->setText(QCoreApplication::translate("Authorization", "<html><head/><body><p><span style=\" color:#263238;\">Password:</span></p></body></html>", nullptr));
        loginPushButton->setText(QCoreApplication::translate("Authorization", "LOG IN", nullptr));
        label_name->setText(QCoreApplication::translate("Authorization", "<html><head/><body><p><span style=\" color:#263238;\">Name:</span></p></body></html>", nullptr));
        label_auth->setText(QCoreApplication::translate("Authorization", "<html><head/><body><p align=\"center\"><span style=\" color:#263238;\">Authentificate yourself</span></p></body></html>", nullptr));
        label_name_app->setText(QCoreApplication::translate("Authorization", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt; color:#404040;\">HEALSTY</span></p></body></html>", nullptr));
        registerPushButton->setText(QCoreApplication::translate("Authorization", "REGISTER", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Authorization: public Ui_Authorization {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTHORIZATION_H
