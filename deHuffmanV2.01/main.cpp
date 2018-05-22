#include <iostream>
#include <fstream>
#include <map>
#include <cstdlib>
#include <bitset>
#include <vector>
int main() {
    using namespace std;
    cout<<"Enter the file name to decompress:";
    string finname;
    cin>>finname;
    ifstream fin(finname,ios::in|ios::binary);
    if(!fin.is_open())
    {
        cerr<<"Failed in open file "<<finname<<'.'<<endl;
        cin.get();
        cin.get();
        return 1;
    }
    int size;
    fin.read((char *)&size,sizeof(int));
    map<int,char> deHuffmanMap;
    for(int i=0;i<size;i++)
    {
        char ch;
        int in;
        fin.read(&ch,sizeof(char));
        fin.read((char*)&in,sizeof(int));
        deHuffmanMap[in]=ch;
    }

    //deHuffmanMap没有去掉每个数字标头的1
    unsigned int bit_1=0,bit_2=0;
    int pos=0;//现在已经读取pos
    double sum=1    ;
    cout<<"Enter the name for target file:";
    string foutname;
    cin>>foutname;
    ofstream fout(foutname);
    vector <unsigned int> vecIn;
    while(fin.read((char*)&bit_1,sizeof(unsigned int)))
        vecIn.push_back(bit_1);
    fin.close();

    bit_1=vecIn[0];
    double count=1;
    double lasttime=0;
    sum=vecIn.size();
    vector<char> vecOut;
    while(count<sum)
    {
        bit_2=vecIn[count];
        if(count/sum>lasttime+0.01)
        {
            cout<<count/sum*100<<"%finished...\n";
            lasttime=count/sum;
        }
        count++;
        while(pos<32)
        {
            int length=1;
            unsigned int code=1;
            code=(bit_1<<pos);
            code=code>>pos;
            code=code>>(31-pos);
            //再读一位 是新数字的最高位
            pos++;
            while(!deHuffmanMap.count(code+(1<<length)))//如果现在这个code并不在表中
            {
                if(pos<32)
                {
                    unsigned int temp=bit_1<<pos;
                    temp=temp>>pos;
                    temp=temp>>(31-pos);
                    code=(code<<1)+temp;
                    pos++;
                }
                else
                {
                    unsigned int temp=bit_2<<(pos-32);
                    temp=temp>>(pos-32);
                    temp=temp>>(63-pos);
                    code=(code<<1)+temp;
                    pos++;
                }
                length++;
            }
            char cha=deHuffmanMap[(code+(1<<length))];
            vecOut.push_back(cha);
        }
        pos-=32;
        bit_1=bit_2;
    }
    for(int i=0;i<vecOut.size();i++)
        fout.write((char*)&vecOut[i],sizeof(char));
    cout<<"Done.";
    cin.get();
    cin.get();
    return 0;
}