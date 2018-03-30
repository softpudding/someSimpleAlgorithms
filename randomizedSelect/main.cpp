#include <iostream>
#include <cstdlib>
#include <ctime>
void exchange (int * pt1,int * pt2)
{
    if(pt1==pt2)
        return ;
    else
    {
        *pt1=*pt1+*pt2;
        *pt2=*pt1-*pt2;
        *pt1=*pt1-*pt2;
    }
}
int randomizedPartition (int * ar, int low, int high)
{
    int rand_n=low+rand()%(high-low)+1;
    exchange(ar+high,ar+rand_n);
    int edge=low-1;
    for(int i=0;i<high;i++)
    {
        if(ar[i]<ar[high])
            exchange(ar+i,ar+(++edge));
    }
    exchange(ar+high,ar+(++edge));
    return edge;
}
int randomizedSelect (int * ar, int i,int low, int high)
{
    if(low==high)
        return ar[i];
    int q=randomizedPartition(ar,low,high);
    if(q+1==i)
        return ar[q];
    else if(q+1<i)
        return randomizedSelect(ar,i,q+1,high);
    else
        return randomizedSelect(ar,i,low,q-1);
}
int main() {
    int ar[10]={9,10,8,7,5,16,4,21,3,1};
    int no2=randomizedSelect(ar,2,0,9);
    std::cout<<no2;
    return 0;
}