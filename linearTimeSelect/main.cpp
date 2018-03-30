#include <iostream>
void exchange(int * pt1,int * pt2)
{
    if(pt1==pt2)
        return;
    *pt1=*pt1+*pt2;
    *pt2=*pt1-*pt2;
    *pt1=*pt1-*pt2;
}

int insertionSort (int * ar, int low,int high)
{
    for(int i=low+1;i<=high;i++)
    {
        int key=ar[i];
        int t=i-1;
        for(;ar[t]>key&&t>=low;t--)
        {
            ar[t+1]=ar[t];
        }
        ar[t+1]=key;
    }
}
int partition (int * ar, int p,int low, int high)
//p value used to part an array
{
    int edge=low-1;
    for(int i=low;i<=high;i++)
    {
        if(ar[i]<p)
            exchange(ar+i,ar+(++edge));
    }
    for(int i=low;i<=high;i++)
    {
        if(ar[i]==p)
            exchange(ar+i,ar+(++edge));
    }
    return edge;
}

int linearTimeSelect (int * ar, int i, int low, int high,int ct=1)
{
    int * toDeleteNextAr=0;
    int median;
    if(high-low<=4)
    {
        insertionSort(ar,low,high);
        return ar[(low+high)/2];
    }
    else
    {
        int * nextAr = new int [(high-low)/5+1];
        toDeleteNextAr=nextAr;
        for(int i=low;i<=high;i+=5)
        {
            if(high-i<=4)
                insertionSort(ar,i,high);
            else
                insertionSort(ar,i,i+4);
        }
        for(int i=0;i<(high-low)/5+1;i++)
        {
            if(high<=(i+1)*5-1)
                nextAr[i]=ar[low+(i*5+high)/2];
            else
                nextAr[i]=ar[low+i*5+2];
        }
        median=linearTimeSelect(nextAr,i,0,(high-low)/5,ct+1);
        if(ct!=1)
            return median;
    }
    int q=partition(ar,median,low,high);
    //q index so q+1 order
    if(q+1==i)
    {
        delete [] toDeleteNextAr;
        return ar[q];
    }
    else if(q+1<i)
    {
        linearTimeSelect(ar,i,q+1,high);
    }
    else
        linearTimeSelect(ar,i,low,q-1);
}

int main() {
    int ar[10]={10,9,4,3,2,5,6,7,1,8};
    std::cout<<linearTimeSelect(ar,5,0,9);
    return 0;
}