#include <iostream>
#include "linklist.h"
int main() {
    LinkList list(1);
    list.Insert(2);
    list.Insert(3);
    list.Insert(4);
    if(list.Search(1)== nullptr)
        std::cout<<"Holy Shit!";
    list.Show();
}