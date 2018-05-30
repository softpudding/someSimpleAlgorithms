#include <iostream>
#include "fibheap.h"
int main() {
    Fibheap<int> heap;
    heap.Insert(10);
    heap.Insert(11);
    heap.Insert(12);
    heap.Insert(1);
    heap.Insert(5);
    heap.Insert(19);
    Fibheap<int> ano_heap;
    ano_heap.Insert(-1);
    ano_heap.Insert(100);
    Fibheap<int> sum_of_heap;
    sum_of_heap.Union(heap,ano_heap);
    std::cout<<sum_of_heap.ExtractMin()->key<<std::endl;
    std::cout<<sum_of_heap.ExtractMin()->key<<std::endl;
    return 0;
}