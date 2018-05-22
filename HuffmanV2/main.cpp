#include <iostream>
#include <fstream>
#include <cctype>
#include <map>
#include <bitset>

//ch=='$'represents an inner node
class Node{
public:
    char ch;
    Node * p;
    Node * l;//0
    Node * r;//1
    double freq;
    Node(char c,double f):ch(c),freq(f)
    {
        p=l=r= nullptr;
    }

};
class minPriorityQueue{
private:
    Node ** list;
    int size;
public:
    explicit minPriorityQueue(int n)
    {
        list=new Node *[n];
        size=n;
        for(int i=0;i<size;i++)
            list[i]= nullptr;
    }
    Node * extractMin()
    {
        Node * re=list[0];
        for(int i=1;i<size;i++)
        {
            list[i-1]=list[i];
        }
        list[size-1]= nullptr;
        return re;
    }
    bool insert(Node * z) {
        for (int i = 0; i < size; i++)
            if (list[i] == nullptr) {
                list[i] = z;
                return true;
            } else if (z->freq < list[i]->freq) {
                Node *temp = list[i];
                list[i] = z;
                for (int j = size - 1; j > i; j--) {
                    list[j] = list[j - 1];
                }
                list[i + 1] = temp;
                return true;
            }

        return false;
    }
    Node *  makeATree()
    {
        while(list[1]!= nullptr)
        {
            Node * a=extractMin();
            Node * b=extractMin();
            Node * z=new Node ('$',a->freq+b->freq);
            z->l=a;z->r=b;
            insert(z);
        }

        return list[0];
    }

};
void Huffman(Node * node,std::map<char,int>& m,int n)//left 0 right 1
{
    if(node->l!= nullptr)
        Huffman(node->l,m,(n<<1)+0);
    if(node->ch!='$')
        m[node->ch]=n;
    if(node->r!= nullptr)
        Huffman(node->r,m,(n<<1)+1);

}
int length(int n)
{
    int i=1;
    while((n>>i)!=1)
        i++;
    return i;
}
int main() {
    using namespace std;
    cout<<"Enter the file name to compress:";
    string finname;
    cin>>finname;
    ifstream fin(finname);
    if(!fin.is_open())
    {
        cerr<<"Open file failed.";
        cin.get();
        cin.get();
        return 1;
    }
    cout<<"Enter the file name to save:";
    string foutname;
    cin>>foutname;
    char ch;
    map<char,double> alphaMap;
    while(fin.get(ch))
    {
        if(alphaMap.count(ch))
            alphaMap[ch]++;
        else
            alphaMap[ch]=1;
    }
    int n=0;
    double sum=0;
    for(auto iter=alphaMap.begin();iter!=alphaMap.end();iter++)
    {
        n++;
        sum+=iter->second;
    }
    n++;
    for(auto iter=alphaMap.begin();iter!=alphaMap.end();iter++)
    {
        iter->second/=sum;
    }
    minPriorityQueue queue(n);
    for(auto iter=alphaMap.begin();iter!=alphaMap.end();iter++)
    {
        Node * newNode=new Node(iter->first,iter->second);
        queue.insert(newNode);
    }
    Node * tree=queue.makeATree();
    map<char,int> huffmanMap;
    Huffman(tree,huffmanMap,1);
    //now huffmanMap has stored the huffman code for target file which begins with 1
    fstream fout(foutname,ios::out|ios::binary);
    fin.close();
    fin.open(finname);
    unsigned int bit_1=0,bit_2=0;
    char pos=0;
    //int 是一个32位数 假设目前我占用了第pos位
    int size=huffmanMap.size();
    fout.write((char*)&size,sizeof(int));
    cout<<endl<<"Here shows the Huffman code for each character:\n";
    for(auto iter=huffmanMap.begin();iter!=huffmanMap.end();iter++)
    {
        cout<<iter->first<<'\t'<<bitset<32>(iter->second)<<endl;
        fout.write((char*)&iter->first,sizeof(char));
        fout.write((char*)&iter->second,sizeof(int));
    }
    int count=0;
    while(fin.get(ch))
    {
        count+=1;
        cout.setf(ios_base::fixed);
        cout.precision(2);
        cout<<(double)count/sum*100<<"%finished."<<endl;
        //length函数输出除去最高位1的huffman编码长度
        int code=huffmanMap[ch];
        if(pos+length(code)<=32)
        {
            bit_1+=(code-(1<<length(code)))<<(32-pos-length(code));
            pos=pos+length(code);
        }
        else
        {
            int leng_1=32-pos;//leng_1是这个bit里还可以存储的位数
            bit_1+=(code-(1<<length(code)))>>(length(code)-leng_1);
            bit_2+=(code-(1<<length(code)))<<(32-(length(code)-leng_1));
            pos=length(code)-leng_1;
            fout.write((char*)&bit_1,sizeof(unsigned int));
            cout<<bitset<32>(bit_1)<<endl;
            bit_1=bit_2;
            bit_2=0;
        }
    }
    fout.write((char*)&bit_1,sizeof(unsigned int));
    cout<<"Done!";
    cin.get();
    cin.get();
    return 0;
}