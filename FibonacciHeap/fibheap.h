//
// Created by 11570 on 2018/5/29.
//
#include <iostream>
#ifndef FIBONACCIHEAP_FIBHEAP_H
#define FIBONACCIHEAP_FIBHEAP_H
template<typename T>
class Node{
public:
    T key;
    int degree;
    Node<T> *left,*right,*parent,*childList;
    bool mark;
    explicit Node(T k)
    {
        key=k;
        degree=0;
        left=right=this;
        parent=childList= nullptr;
        mark=false;
    }

};
template<typename T>
class Fibheap{
private:
    int n;
    Node<T> * rootList;
    Node<T> * min;
    void Consolidate();
    void Link(Node<T>* x,Node<T>* y);
    void Cut(Node<T> * x);
    void CascadingCut(Node<T> * x);
public:
    Fibheap(){
        rootList=min= nullptr;
         n=0;
    }
    void Insert(T k);
    void Union(Fibheap<T> heap1,Fibheap<T> heap2);
    Node<T>* Minimum(){
        return min;
    }
    Node<T>* ExtractMin();
    void DecreaceKey(Node<T> * node,T k);
};
template<typename T>
void Fibheap<T>::Insert(T k) {
    if(rootList== nullptr)
    {
        Node<T> * kNode=new Node<T>(k);
        rootList=min=kNode;
    }
    else
    {
        Node<T> * kNode=new Node<T>(k);
        rootList->right->left=kNode;
        kNode->right=rootList->right;
        rootList->right=kNode;
        kNode->left=rootList;
        if(kNode->key<min->key)
            min=kNode;
    }
    n++;

}
template<typename T>
void Fibheap<T>::Link(Node<T> *x, Node<T> *y) {
    y->left->right=y->right;
    y->right->left=y->left;
    //erase y
    y->parent=x;
    y->left=x->childList;
    y->right=x->childList->right;
    x->childList->right->left=y;
    x->childList->right=y;
    //link y with x's childList
    y->mark=false;
    x->degree++;

}
template<typename T>
void Fibheap<T>::Consolidate()
{
    Node<T> * A[n];
    for(int i=0;i<n;i++)
        A[i]= nullptr;
    Node<T> * cur=rootList,*begin=rootList;
    do{
        while(A[cur->degree]!= nullptr)
        {
            Node<T> * x=cur;
            Node<T> * y=A[cur->degree];
            if(x->key<y->key)
                Link(x,y);
            else Link(y,x);
            A[cur->degree-1]= nullptr;
            A[cur->degree]=cur;
        }
        cur=cur->right;

    }while(cur!=begin);
    min=rootList=nullptr;
    for(int i=0;i<n;i++){
        if(A[i]!= nullptr)
        {
            A[i]->parent= nullptr;
            if(rootList==nullptr)
                rootList=min=A[i];
            else{
                A[i]->left=rootList->left;
                A[i]->right=rootList;
                rootList->left->right=A[i];
                rootList->left=A[i];
                if(A[i]->key<min->key)
                    min=A[i];
            }

        }
    }

}
template<typename T>
void Fibheap<T>::Union(Fibheap<T> heap1, Fibheap<T> heap2) {
    if(heap1.min->key<heap2.min->key)
        min=heap1.min;
    else min=heap2.min;
    rootList=heap1.rootList;
    rootList->right->left=heap2.rootList->left;
    heap2.rootList->left->right=rootList->right;
    rootList->right=heap2.rootList;
    heap2.rootList->left=rootList;
    n=heap1.n+heap2.n;
}
template<typename T>
Node<T>* Fibheap<T>::ExtractMin()
{
    if(min==nullptr)
        return nullptr;
    if(min->childList==nullptr)
    {
        if(min->right!= nullptr)
        {
            auto result=min;
            min->left->right=min->right;
            min->right->left=min->left;//erase min
            Node<T> *begin=min->right,*cur=min->right;
            cur=cur->right;
            min=cur;
            while(cur!=begin)
            {
                if(cur->key<min->key)
                    min=cur;
                cur=cur->right;
            }
            n--;
            return result;
        }
        else {
            rootList= nullptr;
            Node<T> *temp=min;
            min= nullptr;
            return temp;
        }
    }
    else{
        Node<T>* result=min;
        min->left->right=min->right;
        min->right->left=min->left;
        min=min->right;
        Node<T> *cur=min->childList,*begin=min->childList;
        while(cur!=begin)
        {
            cur->parent=nullptr;

            cur->right=rootList;
            cur->left=rootList->left;
            rootList->left->right=cur;
            rootList->left=cur;

            cur=cur->right;
        }
        Consolidate();
        return result;
    }

}
template<typename T>
void Fibheap<T>::Cut(Node<T> *x) {
    Node<T> * y=x->parent;
    x->left->right=x->right;
    x->right->left=x->left;
    //erase from y's childList
    y->degree--;
    x->mark=false;
    x->parent=nullptr;

    rootList->left->right=x;
    rootList->left=x;
    x->left=rootList->left;
    x->right=rootList->right;
    //add to tree rootList


}
template<typename T>
void Fibheap<T>::CascadingCut(Node<T> *x)
{
    Node<T> * y=x->parent;
    if(x->mark==false)
        x->mark=true;
    else
    {
        Cut(x);
        CascadingCut(y);
    }
}
template<typename T>
void Fibheap<T>::DecreaceKey(Node<T> *node, T k) {
    if(k>=node->key)
    {
        std::cerr<<"New key is greater to the original key.";
        return;
    }
    node->key=k;
    if(node->parent!= nullptr&&node->key<node->parent->key)
    {
        Cut(node);
        CascadingCut(node->parent);
    }
    if(node->key<min->key)
        min=node;
}
#endif //FIBONACCIHEAP_FIBHEAP_H
