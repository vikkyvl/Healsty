#include "registration.h"
#include "ui_registration.h"

Registration::Registration(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Registration)
{
    ui->setupUi(this);

    QRegularExpression regex("[a-zA-Z0-9]+");
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(regex, this);

    ui->nameLineEdit->setValidator(validator);
    ui->passwordLineEdit->setValidator(validator);
    ui->confirmLineEdit->setValidator(validator);
}

Registration::~Registration()
{
    delete ui;
}

void Registration::on_nameLineEdit_textEdited(const QString &arg1)
{
    Registration::m_userName = arg1;
}

void Registration::on_passwordLineEdit_textEdited(const QString &arg1)
{
    Registration::m_userPass = arg1;
}


void Registration::on_confirmLineEdit_textEdited(const QString &arg1)
{
    Registration::m_confirmation = arg1;
}

void Registration::on_registerPushButton_clicked()
{
    emit register_button_clicked2();
}

QString Registration::getName()
{
    return m_userName;
}

QString Registration::getPass()
{
    return m_userPass;
}

bool Registration::checkPass()
{
    return (m_confirmation == m_userPass);
}

void Registration::clearPasswordFields()
{
    ui->nameLineEdit->clear();
    ui->passwordLineEdit->clear();
    ui->confirmLineEdit->clear();
}

QString Registration::getConfirmation()
{
    return m_confirmation;
}
