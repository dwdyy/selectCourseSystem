#include "fielist.h"

file_node::~file_node(){;}

// 在pos后面加入x节点
void myLinkedList::insertAft(file_node* pos,file_node* x){
    if(pos->getLinkNext()!=NULL) {
        x->linkToNext(pos->getLinkNext());
        pos->getLinkNext()->linkToPre(x);
    }
    pos->linkToNext(x);
    x->linkToPre(pos);
}
// 删去pos节点
void myLinkedList::deleteNode(file_node*pos){
    if(pos->getLinkNext() == NULL){
        if(pos->getLinkPre() == NULL) {
            // 若判断到这里出现bug
            qDebug() << "WRONG on deltenode in linkedList";
            delete pos;
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
void myLinkedList::insertEnd(file_node* x){
    auto cur = HEAD;
    while(!cur->isEnd()) cur = cur->getLinkNext();
    insertAft(cur,x);
}
