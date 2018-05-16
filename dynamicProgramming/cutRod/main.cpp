#include <iostream>
#include <ctime>
int cutRod (int * p,int n)
{
    if(n==0)
        return 0;
    int result=-1;
    for(int i=1;i<=n;i++)
    {
        int temp=p[i]+cutRod(p,n-i);
        if(temp>result)
            result=temp;
    }
    return result;

}
int memoizedCutRodAux(int * p,int n,int * m)
{
    if(m[n]>=0)
        return m[n];
    int result=-1;
    for(int i=1;i<=n;i++)
    {
        int temp=p[i]+memoizedCutRodAux(p,n-i,m);
        if(temp>result)
        {
            result=temp;
            m[n]=temp;
        }
    }
    return result;

}
int memoizedCutRod(int * p,int n)
{
    int m[n];
    for(int i=0;i<=n;i++)
        m[i]=-1;
    m[0]=0;
    return memoizedCutRodAux(p,n,m);
}
int bottonUpCutRod(int * p, int n)
{
    int m[n+1];
    for(int i=0;i<=n;i++)
        m[i]=-1;
    m[0]=0;
    for(int i=1;i<=n;i++)
        for(int l=1;l<=i;l++)
        {
            int temp=p[l]+m[i-l];
            if(temp>m[i])
                m[i]=temp;
        }
    return m[n];
}

using namespace std;
int main() {
    int p[35]={0,1,5,8,10,13,17,18,22,25,30,31,32,33,34,35,36,37,38,39,40,
    41,42,43,44,45,46,47,48,49,50,52,55,57,60};
    clock_t start=clock();
    //cout<<cutRod(p,34)<<endl;
    clock_t end=clock();
    cout<<double(end-start)/CLOCKS_PER_SEC<<endl;
    start=clock();
    cout<<memoizedCutRod(p,34)<<endl;
    end=clock();
    cout<<double(end-start)/CLOCKS_PER_SEC<<endl;
    start=clock();
    cout<<bottonUpCutRod(p,34)<<endl;
    end=clock();
    cout<<double(end-start)/CLOCKS_PER_SEC<<endl;
    return 0;
}