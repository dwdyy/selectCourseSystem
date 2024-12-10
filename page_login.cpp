#include "page_login.h"
#include "ui_page_login.h"
#include <QMessageBox.h>

extern ManagerData managerData;
extern StudentData studentData;
extern CourseData courseData;
extern StudentCourseData scData;

page_Login::page_Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::page_Login)
{
    ui->setupUi(this);
}

page_Login::~page_Login()
{
    delete ui;
}

void page_Login::on_quitButton_clicked()
{
    exit(0);
}


void page_Login::on_loginButton_clicked()
{
    // 数据库查找用户名和密码
    std::string name = ui->nameEdit->text().toStdString();
    std::string pwd = ui->pwdEdit->text().toStdString();
    if(StudentRegister_check(studentData,name,pwd)){
        emit sendLoginSuccess(StudentRegister_getInfo(studentData,name));
        this->hide();
    }
    else {
        if(ManagerRegister(managerData,name,pwd)){
            emit sendLoginSuccess_m();
            this->hide();
        }
        else {
            QMessageBox err;
            err.setText("账号或密码错误");
            err.exec();
        }
    }

}

