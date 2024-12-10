#include "mainwindow.h"
#include "ui_mainwindow.h"
static const User *user;

extern ManagerData managerData;
extern StudentData studentData;
extern CourseData courseData;
extern StudentCourseData scData;

static StudentModuleTools studentTools;
static ManagerModuleTools managerTools;
static Student _user ;
static std::map<std::string,bool>mp;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_dlgLogin.show();
    auto f = [&](const Student *User){
        user = User;
        Student temp = *(Student*)user;
        _user = *(Student*)user;
        ui->nameLabel->setText("欢迎您:"+QString::fromLocal8Bit(temp.GetName()));
        ui->idLabel->setText("学号"+QString::fromLocal8Bit(temp.GetID()));
        this->show();
        MainWindow::CheckSelected_n_totalCred(scData,_user);
        ui->mainTable->hide();
        ui->chooseTable->hide();
        ui->chooseButton->hide();
        ui->quitButton->hide();
        ui->serachButton->hide();
        ui->searchEdit->hide();
        // MainWindow::StudentSystem(studentTools, courseData, scData, temp);
        ui->mainTable->setSelectionMode(QAbstractItemView::SingleSelection);
        //设置选择行
        ui->mainTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->mainTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->chooseTable->setSelectionMode(QAbstractItemView::SingleSelection);
        //设置选择行
        ui->chooseTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->chooseTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    };
    connect(&m_dlgLogin,&page_Login::sendLoginSuccess,this,f);
    connect(ui->treeWidget,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(onTreeitemClicked(QTreeWidgetItem*,int)));
    connect(&m_dlgLogin,&page_Login::sendLoginSuccess_m,&m_mannager,&mannager::Successlogmannager);
    ui->treeWidget->setColumnCount(1);

    QStringList pas1 ;
    pas1 << "课程管理";
    QTreeWidgetItem *p = new QTreeWidgetItem(ui->treeWidget,pas1);
    ui->treeWidget->addTopLevelItem(p);
    pas1.clear();
    pas1 << "我的课程";
    QTreeWidgetItem *p2 = new QTreeWidgetItem(p,pas1);
    pas1.clear();
    pas1 << "选课";
    QTreeWidgetItem *p3 = new QTreeWidgetItem(p,pas1);

    p->addChild(p3);
    p->addChild(p2);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onTreeitemClicked(QTreeWidgetItem *item, int column){
    if(item->text(0) == "我的课程"){
        MainWindow::CheckSelected_n_totalCred(scData,_user);
        ui->mainTable->show();
        ui->quitButton->show();
        ui->chooseButton->hide();
        ui->chooseTable->hide();
        ui->serachButton->hide();
        ui->searchEdit->hide();
    }
    if(item->text(0) == "选课"){
        MainWindow::CheckOptionalCourses(courseData,serarchConetxt.toStdString());
        ui->chooseTable->show();
        ui->chooseButton->show();
        ui->quitButton->hide();
        ui->mainTable->hide();
        ui->serachButton->show();
        ui->searchEdit->show();
    }
}

void MainWindow::StudentSystem(StudentModuleTools, CourseData& cData, StudentCourseData& scData, Student s){
    MainWindow::CheckSelected_n_totalCred(scData,s);
   // ui->mainTable->show();
    return ;
}
void MainWindow::CheckSelected_n_totalCred(const StudentCourseData& scData, const Student& user)
{
    mp.clear();
    // 查找到该用户的学生选课数据
    const StudentCourse* user_sc = NULL;
    for (size_t c = 0; c < scData.data.size(); c++)
    {
        if (scData.data[c].GetID() == user.GetID())
        {
            // 如果找到了，添加引用
            user_sc = &(scData.data[c]);
        }
    }
    if (user_sc == NULL)
    {
        return;
    }
    else
    {
        QStringList headers;
        headers << "课程代码" << "课程名称" << "学分"  << "授课教师" ;
        this->ui->mainTable->setColumnCount(4);
        this->ui->mainTable->setRowCount(user_sc->selectedCourses.size());
        this->ui->mainTable->setHorizontalHeaderLabels(headers);
        for (size_t i = 0; i < user_sc->selectedCourses.size(); i++)
        {
            this->ui->mainTable->setItem(i,0,new QTableWidgetItem(QString::fromLocal8Bit(user_sc->selectedCourses[i].GetCourseNum())));
            mp[user_sc->selectedCourses[i].GetCourseNum()] = 1;
            this->ui->mainTable->setItem(i,1,new QTableWidgetItem(QString::fromLocal8Bit(user_sc->selectedCourses[i].GetCourseName())));
            std::string x = std::to_string(user_sc->selectedCourses[i].GetCourseCredit());
            this->ui->mainTable->setItem(i,2,new QTableWidgetItem(QString::fromLocal8Bit(x)));
            this->ui->mainTable->setItem(i,3,new QTableWidgetItem(QString::fromLocal8Bit(user_sc->selectedCourses[i].GetTeacherName())));
        }
    }
}
void MainWindow::CheckOptionalCourses(const CourseData& data,std::string context = "")
{
    // 用于保存所有可以选择的课程信息
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
    this->ui->chooseTable->setColumnCount(6);
    this->ui->chooseTable->setRowCount(temp.data.size());
    this->ui->chooseTable->setHorizontalHeaderLabels(headers);
    int cnt = 0 ;
    for (size_t i = 0; i < temp.data.size(); i++)
    {
        if(mp[temp.data[i].GetCourseNum()] == 1) continue;
        if(temp.data[i].GetCourseNum().find(context) == std::string::npos && temp.data[i].GetCourseName().find(context) == std::string::npos && temp.data[i].GetTeacherName().find(context) == std::string::npos )
            continue;
        this->ui->chooseTable->setItem(cnt,0,new QTableWidgetItem(QString::fromLocal8Bit(temp.data[i].GetCourseNum())));
        this->ui->chooseTable->setItem(cnt,1,new QTableWidgetItem(QString::fromLocal8Bit(temp.data[i].GetCourseName())));
        std::string x = std::to_string(temp.data[i].GetCourseCredit());
        this->ui->chooseTable->setItem(cnt,2,new QTableWidgetItem(QString::fromLocal8Bit(x)));
        x = std::to_string(temp.data[i].GetCourseLimit());
        this->ui->chooseTable->setItem(cnt,3,new QTableWidgetItem(QString::fromLocal8Bit(x)));
        x = std::to_string(temp.data[i].GetCoursePop());
        this->ui->chooseTable->setItem(cnt,4,new QTableWidgetItem(QString::fromLocal8Bit(x)));
        this->ui->chooseTable->setItem(cnt,5,new QTableWidgetItem(QString::fromLocal8Bit(temp.data[i].GetTeacherName())));
        cnt ++ ;
    }
    this->ui->chooseTable->setRowCount(cnt);
}


void MainWindow::on_chooseButton_clicked()
{
    QList<QTableWidgetItem*> items = ui->chooseTable->selectedItems();
    if(items.empty()) {
        QMessageBox::warning(this,"Warning","您未选中任何课程");
        return ;
    }
    QString text = items.at(0)->text(); //获取内容
    studentTools.SelectCourse(courseData,scData,_user,std::string(text.toLocal8Bit()));
    MainWindow::CheckSelected_n_totalCred(scData,_user);
    MainWindow::CheckOptionalCourses(courseData,serarchConetxt.toStdString());
}


void MainWindow::on_quitButton_clicked()
{
    QList<QTableWidgetItem*> items = ui->mainTable->selectedItems();
    if(items.empty()) {
        QMessageBox::warning(this,"Warning","您未选中任何课程");
        return ;
    }
    QString text = items.at(0)->text(); //获取内容
    studentTools.DeleteCourse(courseData,scData,_user,std::string(text.toLocal8Bit()));
    MainWindow::CheckSelected_n_totalCred(scData,_user);
    MainWindow::CheckOptionalCourses(courseData,serarchConetxt.toStdString());
}




void MainWindow::on_searchEdit_textChanged(const QString &arg1)
{
    serarchConetxt = arg1;
}


void MainWindow::on_serachButton_clicked()
{
    MainWindow::CheckOptionalCourses(courseData,std::string(serarchConetxt.toLocal8Bit()));
}

