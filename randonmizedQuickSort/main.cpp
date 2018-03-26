#include <iostream>
#include <cstdlib>
#include <ctime>
inline void exchange(int * pt1,int * pt2)
{
    if(pt1==pt2)
        return;//这个很重要！
    *pt1=*pt1+*pt2;
    *pt2=*pt1-*pt2;
    *pt1=*pt1-*pt2;
}
int partition (int * ar, int low, int high)
{
    int key=ar[high];
    int low_bound=low-1;
    for(int i=low;i<high;i++)
    {
        if(ar[i]<key)
            exchange(ar+i,ar+(++low_bound));
    }
    exchange(ar+high,ar+(++low_bound));
    return low_bound;
}
int randomizedPartition(int * ar, int low, int high)
{
    srand(time(nullptr));
    int rand_n=low+rand()%(high-low);
    exchange(ar+high,ar+rand_n);
    return partition(ar,low,high);
}
void quickSort (int * ar, int low, int high)
{
    if(low>=high)
        return;
    int mid=randomizedPartition(ar,low,high);
    quickSort(ar,low,mid-1);
    quickSort(ar,mid+1,high);
}
int main() {
    int ar[10]={10,9,2,4,5,6,7,3,1,8};
    quickSort(ar,0,9);
    for(int i=0;i<10;i++)
        std::cout<<ar[i]<<' ';
    std::cout<<std::endl;
    return 0;
}
