//
// Created by 11570 on 2018/4/16.
//
#include "rbtree.h"
#include <iostream>
Node nil(-1);
Node * NIL=&nil;
Node::Node(int k):
key(k)
{
    p=left=right=NIL;
    color=BLACK;
}
RBTree::RBTree(Node * n):root(n){
        n->p=n->right=n->left=NIL;
}
Node * RBTree::Search(int k)
{
    Node * cur=root;
    while(cur->key!=k)
    {
        if(cur->key<k&&cur->right!=NIL)
            cur=cur->right;
        else if (cur->key>k&&cur->left!=NIL)
            cur=cur->left;
        else
            return NIL;
    }
    return cur;

}
void RBTree::InorderTreeWalk(Node * n)
{
    if(n==NIL)
        return ;
    InorderTreeWalk(n->left);
    std::cout<<n->key<<' ';
    InorderTreeWalk(n->right);
}
Node * RBTree::Minimum()
{
    Node * cur=root;
    while(cur->left!=NIL)
        cur=cur->left;
    return cur;
}
Node * RBTree::Maximum()
{
    Node * cur=root;
    while(cur->right!=NIL)
        cur=cur->right;
    return cur;
}
Node * RBTree::Predecessor(Node *n)
{
    Node * cur=n;
    if(n->left!=NIL)
    {
        return RBTree(n->left).Maximum();
    }
    else if(n->p!=NIL)
        return n->p;
    else return NIL;
}
Node * RBTree::Successor(Node * n)
{
    Node * cur=n;
    if(n->right!=NIL)
    {
        return RBTree(n->right).Minimum();
    }
    else if (n->p!=NIL)
        return n->p;
    else return NIL;
}
void RBTree::TransPlant(Node * n1,Node * n2)
{
    n2->p=n1->p;
    if(n1==n1->p->left)
        n1->p->left=n2;
    else if (n1==n1->p->right)
        n1->p->right=n2;
    else root=n2;
}
void RBTree::LeftRotate(Node * n)
{
    if(n==root)
        root=n->left;
    Node * y=n->right;
    n->right=y->left;
    y->left->p=n;
    y->p=n->p;
    y->left=n;
    if(n==n->p->right)
        n->p->right=y;
    else
        n->p->left=y;
    n->p=y;
}
void RBTree::RightRotate(Node * n)
{
    if(n==root)
        root=n->left;
    Node * y=n->left;
    n->left=y->right;
    y->right->p=n;
    y->p=n->p;
    y->right=n;
    if(n==n->p->right)
        n->p->right=y;
    else
        n->p->left=y;
    n->p=y;
}
Node * RBTree::Insert(int k)
{
    Node * cur=root;
    Node * prev=root;
    while(cur!= NIL)
    {
        prev=cur;
        if(k<cur->key)
            cur=cur->left;
        else if (k>cur->key)
            cur=cur->right;
        else
        {
            std::cerr<<std::endl<<k<<" already in RBTree.\n";
            return NIL;
        }
    }
    if(k<prev->key)
    {
        prev->left=new Node(k);
        prev->left->p=prev;
        prev->left->left=prev->left->right=NIL;
        prev->left->color=Node::RED;
        InsertFixup(prev->left);
        return prev->left;
    }
    else if(k>prev->key)
    {
        prev->right=new Node(k);
        prev->right->p=prev;
        prev->right->left=prev->right->right=NIL;
        prev->right->color=Node::RED;
        InsertFixup(prev->right);
        return prev->right;
    }


}
void RBTree::InsertFixup(Node * n)
{
    while(n->p->color==Node::RED)
    {
        if(n->p==n->p->p->left)
        {
            Node * uncle=n->p->p->right;
            if(uncle->color==Node::RED)
            {
                n->p->color=uncle->color=Node::BLACK;
                n->p->p->color=Node::RED;
                n=n->p->p;
            }
            else if(uncle->color==Node::BLACK&&n==n->p->right)
            {
                n=n->p;
                LeftRotate(n);
            }
            else if(uncle->color==Node::BLACK&&n==n->p->left)
            {
                n->p->color=Node::BLACK;
                n->p->p->color=Node::RED;
                RightRotate(n->p->p);
            }
        }
        else if (n->p==n->p->p->right)
        {
            Node * uncle=n->p->p->left;
            if(uncle->color==Node::RED)
            {
                n->p->color=uncle->color=Node::BLACK;
                n->p->p->color=Node::RED;
                n=n->p->p;
            }
            else if(uncle->color==Node::BLACK&&n==n->p->left)
            {
                n=n->p;
                RightRotate(n);
            }
            else if(uncle->color==Node::BLACK&&n==n->p->right)
            {
                n->p->color=Node::BLACK;
                n->p->p->color=Node::RED;
                LeftRotate(n->p->p);
            }
        }
    }
    root->color=Node::BLACK;
}
bool RBTree::Delete(int k)
{
    Node * toDelete=Search(k);
    Node * toReplace=toDelete;
    Node::c original_color=toDelete->color;//of toReplace
    Node * tRTR;
    toReplace->color=toDelete->color;
    if(toDelete->left==NIL)
    {
        tRTR=toDelete->right;
        TransPlant(toDelete,toDelete->right);
    }
    else if(toDelete->right==NIL)
    {
        tRTR=toDelete->left;
        TransPlant(toDelete,toDelete->left);
    }
    else
    {
        toReplace=Successor(toDelete);
        original_color=toReplace->color;
        tRTR=toReplace->right;
        if(toReplace->p==toDelete)
        {
            TransPlant(toDelete,toReplace);
            toReplace->left=toDelete->left;
            toDelete->left->p=toReplace;
            toReplace->color=toDelete->color;
        }
        else
        {
            TransPlant(toReplace,toReplace->right);
            toReplace->left=toDelete->left;
            toDelete->left->p=toReplace;
            toReplace->right=toDelete->right;
            toDelete->right->p=toReplace;
            TransPlant(toDelete,toReplace);
        }
    }
    if(original_color==Node::BLACK)
        DeleteFixup(tRTR);
}
void RBTree::DeleteFixup(Node *n) {
    while (n->color == Node::BLACK && n != root) {
        if (n == n->p->left) {
            Node *brother = n->p->right;
            {
                if (brother->color == Node::RED) {
                    n->p->color = Node::RED;
                    brother->color = Node::BLACK;
                    LeftRotate(n->p);
                    brother = n->p->right;
                } else if (brother->left->color == Node::BLACK && brother->right->color == Node::BLACK) {
                    n->p->color = Node::RED;
                    n = n->p;
                } else if (brother->color == Node::BLACK && brother->left->color == Node::RED) {
                    brother->color = Node::RED;
                    brother->left->color = Node::BLACK;
                    RightRotate(brother);
                } else if (brother->right->color == Node::RED) {
                    brother->right->color = Node::BLACK;
                    Node::c temp = n->p->color;
                    brother->color = temp;
                    n->p->color = Node::BLACK;
                    LeftRotate(n->p);
                    n = root;
                }
            }
            if (n == n->p->right) {
                Node *brother = n->p->left;
                {
                    if (brother->color == Node::RED) {
                        n->p->color = Node::RED;
                        brother->color = Node::BLACK;
                        RightRotate(n->p);
                        brother = n->p->left;
                    } else if (brother->left->color == Node::BLACK && brother->right->color == Node::BLACK) {
                        n->p->color = Node::RED;
                        n = n->p;
                    } else if (brother->color == Node::BLACK && brother->right->color == Node::RED) {
                        brother->color = Node::RED;
                        brother->right->color = Node::BLACK;
                        LeftRotate(brother);
                    } else if (brother->left->color == Node::RED) {
                        brother->left->color = Node::BLACK;
                        Node::c temp = n->p->color;
                        brother->color = temp;
                        n->p->color = Node::BLACK;
                        RightRotate(n->p);
                        n = root;
                    }
                }
            }
        }

    }
    n->color = Node::BLACK;
}