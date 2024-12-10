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
// if opt == 3 modify student
// if opt == 4 modift course


class myLinkedList{


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
            Course getAftCoutse(){return aftCourse;}
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
        }
        // 在pos后面加入x节点
        void insertAft(file_node* pos,file_node* x){
            if(pos->getLinkNext()!=NULL) {
                x->linkToNext(pos->getLinkNext());
                pos->getLinkNext()->linkToPre(x);
            }
            pos->linkToNext(x);
            x->linkToPre(pos);
        }
        // 删去pos节点
        void deleteNode(file_node*pos){
            if(pos->getLinkNext() == NULL){
                if(pos->getLinkPre() == NULL) {
                    // 若判断到这里出现bug
                    qDebug() << "WRONG on deltenode in linkedList";
                    delete pos ;
                }else {
                    delete pos;
                }
            }else {
                if(pos->getLinkPre() == NULL){
                    // 若判断到这里出现bug
                    qDebug() << "WRONG on deltenode in linkedList";
                    delete pos;
                }else {
                    pos->getLinkPre()->linkToNext(pos->getLinkNext());
                    pos->getLinkNext()->linkToPre(pos->getLinkPre());
                    delete pos ;
                }
            }
        }
        file_node* getHead(){return HEAD;}
};
