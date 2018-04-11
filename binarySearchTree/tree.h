//
// Created by 11570 on 2018/4/11.
//

#ifndef BINARYSEARCHTREE_TREE_H
#define BINARYSEARCHTREE_TREE_H
class Node{
public:
    Node * p;
    Node * left;
    Node * right;
    int key;
    Node(int k):p(nullptr),left(nullptr),right(nullptr),key(k){}
};
class Tree {
public:
    Node * root;
public:
    Tree(Node * n):root(n){}
    Node * Search(int k);
    void InorderTreeWalk(Node * n);
    Node * Minimum();
    Node * Maximum();
    Node * Predecessor(Node * n);
    Node * Successor(Node * n);
    Node * Insert (int k);
    bool Delete(int k);
};

#endif //BINARYSEARCHTREE_TREE_H
