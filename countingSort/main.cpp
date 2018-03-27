#include <iostream>
void countingSort (unsigned int * ar, int low, int high)
{
    int c_size=0;
    for(int i=low;i<=high;i++)
    {
        ar[i]>c_size?c_size=ar[i]:0;
    }
    unsigned int C[c_size+1]={0};
    unsigned int B[high-low+1];
    for(int i=low;i<=high;i++)
    {
        C[ar[i]]++;
    }
    for(int i=1;i<=c_size;i++)
    {
        C[i]+=C[i-1];
    }
    for(int i=high;i>=low;i--)
    {
        B[--C[ar[i]]]=ar[i];
    }
    for(int i=low;i<high;i++)
        ar[i]=B[i];
}

int main() {
    unsigned int ar[10]={2,3,5,1,4,6,8,6,9,10};
    countingSort(ar,0,9);
    for(int i=0;i<10;i++)
        std::cout<<ar[i]<<' ';
    std::cout<<'\n';
    return 0;
}