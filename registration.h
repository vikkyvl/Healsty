#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QWidget>

namespace Ui {
class Registration;
}

class Registration : public QWidget
{
    Q_OBJECT

public:
    explicit Registration(QWidget *parent = nullptr);
    ~Registration();
    QString getName();
    QString getPass();
    bool checkPass();
    void clearPasswordFields();
    QString getConfirmation();

signals:
    void register_button_clicked2();

private slots:
    void on_nameLineEdit_textEdited(const QString &arg1);

    void on_passwordLineEdit_textEdited(const QString &arg1);

    void on_confirmLineEdit_textEdited(const QString &arg1);

    void on_registerPushButton_clicked();

private:
    Ui::Registration *ui;
    QString m_userName;
    QString m_userPass;
    QString m_confirmation;
};

#endif // REGISTRATION_H
