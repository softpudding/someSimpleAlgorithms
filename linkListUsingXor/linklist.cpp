//
// Created by 11570 on 2018/4/2.
//
#include "linklist.h"
#include <iostream>
Node * XOR (Node * node1,Node * node2)
{
    unsigned int re=(unsigned int)node1^(unsigned int)node2;
    return (Node *)re;
}
LinkList::LinkList(int n) {
    Node * node=new Node{n, XOR(nullptr, nullptr)};
    head=tail=node;
}
Node * LinkList::Search(int k) {
    Node * cur=head;
    Node * prev= nullptr;
    while(cur->key!=k&&cur!=tail)
    {
        Node * temp=cur;
        cur=XOR(cur->np,prev);//move to next
        prev=temp;
    }
    if(cur->key==k)
        return cur;
    if(tail->key==k)
        return tail;
    else return nullptr;
}
void LinkList::Delete(int k) {
    Node * cur=head;
    Node * prev= nullptr;
    while(cur->key!=k&&cur!=tail)
    {
        Node * temp=cur;
        cur=XOR(cur->np,prev);//move to next
        prev=cur;
    }
    if(cur->key!=k)
    {
        std::cout<<"Delete failed.";
        return ;
    }
    prev->np=XOR(XOR(cur,prev->np),XOR(cur->np,prev));
    XOR(cur->np,prev)->np=XOR(XOR(cur,XOR(cur->np,prev)),prev);
    delete cur;

}
void LinkList::Insert(int k) {
    Node * node=new Node{k, XOR(nullptr,head)};
    head->np=XOR(XOR(head->np, nullptr),node);
    head=node;
}
void LinkList::Show() {
    Node * cur=head;
    Node * prev= nullptr;
    while(cur!=tail)
    {
        std::cout<<cur->key<<' ';
        Node * temp=cur;
        cur=XOR(cur->np,prev);
        prev=temp;
    }
    std::cout<<cur->key;
}