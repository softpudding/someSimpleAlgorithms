#include <iostream>
#include "avltree.h"
int main() {
    Node root(5);
    AVLTree tree(&root);
    tree.InorderTreeWalk(tree.root);
    std::cout<<std::endl;
    tree.Insert(6);
    tree.Insert(2);
    tree.Insert(4);
    tree.Insert(1);
    tree.Insert(12);
    tree.Insert(13);
    tree.Insert(14);
    tree.InorderTreeWalk(tree.root);
    std::cout<<std::endl;
    std::cout<<"Above tree is"<<(tree.IsAVL(tree.root)? "":" not")<<" an AVL tree.\n";
    tree.Insert(11);
    tree.InorderTreeWalk(tree.root);
    std::cout<<std::endl;
    tree.Delete(4);
    tree.Delete(1);
    tree.InorderTreeWalk(tree.root);
    std::cout<<std::endl;
    std::cout<<"Above tree is"<<(tree.IsAVL(tree.root)? "":" not")<<" an AVL tree.\n";
    std::cout<<"Maximum: "<<tree.Maximum()->key<<std::endl;
    std::cout<<"Minimum: "<<tree.Minimum()->key<<std::endl;
    std::cout<<"Search for 6: "<<tree.Search(6)->key<<std::endl;
    std::cout<<"Successor of 2: "<<tree.Successor(tree.Search(2))->key<<std::endl;
    std::cout<<"Predecessor of 2: "<<tree.Predecessor(tree.Search(2))->key<<std::endl;

}