#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
class subArray
{
public:
    int * ar;
    int low;
    int high;
    int sum;
};
subArray & stupidMethod (subArray & subarray)
{
    int temp_sum=subarray.ar[subarray.low];
    int sum=0;
    for(int i=subarray.low;i<subarray.high;i++)
    {
        temp_sum=subarray.ar[i];
        if(temp_sum>sum)
            sum=temp_sum;
        for(int j=i+1;j<=subarray.high;j++)
        {
            temp_sum+=subarray.ar[j];
            if(temp_sum>sum)
                sum=temp_sum;
        }
    }
    subarray.sum=sum;
    return subarray;
}

subArray & findMaxCrossingSubarray(subArray & subarray)
{

    int mid=(subarray.low+subarray.high)/2;
    int temp_sum=subarray.ar[mid];
    int sum=temp_sum;
    int lower_bound=subarray.low,upper_bound=subarray.high;
    for(int i=mid-1;i>=lower_bound;i--)
    {
        temp_sum+=subarray.ar[i];
        if(temp_sum>sum)
        {
            sum=temp_sum;
            subarray.low=i;
        }
    }//left-side
    temp_sum=sum;
    for(int i=mid+1;i<=upper_bound;i++)
    {
        temp_sum+=subarray.ar[i];
        if(temp_sum>sum)
        {
            sum=temp_sum;
            subarray.high=i;
        }
    }
    subarray.sum=sum;
    //right-side
    return subarray;

}
subArray findMaxSubarray (subArray subarray)
{
    if(subarray.low==subarray.high)
    {
        subarray.sum=subarray.ar[subarray.low];
        return subarray;
    }
    else
    {
        int mid=(subarray.low+subarray.high)/2;
        subArray left_sub({subarray.ar,subarray.low,mid,0}),mid_sub({subarray.ar,subarray.low,subarray.high,0}),right_sub({subarray.ar,mid+1,subarray.high,0});
        {
            left_sub=findMaxSubarray(left_sub);
            right_sub=findMaxSubarray(right_sub);
            mid_sub=findMaxCrossingSubarray(mid_sub);
        }
        if(left_sub.sum>=right_sub.sum&&left_sub.sum>=mid_sub.sum)
            return left_sub;
        else if(right_sub.sum>=left_sub.sum&&right_sub.sum>=mid_sub.sum)
            return right_sub;
        else return mid_sub;
    }
}
int main ()
{
    int array[100];
    srand(time(nullptr));
    for(int i=0;i<100;i++)
    {
        array[i]=rand()%100;
        if(rand()%100>50)
            array[i]*=-1;
    }
    //max=47
    subArray ar1={array,0,99,0};
    subArray ar2=ar1;
    ar1=findMaxSubarray(ar1);
    std::cout<<"Max sum:"<<ar1.sum;
    ar2=stupidMethod(ar2);
    std::cout<<"\nMax sum using stupidMethod:"<<ar2.sum;
    return 0;
}
