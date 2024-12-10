#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QMessageBox>
#include <QMainWindow>
#include "page_login.h"
#include <mannager.h>
#include<QTreeWidgetItem>
#include<map>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
protected:
    void closeEvent(QCloseEvent *event) override ;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void CheckSelected_n_totalCred(const StudentCourseData& scData, const Student& user);
    void StudentSystem(StudentModuleTools, CourseData& cData, StudentCourseData& scData, Student s);
    void CheckOptionalCourses(const CourseData& data,std::string context);
private:
    Ui::MainWindow *ui;
    page_Login m_dlgLogin;
    mannager m_mannager;
    QString serarchConetxt;
private slots:
    void onTreeitemClicked(QTreeWidgetItem *item, int column);
    void on_chooseButton_clicked();
    void on_quitButton_clicked();
    void on_searchEdit_textChanged(const QString &arg1);
    void on_serachButton_clicked();
};
#endif // MAINWINDOW_H
