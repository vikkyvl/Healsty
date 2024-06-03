#include "authorization.h"
#include "ui_authorization.h"

Authorization::Authorization(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Authorization)
{
    ui->setupUi(this);

    QRegularExpression regex("[a-zA-Z0-9]+");
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(regex, this);

    ui->nameLineEdit->setValidator(validator);
    ui->passwordLineEdit->setValidator(validator);
}

Authorization::~Authorization()
{
    delete ui;
}

void Authorization::on_nameLineEdit_textEdited(const QString &arg1)
{
    Authorization::m_username = arg1;
}

void Authorization::on_passwordLineEdit_textEdited(const QString &arg1)
{
    Authorization::m_userpass = arg1;
}

void Authorization::on_loginPushButton_clicked()
{
    emit login_button_clicked();
}

void Authorization::on_registerPushButton_clicked()
{
    emit register_button_clicked();
}

QString Authorization::getLogin()
{
    return Authorization::m_username;
}

QString Authorization::getPass()
{
    return Authorization::m_userpass;
}

