//
// Created by 11570 on 2018/5/25.
//

#ifndef BTREE_BTREE_H
#define BTREE_BTREE_H

#include <cstdint>

#define T 2
template <typename type>
class Node
{
public:
    //suppose degree=T,thus numofkeys<=2T-1 numofsons<=2T
    Node * p;
    type keys[2*T-1];
    Node<type> * c[2*T];
    //c is the array of pointers to its sons..or daughters
    bool leaf;//is this a leaf
    int size;//keys in Node thus children should be size+1
    Node(type key=0)
    {
        size=1;
        keys[0]=key;
        for(int i=0;i<2*T;i++)
            c[i]=nullptr;
        leaf=false;
        p= nullptr;
    }
    void SplitNode(int toSplit)//if c[i] is a child with 2*T-1 elements than we gotta split it
    {
        Node<type> * newNode=new Node<type>(c[toSplit]->keys[T]);
        newNode->size=T-1;
        for(int i=0;i<T-1;i++)
            newNode->keys[i]=c[toSplit]->keys[T+i];
        for(int i=0;i<T;i++)
            newNode->c[i]=c[toSplit]->c[i+T];
        newNode->leaf=c[toSplit]->leaf;
        newNode->p=this;
        //newNode 内部问题解决完了
        c[toSplit]->size=T-1;//toSplit内部问题也解决了
        size++;
        for(int i=size;i>toSplit+1;i--)
            c[i]=c[i-1];
        c[toSplit+1]=newNode;
        for(int i=size-1;i>toSplit;i--)
            keys[i]=keys[i-1];
        keys[toSplit]=c[toSplit]->keys[T-1];//toSplit父节点也解决了
    }

};

template <typename type>
class BTree
{
private:
    Node<type> * root;
    void insertNonful(type toInsert,Node<type> * curNode)
    {
        //在保证当前这个节点不满的情况下
        for(int i=0;i<curNode->size;i++)
        {
            if(toInsert<curNode->keys[i])
            {
                if(curNode->leaf)
                {
                    for(int in=curNode->size-1;in>i;in--)
                        curNode->keys[in]=curNode->keys[in-1];
                    curNode->keys[i]=toInsert;
                }
                else
                {
                    if(curNode->c[i]->size==2*T-1)
                    {
                        curNode->SplitNode(i);
                        if(toInsert>curNode->keys[i])
                            insertNonful(toInsert,curNode->c[i+1]);
                        else
                            insertNonful(toInsert,curNode->c[i]);
                    }
                    else
                        insertNonful(toInsert,curNode->c[i]);
                }
            }
            break;

        }

    }
    type predecessor(Node<type> *curNode)//find the right right right..ele in curNode
    {
        if(!curNode->leaf)
        {
            curNode=curNode->c[curNode->size];
        }
        return curNode->keys[curNode->size-1];
    }
    type successor(Node<type> *curNode)
    {
        if(!curNode->leaf)
        {
            curNode=curNode->c[0];
        }
        return curNode->keys[0];
    }
public:


    void insert(type toInsert)
    {
        if(root->size==2*T-1)
        {
            Node<type> * newRoot=new Node<type>(root->keys[T-1]);
            Node<type> * newBranch=new Node<type>(root->keys[T]);
            root->size=T-1;
            newBranch->size=T-1;
            for(int i=0;i<T;i++)
                newBranch->keys[i]=root->keys[T+i];
            for(int i=0;i<T;i++)
                newBranch->c[i]=root->c[T+i];
            newBranch->leaf=false;//newBranch finished
            newRoot->size=1;
            newRoot->leaf=false;
            newRoot->c[0]=root,newRoot->c[1]=newBranch;
            root=newRoot;
            insertNonful(toInsert,root);
        }
        else
            insertNonful(toInsert,root);
    }
    Node<type>* search(type toSearch,Node<type> *curNode)
    {
        for(int i=0;i<curNode->size;i++)
        {
            if(toSearch<=curNode->keys[i])
            {
                if(toSearch==curNode->keys[i])
                    return curNode;
                else
                {
                    if(curNode->leaf)
                        return nullptr;
                    else
                        return search(toSearch,curNode->c[i]);
                }
            }
        }
    }
    void Delete(type key)
    {
        Node<type> * curNode=root;
        int i;
        for(i=0;i<curNode->size&&key>curNode->keys[i];i++);
        {
            if(key<curNode->keys[i])
            {
                if(curNode==root)
                    curNode=curNode->c[i];
                else{
                    if(curNode->c[i]->size>T-1)
                        curNode=curNode->c[i];
                    else
                    {
                        if(i-1>=0&&curNode->c[i-1]->size>T-1)
                        {
                            type temp=curNode->keys[i-1];
                            curNode->keys[i-1]=curNode->c[i-1]->keys[curNode->c[i-1]->size-1];
                            //
                            curNode->c[i]->size++;
                            for(int in=curNode->c[i]->size-1;in>=1;in--)
                                curNode->c[i]->keys[i]=curNode->c[i]->keys[i-1];
                            for(int in=curNode->c[i]->size;in>=1;in--)
                                curNode->c[i]->keys[i]=curNode->c[i]->keys[i-1];
                            curNode->c[i]->keys[0]=temp;
                            curNode->c[i]->c[0]=curNode->c[i-1]->c[curNode->c[i-1]->size];
                            //
                            curNode->c[i-1]->size--;
                        }
                        else if(i+1<curNode->size&&curNode->c[i+1]->size>T-1&&curNode->c[i-1]->size<=T-1)
                        {
                            type temp=curNode->keys[i];
                            curNode->keys[i]=curNode->c[i+1]->keys[0];
                            curNode->c[i]->c[curNode->c[i]->size+1]=curNode->c[i+1]->c[0];
                            curNode->c[i]->keys[curNode->c[i]->size]=temp;
                            for(int in=0;in<curNode->c[in+1]->size;in++)
                                curNode->c[in+1]->keys[in]=curNode->c[in+1]->keys[in+1];
                            for(int in=0;i<curNode->c[in+1]->size+1;in++)
                                curNode->c[in+1]->c[in]=curNode->c[in+1]->c[in+1];
                            //
                            //
                            curNode->c[i+1]->size--;
                        }
                        else //both c[i-1]->size and c[i+1]->size are T-1
                        {
                            if(i>0)
                            {
                                curNode->c[i-1]->size++;
                                curNode->c[i-1]->keys[T-1]=curNode->keys[i-1];
                                for(int in=T;in<2*T-1;in++)
                                {
                                    curNode->c[i-1]->keys[in]=curNode->c[i]->keys[in-T];
                                }
                                for(int in=T;in<2*T;in++)
                                {
                                    curNode->c[i-1]->c[in]=curNode->c[i]->c[in-T];
                                }//two nodes have concentrated in one
                                for(int in=i;in<curNode->size;in++)
                                {
                                    curNode->c[in]=curNode->c[in+1];
                                }
                                for(int in=i;in<curNode->size-1;in++)
                                {
                                    curNode->keys[in]=curNode->keys[in+1];
                                }
                                curNode->size--;
                            }
                            else if(i==0)
                            {
                                curNode->c[i]->size++;
                                curNode->c[i]->keys[T-1]=curNode->keys[i];
                                for(int in=T;in<2*T-1;in++)
                                {
                                    curNode->c[i]->keys[in]=curNode->c[i+1]->keys[in-T];
                                }
                                for(int in=T;in<2*T;in++)
                                {
                                    curNode->c[i]->c[in]=curNode->c[i+1]->c[in-T];
                                }//two nodes have concentrated in one
                                for(int in=i+1;in<curNode->size;in++)
                                {
                                    curNode->c[in]=curNode->c[in+1];
                                }
                                for(int in=i;in<curNode->size-1;in++)
                                {
                                    curNode->keys[in]=curNode->keys[in+1];
                                }
                                curNode->size--;
                            }
                        }
                    }
                }
            }
            else if(key==curNode->keys[i])
            {
                if(curNode->leaf)//if curNode a leaf just delete it~
                {
                    for(int in=i;in<curNode->size-1;in++)
                        curNode->keys[in]=curNode->keys[in+1];
                    curNode->size--;
                }
                else
                {
                    if(curNode->c[i]->size>T-1)
                    {
                        type temp=predecessor(curNode->c[i]);
                        Delete(temp);
                        curNode->keys[i]=temp;
                    }
                    else if(curNode->c[i+1]->size>T-1)
                    {
                        type temp=successor(curNode->c[i+1]);
                        Delete(temp);
                        curNode->keys[i]=temp;
                    }
                    else//time to concentrate c[i] and c[i+1] in c[i]
                    {
                        type temp=curNode->keys[i];
                        curNode->c[i]->size++;
                        curNode->c[i]->keys[curNode->c[i]->size-1]=curNode->keys[i];
                        for(int in=T;in<2*T-1;in++)
                            curNode->c[i]->keys[in]=curNode->c[i+1]->keys[in-T];
                        for(int in=T;in<2*T;in++)
                            curNode->c[i]->c[in]=curNode->c[i+1]->c[in-T];
                        for(int in=i;in<curNode->size-1;in++)
                            curNode->keys[in]=curNode->keys[in+1];
                        for(int in=i+1;in<curNode->size;in++)
                            curNode->c[i]=curNode->c[i+1];
                        curNode->size--;
                        Delete(temp);
                    }
                }
            }
        }


    }
    BTree(Node<type> * node)
    {
        root=node;
        root->leaf=true;
    }
};


#endif //BTREE_BTREE_H
