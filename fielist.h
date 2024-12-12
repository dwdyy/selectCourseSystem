#ifndef FIELIST_H
#define FIELIST_H
#include <StuManage.h>
#include <QWidget>
#include <QDateTime>
#endif // FIELIST_H
// if opt == -1 链表头部
// if opt == 0 del course
// if opt == 1 del student
// if opt == 2 add course
// if opt == 3 add student
// if opt == 4 modify student
// if opt == 5 modift course
class file_node{
private:
    QDateTime time;
    int opt ;
    Student preStudent,aftStudent;
    Course preCourse,aftCourse;
    file_node* nex;
    file_node* pre;
public:
    file_node(){nex = pre = NULL;}
    ~file_node();
    int getOpt(){return opt;}
    Student getPreStudent(){return preStudent;}
    Student getAftStudent(){return aftStudent;}
    Course getPreCourse(){return preCourse;}
    Course getAftCourse(){return aftCourse;}
    QDateTime getTime(){return time;}
    file_node* getLinkNext(){return nex;}
    file_node* getLinkPre(){return pre;}
    void linkToNext(file_node* nnex){nex = nnex;}
    void linkToPre(file_node* npre){pre = npre;}
    void setPreStudent(Student x){preStudent = x;}
    void setAftStudent(Student x){aftStudent = x;}
    void setPreCourse(Course x){preCourse = x;}
    void setAftCourse(Course x){aftCourse = x;}
    void setTime(QDateTime x){time = x;}
    void setOpt(int x){opt = x;}
    bool isEnd(){return nex == NULL;}
    bool isBegin(){return pre == NULL;}

};

class myLinkedList{
    private:
        file_node*HEAD;
    public:
        myLinkedList(){
            HEAD = new file_node();
            HEAD->setOpt(-1);
        }
        ~myLinkedList(){
            file_node* res = HEAD;
            while(!res->isEnd()) res = res->getLinkNext();
            while(!res->isBegin()){
                res = res->getLinkPre();
                delete res->getLinkNext();
            }
            delete res;
            HEAD = NULL;
        }
        // 在链表最后加入x
        void insertEnd(file_node *x);
        // 在pos后面加入x节点
        void insertAft(file_node* pos,file_node* x);
        // 删去pos节点
        void deleteNode(file_node*pos);
        file_node* getHead(){return HEAD;}
        int getSize();
};
