#include <iostream>
//table should be 0...size-1,0...size-1 should be ini to all 1
int maxPalindrome (char * st,int size,int ** table)
{
    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
            table[i][j]=0;
    for(int i=0;i<size;i++)
        table[i][i]=1;
    for(int l=2;l<=size;l++)//l the length of a string
    {
        for(int i=0;i<size+1-l;i++)//i+l-1<size so i<size-l+1
        {
            if(st[i]==st[i+l-1])
                table[i][i+l-1]=table[i+1][i+l-2]+2;
            else if(table[i+1][i+l-1]>=table[i][i+l-2])
                table[i][i+l-1]=table[i+1][i+l-1];
            else
                table[i][i+l-1]=table[i][i+l-2];
        }
    }
    return table[0][size-1];

}
int main() {
    int size=11;
    int ** lengthTable=new int *[size];
    for(int i=0;i<size;i++)
        lengthTable[i]=new int [size];
    char s[size]="ccharacterc";
    std::cout<<maxPalindrome(s,size,lengthTable);

    return 0;
}