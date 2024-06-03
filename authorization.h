#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QWidget>

namespace Ui {
class Authorization;
}

class Authorization : public QWidget
{
    Q_OBJECT

public:
    explicit Authorization(QWidget *parent = nullptr);
    ~Authorization();
    QString getLogin();
    QString getPass();

signals:
    void login_button_clicked();
    void register_button_clicked();

private slots:
    void on_nameLineEdit_textEdited(const QString &arg1);

    void on_passwordLineEdit_textEdited(const QString &arg1);

    void on_loginPushButton_clicked();

    void on_registerPushButton_clicked();

private:
    Ui::Authorization *ui;
    QString m_username;
    QString m_userpass;
};

#endif // AUTHORIZATION_H
