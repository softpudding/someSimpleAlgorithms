#include <iostream>
template <typename T>
T insertionSort (T * ,int );
template <typename T>
void showArray (T *, int);
int main ()
{
    int ar[10]={10,2,3,4,1,7,8,9,6,5};
    insertionSort(ar,10);
    showArray(ar,10);
    return 0;
}
template  <typename T>
T insertionSort (T * ar, int n)
{
    for(int i=1;i<n;i++)
    {
        T key=ar[i];
        int t=i-1;
        for(;ar[t]>key&&t>=0;t--)
        {
            ar[t+1]=ar[t];
        }
        ar[t+1]=key;
    }
}
template <typename T>
void showArray (T * ar, int n)
{
    for(int i=0;i<n;i++)
    {
        std::cout<<ar[i]<<" ";
        if(i%5==4)
            std::cout<<std::endl;
    }
    if(n%5!=4)
        std::cout<<std::endl;
}
