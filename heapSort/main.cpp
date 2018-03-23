#include <iostream>
#include <cmath>
int parent (int i)
{
    return i/2;
}
int left (int i)
{
    return 2*i;
}
int right (int i)
{
    return 2*i+1;
}
void maxHeapify (int * heap,int i,const int n)//i the index ,n the the number of elements in heap
{
    if(left(i)>n-1)
        return;
    int cur=i;
    int max=heap[i];
    if(heap[left(i)]>max)
    {
        max=heap[left(i)];
        cur=left(i);
    }
    if(heap[right(i)]>max&&right(i)<=n-1)
    {
        max=heap[right(i)];
        cur=right(i);
    }
    if(cur!=i)//exchange value
    {
        heap[i]=heap[i]+heap[cur];
        heap[cur]=heap[i]-heap[cur];
        heap[i]=heap[i]-heap[cur];
        maxHeapify(heap,cur,n);
    }
}
void buildMaxHeap (int * heap, const int n)
{
    for(int i=parent(n);i>=0;i--)
        maxHeapify(heap,i,n);
}
int * heapSort (int * heap,int size)//return a int * where a new sorted array will be stored
{
    buildMaxHeap(heap,size);
    int * dest=new int [size];
    int lastIndex=size-1;//index for the last element in heap
    for(int i=0;i<size;i++)
    {
        dest[i]=heap[0];
        {
            heap[0]=heap[0]+heap[lastIndex];
            heap[lastIndex]=heap[0]-heap[lastIndex];
            heap[0]=heap[0]-heap[lastIndex];
        }
        maxHeapify(heap,0,--lastIndex+1);
    }
    return dest;
}
using std::cin;
using std::cout;
int main() {
    int heap[10]={5,6,7,4,8,9,1,2,3,10};
    int * sorted_heap=heapSort(heap,10);
    for(int i=0;i<10;i++)
        cout<<sorted_heap[i]<<' ';
    return 0;
}