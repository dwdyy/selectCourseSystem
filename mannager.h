#ifndef MANNAGER_H
#define MANNAGER_H
#include<QMessageBox>
#include <QMainWindow>
#include "page_login.h"
#include<QTreeWidgetItem>
#include<map>
#include <QMainWindow>

namespace Ui {
class mannager;
}

class mannager : public QMainWindow
{
    Q_OBJECT
protected:
    void closeEvent(QCloseEvent *event) override ;
public:
    explicit mannager(QWidget *parent = nullptr);
    ~mannager();

private:
    Ui::mannager *ui;
    void student_layout();
    void course_layout(std::string context );
    QString serarchConetxt;
    void diaryLayout();
public slots:
    void Successlogmannager();
private slots:
    void onTreeitemClicked(QTreeWidgetItem *item, int column);
    void on_acButton_clicked();
    void on_asButton_clicked();
    void on_dsButton_clicked();
    void on_dcButton_clicked();
    void on_searchEdit_textChanged(const QString &arg1);
    void on_serachButton_clicked();
    void on_modifyCourse_clicked();
    void on_modifyStudent_clicked();
};

#endif // MANNAGER_H
