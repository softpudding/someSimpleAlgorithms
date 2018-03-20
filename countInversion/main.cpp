#include <iostream>
#include <ctime>
#include <cstdlib>
void merge (int * ar,int i1,int i2,int i3);
void mergeSort(int * ar,int ib,int ie);
static int ct=0;
const int N=10;
//merge array ar1[i1...i2] and array ar1[i2+1...i3]
int stupidCount(int * ar,int n)
{
    int count=0;
    for(int i=0;i<n;i++)
        for(int ii=i+1;ii<n;ii++)
        {
            if(ar[i]>ar[ii])
                count++;
        }
    return count;
}
int main() {
    srand(time(0));
    int array[N];
    for(int i=0;i<N;i++)
        array[i]=rand()%10;
    for(int i=0;i<N;i++)
    {
        std::cout<<array[i]<<' ';
    }
    int re=stupidCount(array,N);
    std::cout<<std::endl;
    mergeSort(array,0,N-1);
    std::cout<<"Result:";
    for(int i=0;i<N;i++)
    {
        std::cout<<array[i]<<' ';
        if(i%10==9)
            std::cout<<std::endl;
    }
    std::cout<<"Inversions: "<<ct;
    std::cout<<"\nActually: "<<re;
    std::cin.get();
    std::cin.get();
    return 0;
}
void merge (int * ar,int i1,int i2,int i3)
{
    //the number of numbers is i3-i1+1
    int temp1[i2-i1+1],temp2[i3-i2];
    for(int i=0;i<i2-i1+1;i++)
        temp1[i]=ar[i1+i];

    for(int i=0;i<i3-i2;i++)
        temp2[i]=ar[i2+1+i];
    //now temp1 is exactly the same as ar[i1...i2]
    //and temp2 is the same as ar[i2+1,i3]
    int small2=0;
    for(int i=0,key1=0,key2=0;i<i3-i1+1;i++)
    {
        if(key1==i2-i1+1)//temp1 full
            ar[i1+i]=temp2[key2++];
        else if(key2==i3-i2)//temp2 full
        {
            ar[i1+i]=temp1[key1++];
            ct+=small2;
        }
        else if(temp1[key1]<=temp2[key2])
        {
            ar[i1+i]=temp1[key1++];
            ct+=small2;
        }
        else
        {
            ar[i1+i]=temp2[key2++];
            small2++;
        }
    }
}
void mergeSort(int * ar, int ib,int ie)
{
    if(ib<ie)
    {
        int im=(ib+ie)/2;
        mergeSort(ar,ib,im);
        mergeSort(ar,im+1,ie);
        merge(ar,ib,im,ie);
    }
}