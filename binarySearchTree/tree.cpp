//
// Created by 11570 on 2018/4/11.
//
#include <iostream>
#include "tree.h"
void TransPlant (Node * n1,Node * n2)//take n2 to replace the place of n1
{
    if(n2== nullptr)
    {
        if(n1==n1->p->right)
            n1->p->right=n2;
        else if(n1==n1->p->left)
            n1->p->left=n2;
        return ;
    }
    if(n1->p== nullptr)
        n1=n2;
    if(n1==n1->p->right)
        n1->p->right=n2;
    else if(n1==n1->p->left)
        n1->p->left=n2;
    n2->p=n1->p;
}
Node * Tree::Search (int k)
{
    Node * cur=root;
    while(cur->key!=k&&cur!= nullptr)
    {
        if(cur->key<k)
            cur=cur->right;
        else cur=cur->left;
    }
    if(cur->key==k)
        return cur;
    else return nullptr;
}
void Tree::InorderTreeWalk(Node * n)
{
    if(n== nullptr)
        return ;
    InorderTreeWalk(n->left);
    std::cout<<n->key<<' ';
    InorderTreeWalk(n->right);
}
Node * Tree::Minimum()
{
    if(root->left== nullptr)
        return root;
    Node * cur=root;
    while(cur->left!= nullptr)
        cur=cur->left;
    return cur;
}
Node * Tree::Maximum()
{
    if(root->right== nullptr)
        return root;
    Node * cur=root;
    while(cur->right!= nullptr)
        cur=cur->right;
    return cur;
}
Node * Tree::Predecessor(Node * n)
{
    if(n->left!= nullptr)
    {
        return Tree(n->left).Maximum();
    }
    else if(n->p!= nullptr)
        return n->p;
    else return nullptr;
}
Node * Tree::Successor(Node *n)
{
    if(n->right!= nullptr)
    {
        return Tree(n->right).Minimum();
    }
    else if(n->p!= nullptr)
        return n->p;
    else return nullptr;
}
Node * Tree::Insert(int k)
{
    Node * cur=root;
    Node * prev= nullptr;
    while(cur!= nullptr)
    {
        prev=cur;
        if(k<cur->key)
            cur=cur->left;
        else if(k>cur->key)
            cur=cur->right;
        else
        {
            std::cerr<<k<<" already in tree.\n";
            return nullptr;
        }
    }
    Node * toInsert=new Node(k);
    toInsert->p=prev;
    if(k<prev->key)
        prev->left=toInsert;
    else
        prev->right=toInsert;
}
bool Tree::Delete(int k)
{
    Node * toDelete=Search(k);
    if(toDelete== nullptr)
    {
        std::cerr<<"Delete failed.\n";
        return false;
    }
    if(toDelete->left== nullptr)
        TransPlant(toDelete,toDelete->right);
    else if(toDelete->right==nullptr)
        TransPlant(toDelete,toDelete->left);
    else
    {
        Node * toReplace=Tree(toDelete->right).Maximum();
        if(toReplace==toDelete->right)
        {
            toReplace->left=toDelete->left;
            toDelete->left->p=toReplace;
            TransPlant(toDelete,toReplace);
        }
        else
        {
            TransPlant(toDelete,toReplace);
            toReplace->left=toDelete->left;
            toReplace->right=toDelete->right;
            toDelete->right->p=toReplace;
            toDelete->left->p=toReplace;
        }
    }


}
