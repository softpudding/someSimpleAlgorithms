#include <iostream>
#include <fstream>
#include <map>
#include <cstdlib>
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
    unsigned char bit_1=0,bit_2=0;
    int pos=0;//现在已经读取pos
    fin.read((char *)&bit_1,sizeof(char));
    double sum=1    ;
    cout<<"Enter the name for target file:";
    string foutname;
    cin>>foutname;
    ofstream fout(foutname);
    while(fin.read((char *)&bit_2,sizeof(char)))
        sum++;
    fin.close();fin.open(finname,ios::in|ios::binary);
    fin.read((char *)&size,sizeof(int));
    for(int i=0;i<size;i++)
    {
        char ch;
        int in;
        fin.read(&ch,sizeof(char));
        fin.read((char*)&in,sizeof(int));
    }
    fin.read((char*)&bit_1,sizeof(char));
    double count=0;
    while(fin.read((char *)&bit_2,sizeof(char)))
    {

        cout.setf(ios_base::fixed);
        cout.precision(2);
        cout<<count++/sum*100<<"%finished."<<endl;
        while(pos<8)
        {
            int length=1;
            unsigned char code=1;
            code=(bit_1<<pos);
            code=code>>pos;
            code=code>>(7-pos);
            //再读一位 是新数字的最高位
            pos++;
            while(!deHuffmanMap.count(code+(1<<length)))//如果现在这个code并不在表中
            {
                if(pos<8)
                {
                    unsigned char temp=bit_1<<pos;
                    temp=temp>>pos;
                    temp=temp>>(7-pos);
                    code=(code<<1)+temp;
                    pos++;
                }
                else
                {
                    unsigned char temp=bit_2<<(pos-8);
                    temp=temp>>(pos-8);
                    temp=temp>>(15-pos);
                    code=(code<<1)+temp;
                    pos++;
                }
                length++;
            }
            char cha=deHuffmanMap[(code+(1<<length))];
            fout<<deHuffmanMap[code+((1<<length))];
        }
        pos-=8;
        bit_1=bit_2;
    }

    cout<<"Done.";
    cin.get();
    cin.get();
    return 0;
}