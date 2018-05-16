#include <iostream>
int LCS (int * x, int * y,int **table)
{
    //table[i][j]--->...x[i-1],...y[j-1]
    for(int i=1;i<=10;i++)
        for(int j=1;j<=10;j++)
        {
            if(x[i-1]==y[j-1])
                table[i][j]=table[i-1][j-1]+1;
            else if(table[i-1][j]>=table[i][j-1])
                table[i][j]=table[i-1][j];
            else if(table[i-1][j]<table[i][j-1])
                table[i][j]=table[i][j-1];
        }
    return table[10][10];
}
void showArray(int * x,int * y,int ** table)
{
    for(int i=10,j=10;i>0&&j>0;)
    {
        if(table[i][j]==table[i-1][j-1]+1&&x[i-1]==y[j-1])
        {
            i--,j--;
            std::cout<<x[i]<<' ';
        }
        else if(table[i][j]==table[i-1][j])
        {
            i--;
        }
        else{
            j--;
        }
    }
}
//another solution which only uses two array of 10 ints
int LCSV2(int * x,int * y,int * prev,int *cur)
{
    for(int i=1;i<=10;i++)
    {
        for(int j=1;j<=10;j++)
        {
            if(x[i]==y[j])
                cur[j]=prev[j-1]+1;
            else if(cur[j-1]>=prev[j])
                cur[j]=cur[j-1];
            else if(cur[j-1]<prev[j])
                cur[j]=prev[j];
        }
        int * temp;
        temp=cur;
        cur=prev;
        prev=temp;
    }
    return prev[10];
}
int main() {
    using namespace std;
    int ** c=(int **)malloc(sizeof(int *)*11);
    for(int i=0;i<11;i++)
        c[i]=(int *)malloc(11*sizeof(int));
    int * table1=(int *)calloc(11,sizeof(int));
    int * table2=(int *)calloc(11,sizeof(int));
    for(int i=0;i<11;i++)
        for(int j=0;j<11;j++)
            c[i][j]=0;
    int x[10]={7,9,8,3,2,4,1,5,6,10};
    int y[10]={6,9,8,7,3,2,1,4,5,10};
    cout<<LCS(x,y,c)<<endl;
    cout<<LCSV2(x,y,table1,table2)<<endl;
    showArray(x,y,c);
    return 0;
}