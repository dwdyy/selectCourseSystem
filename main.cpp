#include "mainwindow.h"
#include <QMessageBox>
#include <fstream>
#include <QApplication>
#include <mannager.h>
ManagerData managerData;
StudentData studentData;
CourseData courseData;
StudentCourseData scData;

// 用于在程序一开始执行拷贝数据操作
void ReadFiles();
// 保存数据
void SaveData();

void MainWindow::closeEvent(QCloseEvent *event) {
    SaveData();
    QMainWindow::closeEvent(event);
}
//#pragma execution_character_set("utf-8")
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ReadFiles();
    MainWindow w;
    return a.exec();
}

void CopyStudentData()
{
    std::fstream fData;
    fData.open("StudentData.txt", std::ios::in);
    std::string data1;
    std::string data2;
    std::string data3;
    std::string data4;
    std::string data5;

    if (fData.is_open())
    {
        while (!fData.eof())
        {
            fData >> data1;
            fData >> data2;
            fData >> data3;
            fData >> data4;
            fData >> data5;
            Student temp(data1, data2, data3, data4, data5);
            studentData.data.push_back(temp);
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("找不到学生数据");
        msgBox.exec();
    }
}

void CopyManagerData()
{
    std::fstream fData;
    fData.open("ManagerData.txt", std::ios::in);
    std::string data1;
    std::string data2;

    if (fData.is_open())
    {
        while (!fData.eof())
        {
            fData >> data1;
            fData >> data2;
            Manager temp(data1, data2);
            managerData.data.push_back(temp);
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("找不到管理员数据");
        msgBox.exec();
    }
}

void CopyCourseData()
{
    std::fstream fData;
    fData.open("CourseData.txt", std::ios::in);
    std::string data1;
    std::string data2;
    std::string data3;
    std::string data4;
    std::string data5;
    std::string data6;

    if (fData.is_open())
    {
        while (!fData.eof())
        {
            fData >> data1;
            fData >> data2;
            fData >> data3;
            fData >> data4;
            fData >> data5;
            fData >> data6;
            //将data3和data4的字符串数据转换为int类型数据
            int result1 = std::atoi(data3.c_str());
            int result2 = std::atoi(data4.c_str());
            int result3 = std::atoi(data5.c_str());

            Course temp(data1, data2, result1, result2, result3, data6);
            courseData.data.push_back(temp);
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("找不到课程数据");
        msgBox.exec();
    }
}
void CopyStudentCourseData()
{
    std::fstream fData;
    fData.open("StudentCourseData.txt", std::ios::in);
    std::string data1;
    std::string data2;
    std::string data3;
    std::string data4;
    std::string data5;

    if (fData.is_open())
    {
        while (!fData.eof())
        {
            fData >> data1;
            fData >> data2;
            fData >> data3;
            fData >> data4;
            fData >> data5;
            //将data3和data4的字符串数据转换为int类型数据
            int result1 = std::atoi(data5.c_str());
            StudentCourse temp(data1, data2, data3, data4, result1);
            // 拷贝剩余的选课数据
            for (int i = 0; i < result1; i++)
            {
                std::string data1;
                std::string data2;
                std::string data3;
                std::string data4;
                int c = std::atoi(data3.c_str());
                fData >> data1;
                fData >> data2;
                fData >> c;
                fData >> data4;
                temp.selectedCourses.push_back(
                    Course(data1, data2, c, data4)
                    );
            }
            scData.data.push_back(temp);
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("找不到学生课程数据");
        msgBox.exec();
    }
}
void ReadFiles()
{
    CopyStudentData();
    CopyManagerData();
    CopyCourseData();
    CopyStudentCourseData();
}


// 保存所有学生数据
void SaveStudentData()
{
    std::fstream fData;
    fData.open("StudentData.txt", std::ios::out);
    std::string data1;
    std::string data2;
    std::string data3;
    std::string data4;
    std::string data5;

    if (fData.is_open())
    {
        for (size_t i = 0; i < studentData.data.size(); i++)
        {
            data1 = studentData.data[i].GetMajor();
            data2 = studentData.data[i].GetClassNum();
            data3 = studentData.data[i].GetID();
            data4 = studentData.data[i].GetName();
            data5 = studentData.data[i].GetPassword();

            fData << data1;
            fData << " ";
            fData << data2;
            fData << " ";
            fData << data3;
            fData << " ";
            fData << data4;
            fData << " ";
            fData << data5;
            if(!(i + 1 == studentData.data.size()))
                fData << std::endl;
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("文件未保存");
        msgBox.exec();
    }

    fData.close();
}


// 保存所有课程数据
void SaveCourseData()
{
    std::fstream fData;
    fData.open("CourseData.txt", std::ios::out);
    std::string data1;
    std::string data2;
    int data3;
    int data4;
    int data5;
    std::string data6;

    if (fData.is_open())
    {
        for (size_t i = 0; i < courseData.data.size(); i++)
        {
            data1 = courseData.data[i].GetCourseNum();
            data2 = courseData.data[i].GetCourseName();
            data3 = courseData.data[i].GetCourseCredit();
            data4 = courseData.data[i].GetCourseLimit();
            data5 = courseData.data[i].GetCoursePop();
            data6 = courseData.data[i].GetTeacherName();

            fData << data1;
            fData << " ";
            fData << data2;
            fData << " ";
            fData << data3;
            fData << " ";
            fData << data4;
            fData << " ";
            fData << data5;
            fData << " ";
            fData << data6;
            if (!(i + 1 == courseData.data.size()))
                fData << std::endl;
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("文件未保存");
        msgBox.exec();
    }

    fData.close();
}

// 保存所有管理员数据
void SaveManagerData()
{
    std::fstream fData;
    fData.open("ManagerData.txt", std::ios::out);
    std::string data1;
    std::string data2;

    if (fData.is_open())
    {
        for (size_t i = 0; i < managerData.data.size(); i++)
        {
            data1 = managerData.data[i].GetName();
            data2 = managerData.data[i].GetPassword();

            fData << data1;
            fData << " ";
            fData << data2;
            if(!(i + 1 == managerData.data.size()))
                fData << std::endl;
        }
    }
    else
    {        QMessageBox msgBox;
        msgBox.setText("文件未保存");
        msgBox.exec();
    }

    fData.close();
}

// 保存所有学生选课数据
void SaveStudentCourseData()
{
    std::fstream fData;
    fData.open("StudentCourseData.txt", std::ios::out);
    std::string data1;
    std::string data2;
    std::string data3;
    std::string data4;
    int data5;

    if (fData.is_open())
    {
        for (size_t i = 0; i < scData.data.size(); i++)
        {
            data1 = scData.data[i].GetMajor();
            data2 = scData.data[i].GetClassNum();
            data3 = scData.data[i].GetID();
            data4 = scData.data[i].GetName();
            data5 = scData.data[i].GetSelectedCourseNum();

            fData << data1;
            fData << " ";
            fData << data2;
            fData << " ";
            fData << data3;
            fData << " ";
            fData << data4;
            fData << " ";
            fData << data5;

            for (int c = 0; c < data5; c++)
            {
                std::string d1 = scData.data[i].selectedCourses[c].GetCourseNum();
                std::string d2 = scData.data[i].selectedCourses[c].GetCourseName();
                int d3 = scData.data[i].selectedCourses[c].GetCourseCredit();
                std::string d4 = scData.data[i].selectedCourses[c].GetTeacherName();

                fData << " ";
                fData << d1;
                fData << " ";
                fData << d2;
                fData << " ";
                fData << d3;
                fData << " ";
                fData << d4;
            }
            if(!(i + 1 == scData.data.size()))
                fData << std::endl;
        }
    }
    else
    {        QMessageBox msgBox;
        msgBox.setText("文件未保存");
        msgBox.exec();
    }

    fData.close();
}

// 保存数据
void SaveData()
{
    SaveStudentData();
    SaveCourseData();
    SaveManagerData();
    SaveStudentCourseData();
}
