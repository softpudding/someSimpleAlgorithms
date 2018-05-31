#include <iostream>
#include "vebtree.h"

int main() {
    vEB vebtree(16);

    vebtree.vEBInsert(0);
    vebtree.vEBInsert(1);
    vebtree.vEBInsert(2);
    vebtree.vEBInsert(3);
    vebtree.vEBInsert(4);
    vebtree.vEBInsert(5);
    vebtree.vEBInsert(6);
    vebtree.vEBInsert(7);
    vebtree.vEBInsert(8);
    vebtree.vEBInsert(9);
    vebtree.vEBInsert(10);
    vebtree.vEBInsert(11);
    vebtree.vEBInsert(12);
    vebtree.vEBInsert(13);
    vebtree.vEBInsert(14);
    vebtree.vEBInsert(15);

    for(int i=0;i<15;i++)
        std::cout<<"Successor of "<<i<<" is "<<vebtree.vEBSuccessor(i)<<std::endl;

    for(int i=1;i<16;i++)
        std::cout<<"Predecessor of "<<i<<" is "<<vebtree.vEBPredecessor(i)<<std::endl;

    std::cout<<7<<(vebtree.vEBMember(7)? " is ":" isn't ")<<"in the tree."<<std::endl;

    vebtree.vEBDelete(7);

    std::cout<<7<<(vebtree.vEBMember(7)? " is ":" isn't ")<<"in the tree."<<std::endl;


    return 0;
}