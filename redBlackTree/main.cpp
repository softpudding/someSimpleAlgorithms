#include <iostream>
#include "rbtree.h"
int main() {
    Node * root=new Node(99);
    RBTree tree(root);
    tree.InorderTreeWalk(tree.root);
    std::cout<<std::endl;

    tree.Insert(77);
    tree.Insert(75);
    tree.Insert(97);
    tree.Insert(101);
    tree.Insert(120);
    tree.Insert(116);
    tree.InorderTreeWalk(tree.root);
    std::cout<<std::endl;

    tree.Delete(97);
    tree.InorderTreeWalk(tree.root);
    std::cout<<std::endl;

    tree.Delete(99);
    tree.InorderTreeWalk(tree.root);
    std::cout<<std::endl;

    std::cout<<tree.Maximum()->key<<' '<<tree.Minimum()->key<<std::endl;

    
    return 0;
}