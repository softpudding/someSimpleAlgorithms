//
// Created by 11570 on 2018/4/2.
//

#ifndef LINKLISTUSINGXOR_LINKLIST_H
#define LINKLISTUSINGXOR_LINKLIST_H

typedef struct Node{
    int key;
    Node * np;
    //np=next^prev
}Node;
class LinkList{
private:
    Node * head;
    Node * tail;
public:
    LinkList(int n);
    LinkList(){
        head=tail= nullptr;
    }
    Node * Search(int k);
    void Insert (int k);
    void Delete (int k);
    void Show();
};

#endif //LINKLISTUSINGXOR_LINKLIST_H
