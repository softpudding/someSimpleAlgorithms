#include <iostream>
#include <cstdlib>
#include <ctime>
typedef struct{
    int low;
    int high;
} two_index;
inline bool isNotSame (int * ar,int low,int high)
{
    for(int i=low+1;i<=high;i++)
    {
        if(ar[i]!=ar[low])
            return true;
    }
    return false;
}
inline void exchange (int * pt1,int * pt2)
{
    if(pt1==pt2)
        return;
    else
    {
        *pt1=*pt1+*pt2;;
        *pt2=*pt1-*pt2;
        *pt1=*pt1-*pt2;
    }
}
two_index partition_1 (int * ar,int low,int high)
{
    int key=ar[high];
    two_index re{low-1,high+1};
    for(int i=low;i<high;i++)
    {
        if(ar[i]<key)
            exchange(ar+i,ar+(++re.low));
    }
    exchange(ar+high,ar+(++re.low));//key in re.low right now
    for(int i=high;i>re.low;i--)
    {
        if(ar[i]>key)
            exchange(ar+i,ar+(--re.high));
    }
    re.high--;
    return re;

}
two_index randomizedPartition_1 (int * ar,int low, int high)
{
    int rand_n=low+rand()%(high-low+1);
    exchange(ar+rand_n,ar+high);
    return partition_1(ar,low,high);
}
void quickSort_1(int * ar,int low,int high)
{
    if(isNotSame(ar,low,high))
    {
        two_index indexes=randomizedPartition_1(ar,low,high);
        quickSort_1(ar,low,indexes.low-1);
        quickSort_1(ar,indexes.high+1,high);
    }
}
int main() {
    int ar[16]={1,1,10,9,9,2,8,8,9,4,5,6,7,3,1,8};
    quickSort_1(ar,0,15);
    for(int i=0;i<16;i++)
        std::cout<<ar[i]<<' ';
    std::cout<<std::endl;
    return 0;
}


