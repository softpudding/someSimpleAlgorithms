//
// Created by 11570 on 2018/4/18.
//

#ifndef AVLTREE_AVLTREE_H
#define AVLTREE_AVLTREE_H

//
// Created by 11570 on 2018/4/11.
//

class Node{
public:
    Node * p;
    Node * left;
    Node * right;
    int h;
    int key;
    Node(int k);
    Node(int k,int height);
};

class AVLTree {
private:
    void Balance(Node * n);
    void InsertHeightFixup(Node * n);
    void LeftRotate(Node * n);
    void RightRotate(Node * n);
    //void RightRotateHeightFixup(Node * n);
    //void LeftRotateHeightFixup(Node * n);
    //void HeightPlus(Node * n);
    //void HeightMinus(Node * n);
public:
    Node * root;
public:
    bool IsAVL(Node * n);
    explicit AVLTree(Node * n):root(n){}
    Node * Search(int k);
    void InorderTreeWalk(Node * n);
    Node * Minimum();
    Node * Maximum();
    Node * Predecessor(Node * n);
    Node * Successor(Node * n);
    Node * Insert (int k);
    bool Delete(int k);
};



#endif //AVLTREE_AVLTREE_H
