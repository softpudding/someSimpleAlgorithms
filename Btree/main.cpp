#include <iostream>
#include "btree.h"
int main() {
    Node<int> node(1);
    BTree<int> bTree(&node);
    bTree.insert(2);
    bTree.insert(0);
    bTree.insert(4);
    bTree.insert(3);
    bTree.Delete(3);
    return 0;
}