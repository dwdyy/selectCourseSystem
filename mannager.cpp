#include "mannager.h"
#include "ui_mannager.h"
#include <QInputDialog.h>
#include <QFormLayout.h>
static const User *user;

extern ManagerData managerData;
extern StudentData studentData;
extern CourseData courseData;
extern StudentCourseData scData;
extern void SaveData();
static StudentModuleTools studentTools;
static ManagerModuleTools managerTools;
mannager::mannager(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mannager)
{
    ui->setupUi(this);
    connect(ui->treeWidget,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(onTreeitemClicked(QTreeWidgetItem*,int)));
    ui->treeWidget->setColumnCount(1);
    ui->acButton->hide();
    ui->asButton->hide();
    ui->dcButton->hide();
    ui->dsButton->hide();
    ui->studentTable->hide();
    ui->courseTable->hide();
    ui->serachButton->hide();
    ui->searchEdit->hide();
    ui->modifyCourse->hide();
    ui->modifyStudent->hide();
    // MainWindow::StudentSystem(studentTools, courseData, scData, temp);
    ui->courseTable->setSelectionMode(QAbstractItemView::SingleSelection);
    //设置选择行
    ui->courseTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->courseTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->studentTable->setSelectionMode(QAbstractItemView::SingleSelection);
    //设置选择行
    ui->studentTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->studentTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QStringList pas1 ;
    pas1 << "信息管理";
    QTreeWidgetItem *p = new QTreeWidgetItem(ui->treeWidget,pas1);
    ui->treeWidget->addTopLevelItem(p);
    pas1.clear();
    pas1 << "学生管理";
    QTreeWidgetItem *p2 = new QTreeWidgetItem(p,pas1);
    pas1.clear();
    pas1 << "课程管理";
    QTreeWidgetItem *p3 = new QTreeWidgetItem(p,pas1);
    p->addChild(p3);
    p->addChild(p2);
}

void mannager::Successlogmannager(){
    ui->courseTable->hide();
    ui->studentTable->hide();
    this->show();

}
void mannager::student_layout(){
    QStringList headers;
    headers << "专业" << "班级" << "学号"<<"姓名" << "登录密码";
    this->ui->studentTable->setColumnCount(5);
    this->ui->studentTable->setRowCount(studentData.data.size());
    this->ui->studentTable->setHorizontalHeaderLabels(headers);

    sort(studentData.data.begin(), studentData.data.end(),[](Student a, Student b){
        return a.GetID() < b.GetID();
    });

    for (size_t i = 0; i < studentData.data.size(); i++)
    {
        this->ui->studentTable->setItem(i,0,new QTableWidgetItem(QString::fromLocal8Bit(studentData.data[i].GetMajor())));
        this->ui->studentTable->setItem(i,1,new QTableWidgetItem(QString::fromLocal8Bit(studentData.data[i].GetClassNum())));
        this->ui->studentTable->setItem(i,2,new QTableWidgetItem(QString::fromLocal8Bit(studentData.data[i].GetID())));
        this->ui->studentTable->setItem(i,3,new QTableWidgetItem(QString::fromLocal8Bit(studentData.data[i].GetName())));
        this->ui->studentTable->setItem(i,4,new QTableWidgetItem(QString::fromLocal8Bit(studentData.data[i].GetPassword())));
    }
}
void mannager::course_layout(std::string context = ""){
    // 用于保存所有可以选择的课程信息
    CourseData data = courseData;
    CourseData temp;
    for (size_t i = 0; i < data.data.size(); i++)
    {
        if (!data.data[i].isFull())
        {
            temp.data.push_back(data.data[i]);
        }
    }
    // 打印所有可选课程信息

    QStringList headers;
    headers << "课程代码" << "课程名称" << "学分"<<"课程容量" << "选课人数" << "授课教师" ;
    this->ui->courseTable->setColumnCount(6);
    this->ui->courseTable->setRowCount(temp.data.size());
    this->ui->courseTable->setHorizontalHeaderLabels(headers);
    int cnt = 0 ;
    sort(temp.data.begin(),temp.data.end(),[](Course a,Course b){
        return a.GetCourseNum() < b.GetCourseNum();
    });
    for (size_t i = 0; i < temp.data.size(); i++)
    {
       // qDebug() <<QString::fromLocal8Bit( temp.data[i].GetTeacherName() ) ;
        if(temp.data[i].GetCourseNum().find(context) == std::string::npos && temp.data[i].GetCourseName().find(context) == std::string::npos && temp.data[i].GetTeacherName().find(context) == std::string::npos )
            continue;
        this->ui->courseTable->setItem(cnt,0,new QTableWidgetItem(QString::fromLocal8Bit(temp.data[i].GetCourseNum())));
        this->ui->courseTable->setItem(cnt,1,new QTableWidgetItem(QString::fromLocal8Bit(temp.data[i].GetCourseName())));
        std::string x = std::to_string(temp.data[i].GetCourseCredit());
        this->ui->courseTable->setItem(cnt,2,new QTableWidgetItem(QString::fromLocal8Bit(x)));
        x = std::to_string(temp.data[i].GetCourseLimit());
        this->ui->courseTable->setItem(cnt,3,new QTableWidgetItem(QString::fromLocal8Bit(x)));
        x = std::to_string(temp.data[i].GetCoursePop());
        this->ui->courseTable->setItem(cnt,4,new QTableWidgetItem(QString::fromLocal8Bit(x)));
        this->ui->courseTable->setItem(cnt,5,new QTableWidgetItem(QString::fromLocal8Bit(temp.data[i].GetTeacherName())));
        cnt ++ ;
    }
    this->ui->courseTable->setRowCount(cnt);
}
void mannager::onTreeitemClicked(QTreeWidgetItem *item, int column){
    if(item->text(0) == "学生管理"){
        mannager::student_layout();
        ui->studentTable->show();
        ui->asButton->show();
        ui->dsButton->show();
        ui->acButton->hide();
        ui->dcButton->hide();
        ui->courseTable->hide();
        ui->serachButton->hide();
        ui->searchEdit->hide();
        ui->modifyStudent->show();
        ui->modifyCourse->hide();
    }
    else if(item->text(0) == "课程管理"){
        mannager::course_layout(std::string(mannager::serarchConetxt.toLocal8Bit()));
        ui->courseTable->show();
        ui->acButton->show();
        ui->dcButton->show();
        ui->asButton->hide();
        ui->dsButton->hide();
        ui->studentTable->hide();
        ui->serachButton->show();
        ui->searchEdit->show();
        ui->modifyStudent->hide();
        ui->modifyCourse->show();
    }
}

mannager::~mannager()
{
    delete ui;
}

void mannager::on_acButton_clicked()
{
    QDialog dialog(this);
    // Use a layout allowing to have a label next to each field
    QFormLayout form(&dialog);

    // Add some text above the fields
    form.addRow(new QLabel("添加信息"));

    // Add the lineEdits with their respective labels
    QStringList headers;
    headers << "课程代码" << "课程名称" << "学分" <<"课程容量"  << "授课教师" ;
    QList<QLineEdit *> fields;
    for(int i = 0; i < 5; ++i) {
        QLineEdit *lineEdit = new QLineEdit(&dialog);
        QString label = headers.at(i).arg(i + 1);
        form.addRow(label, lineEdit);
        fields << lineEdit;
    }

    // Add some standard buttons (Cancel/Ok) at the bottom of the dialog
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    // Show the dialog as modal
    if (dialog.exec() == QDialog::Accepted) {
        // If the user didn't dismiss the dialog, do something with the fields
        std::string data1 = std::string(fields.at(0)->text().toLocal8Bit());
        std::string data2 = std::string(fields.at(1)->text().toLocal8Bit());
        auto data3 = fields.at(2)->text().toInt();
        auto data4 = fields.at(3)->text().toInt();
        std::string data5 = std::string(fields.at(4)->text().toLocal8Bit());
        if(data1.empty() || data2.empty() || fields.at(2)->text().isEmpty() ||fields.at(3)->text().isEmpty() || data5.empty()){
            QMessageBox::warning(this,"Warning","内容不能为空");
        }else {
        courseData.data.push_back(Course(data1, data2, data3, data4, 0, data5));
        }
    }
    course_layout();
}

void mannager::closeEvent(QCloseEvent *event) {
    SaveData();
    QMainWindow::closeEvent(event);
}


void mannager::on_asButton_clicked()
{
    QDialog dialog(this);
    // Use a layout allowing to have a label next to each field
    QFormLayout form(&dialog);

    // Add some text above the fields
    form.addRow(new QLabel("添加信息"));

    // Add the lineEdits with their respective labels
    QStringList headers;
    headers << "专业" << "班级" << "学号" <<"姓名"  << "登录密码" ;
    QList<QLineEdit *> fields;
    for(int i = 0; i < 5; ++i) {
        QLineEdit *lineEdit = new QLineEdit(&dialog);
        QString label = headers.at(i).arg(i + 1);
        form.addRow(label, lineEdit);
        fields << lineEdit;
    }

    // Add some standard buttons (Cancel/Ok) at the bottom of the dialog
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    // Show the dialog as modal
    if (dialog.exec() == QDialog::Accepted) {
        // If the user didn't dismiss the dialog, do something with the fields
        std::string data1 = std::string(fields.at(0)->text().toLocal8Bit());
        std::string data2 = std::string(fields.at(1)->text().toLocal8Bit());
        auto data3 = std::string(fields.at(2)->text().toLocal8Bit());
        auto data4 = std::string(fields.at(3)->text().toLocal8Bit());
        std::string data5 = std::string(fields.at(4)->text().toLocal8Bit());

        if(data1.empty() || data2.empty() || fields.at(2)->text().isEmpty() ||fields.at(3)->text().isEmpty()){
            QMessageBox::warning(this,"Warning","内容不能为空");
        }
        else {
            Student stemp(data1, data2, data3, data4, data5);
            StudentCourse sctemp(data1, data2, data3, data4);
            studentData.data.push_back(stemp);
            scData.data.push_back(sctemp);
        }
    }
    student_layout();
}


void mannager::on_dsButton_clicked()
{
    QList<QTableWidgetItem*> items = ui->studentTable->selectedItems();
    if(items.empty()) {
        QMessageBox::warning(this,"Warning","您未选中任何学生");
        return ;
    }
    QString text = items.at(2)->text(); //获取内容
    managerTools.Manage_Delete(studentData,scData,courseData,std::string(text.toLocal8Bit()));
    student_layout();
}


void mannager::on_dcButton_clicked()
{
    QList<QTableWidgetItem*> items = ui->courseTable->selectedItems();
    if(items.empty()) {
        QMessageBox::warning(this,"Warning","您未选中任何课程");
        return ;
    }
    QString text = items.at(0)->text(); //获取内容
    managerTools.Manage_Delete(courseData,scData,std::string(text.toLocal8Bit()));
    course_layout(std::string(mannager::serarchConetxt.toLocal8Bit()));
}


void mannager::on_searchEdit_textChanged(const QString &arg1)
{
    mannager::serarchConetxt = arg1;
}


void mannager::on_serachButton_clicked()
{
    mannager::course_layout(std::string(mannager::serarchConetxt.toLocal8Bit()));
}


void mannager::on_modifyCourse_clicked()
{
    QList<QTableWidgetItem*> items = ui->courseTable->selectedItems();
    if(items.empty()) {
        QMessageBox::warning(this,"Warning","请选中课程后在进行修改");
        return ;
    }
    QDialog dialog(this);
    // Use a layout allowing to have a label next to each field
    QFormLayout form(&dialog);

    // Add some text above the fields
    form.addRow(new QLabel("添加信息"));

    // Add the lineEdits with their respective labels
    QStringList headers;
    headers << "课程代码" << "课程名称" << "学分" <<"课程容量"  << "授课教师" ;
    QList<QLineEdit *> fields;
    for(int i = 0; i < 5; ++i) {
        QLineEdit *lineEdit = new QLineEdit(&dialog);
        QString label = headers.at(i).arg(i + 1);
        form.addRow(label, lineEdit);
        fields << lineEdit;
        lineEdit->setText(i != 4 ? items.at(i)->text() :items.at(5)->text());
    }

    // Add some standard buttons (Cancel/Ok) at the bottom of the dialog
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    // Show the dialog as modal
    if (dialog.exec() == QDialog::Accepted) {
        // If the user didn't dismiss the dialog, do something with the fields
        std::string data1 = std::string(fields.at(0)->text().toLocal8Bit());
        std::string data2 = std::string(fields.at(1)->text().toLocal8Bit());
        auto data3 = fields.at(2)->text().toInt();
        auto data4 = fields.at(3)->text().toInt();
        std::string data5 = std::string(fields.at(4)->text().toLocal8Bit());
        if(data1.empty() || data2.empty() || fields.at(2)->text().isEmpty() ||fields.at(3)->text().isEmpty() || data5.empty()){
            QMessageBox::warning(this,"Warning","内容不能为空");
        }else {
            Course temp = Course(data1, data2, data3, data4, items.at(4)->text().toInt(), data5);
            on_dcButton_clicked();
            courseData.data.push_back(temp);
        }
    }
    course_layout();
}


void mannager::on_modifyStudent_clicked()
{
    QList<QTableWidgetItem*> items = ui->studentTable->selectedItems();
    if(items.empty()) {
        QMessageBox::warning(this,"Warning","请选中课程后在进行修改");
        return ;
    }
    QDialog dialog(this);
    // Use a layout allowing to have a label next to each field
    QFormLayout form(&dialog);

    // Add some text above the fields
    form.addRow(new QLabel("添加信息"));

    // Add the lineEdits with their respective labels
    QStringList headers;
    headers  << "登录密码" ;
    QList<QLineEdit *> fields;
    for(int i = 0; i < 1; ++i) {
        QLineEdit *lineEdit = new QLineEdit(&dialog);
        QString label = headers.at(i).arg(i + 1);
        form.addRow(label, lineEdit);
        fields << lineEdit;
        lineEdit->setText(items.at(4)->text());
    }

    // Add some standard buttons (Cancel/Ok) at the bottom of the dialog
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    // Show the dialog as modal
    if (dialog.exec() == QDialog::Accepted) {
        // If the user didn't dismiss the dialog, do something with the fields
        std::string data5 = std::string(fields.at(0)->text().toLocal8Bit());
        if(data5.empty()){
            QMessageBox::warning(this,"Warning","内容不能为空");
        }
        else {
            Student stemp(std::string(items.at(0)->text().toLocal8Bit()),
                          std::string(items.at(1)->text().toLocal8Bit()),
                          std::string(items.at(2)->text().toLocal8Bit()),
                          std::string(items.at(3)->text().toLocal8Bit()),
                          data5);
            QString text = items.at(2)->text(); //获取内容
            managerTools.Manage_Delete_nonecourse(studentData,scData,courseData,std::string(text.toLocal8Bit()));
            studentData.data.push_back(stemp);
        }
    }
    student_layout();
}

