#ifndef PAGE_LOGIN_H
#define PAGE_LOGIN_H
#include <StuManage.h>
#include <QWidget>

namespace Ui {
class page_Login;
}

class page_Login : public QWidget
{
    Q_OBJECT

public:
    explicit page_Login(QWidget *parent = nullptr);
    ~page_Login();

private slots:
    void on_quitButton_clicked();
    void on_loginButton_clicked();

private:
    Ui::page_Login *ui;
signals:
    void sendLoginSuccess(const Student *User);
    void sendLoginSuccess_m();
};

#endif // PAGE_LOGIN_H
