//
// Created by 11570 on 2018/5/31.
//

#ifndef VEBTREE_VEBTREE_H
#define VEBTREE_VEBTREE_H
//vEB tree can only be applied to non-negative keys so just use unsigned int instead of int
//this version can only be applied to non-negative version
//high and low are based on the fact that int or unsigned int is stored in 4 bytes,32 bits
unsigned int length(unsigned int n)//this function tells the length of a bin number
{
    unsigned int temp=n;
    unsigned int ct=0;
    while(temp!=0)
    {
        temp>>=1;
        ct++;
    }
    return ct;
}
class vEB {
private:
    unsigned int u;
    vEB * summary;
    vEB ** cluster;//two arrays of vEB pts
    unsigned int min;
    unsigned int max;
    unsigned int high(unsigned int x)
    {
        unsigned int l=length(u);
        x>>=(unsigned int)(l/2);
        return x;
    }
    unsigned int low(unsigned int x)
    {
        unsigned int l=length(u);
        x<<=(32-(unsigned int)(l/2));
        x>>=(32-(unsigned int)(l/2));
        return x;
    }
    unsigned int index(unsigned int x,unsigned int y)
    {
        unsigned int l=length(u);
        l/=2;
        return (x<<l)+y;
    }
    void vEBEmptyInsert(unsigned int x)
    {
        min=max=x;
    }
public:
    explicit vEB(unsigned int n);
    bool vEBMember(unsigned int x);
    unsigned int vEBSuccessor(unsigned int x);
    unsigned int vEBPredecessor(unsigned int x);
    void vEBInsert(unsigned int x);
    void vEBDelete(unsigned int x);
};

vEB::vEB(unsigned int n):u(n)
{
    unsigned int new_u=u>>(length(u)/2);//which should be the size of cluster/summary
    unsigned int new_size=u/new_u;//which should be the new u of each cluster/summary
    min=max=UINT32_MAX;//use UINT32_MAX as a sign of NIL
    if(u!=2)
    {
        summary=new vEB(new_u);
        cluster=new vEB *[new_u];
        for(int i=0;i<new_u;i++)
            cluster[i]=new vEB(new_size);
    }
    else//for u=2 jusr need min and max
    {
        summary= nullptr;
        cluster= nullptr;
    }
}
bool vEB::vEBMember(unsigned int x)
{
    if(x==min||x==max)
        return true;
    else if(summary!= nullptr)
        return cluster[high(x)]->vEBMember(low(x));
    else return false;
    /*this is the version on textbook
     if(x==min||x==max)
        return true;
     else if(u==2)
        return false;
     else
        return cluster[high(x)->vEBMember(low(x));
     */
}
unsigned int vEB::vEBSuccessor(unsigned int x)
{
    if(u==2)
    {
        if(x==0&&max==1)
            return 1;
        else return UINT32_MAX;
    }
    else if(x<min&&min!=UINT32_MAX)
    {
        return min;
    }
    else
    {
        unsigned int max_low=cluster[high(x)]->max;
        if(max_low!=UINT32_MAX&&low(x)<max_low)
            return index(high(x),cluster[high(x)]->vEBSuccessor(low(x)));
        else
        {
            unsigned int succ_cluster=summary->vEBSuccessor(high(x));
            if(succ_cluster!=UINT32_MAX)
                return index(succ_cluster,cluster[succ_cluster]->min);
            else return UINT32_MAX;
        }
    }
}
unsigned int vEB::vEBPredecessor(unsigned int x)
{
    if(u==2)
    {
        if(x==1&&min==0)
            return 0;
        else return UINT32_MAX;
    }
    else if(x>max&&max!=UINT32_MAX)
    {
        return max;
    }
    else
    {
        unsigned int min_low=cluster[high(x)]->min;
        if(min_low!=UINT32_MAX&&low(x)>min_low)//同簇
            return index(high(x),cluster[high(x)]->vEBPredecessor(low(x)));
        else//非同簇
        {
            unsigned int pred_cluster=summary->vEBPredecessor(high(x));
            if(pred_cluster!=UINT32_MAX)//如果存在前一簇
                return index(pred_cluster,cluster[pred_cluster]->max);
            else if(min!=UINT32_MAX&&min<x)//如果有不在簇里的 并且确实比这个小//不然如果是同一个数呢
                return min;
            else return UINT32_MAX;
        }


    }

}
void vEB::vEBInsert(unsigned int x)
{
    if(min==UINT32_MAX)
    {
        vEBEmptyInsert(x);
    }
    else
    {
        if(x<min)
        {
            unsigned int temp=x;
            x=min;
            min=temp;
        }
        if(u>2)
        {
            if(cluster[high(x)]->min==UINT32_MAX)
            {
                summary->vEBInsert(high(x));
                cluster[high(x)]->vEBEmptyInsert(low(x));
            }
            else
                cluster[high(x)]->vEBInsert(low(x));
        }
        if(x>max)
            max=x;

    }

}
void vEB::vEBDelete(unsigned int x)
{
    if(min==max)
        min=max=UINT32_MAX;
    else if(u==2)
    {
        if(x==1)
        {
            max=0;
        }
        else
            min=1;
    }
    else
    {
        if(x==min)
        {
            unsigned int first_cluster=summary->min;
            unsigned int offset=cluster[first_cluster]->min;
            unsigned int temp=x;
            x=index(first_cluster,offset);
            min=temp;
        }
        cluster[high(x)]->vEBDelete(low(x));
        if(cluster[high(x)]->min==UINT32_MAX)
        {
            summary->vEBDelete(high(x));
            if(max==x)
            {
                unsigned int summary_max=summary->max;
                if(summary_max==UINT32_MAX)
                    max=min;
                else{
                    unsigned int offset=cluster[summary_max]->max;
                    max=index(summary_max,offset);
                }
            }
        }
        else if(max==x)
        {
            max=index(high(x),cluster[high(x)]->max);
        }
    }
}

#endif //VEBTREE_VEBTREE_H
