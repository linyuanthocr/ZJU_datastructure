#include<vector>
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cctype>
#include<cmath>
#include<cstdlib>
#include<queue>
using namespace std;
#define MAXnum 10001
#define INF 100001
#define max(a,b) a>b?a:b
#define min(a,b) a<b?a:b
struct node{
    int prefect;
    int c[6];
    int sum;
    int flag;
    int id;
}p[MAXnum];

bool compare(struct node p1,struct node p2 )
{
    if(p1.sum!=p2.sum)
        return p1.sum>p2.sum;
    else if(p1.prefect!=p2.prefect)
        return p1.prefect>p2.prefect;
    else
        return p1.id<p2.id;
    
    return false;
}
void sort1(int n,int k)
{
    
    struct node t;
    int j=0;
    
    for(int i=1;i<n;i++)
    {
        t=p[i];
        for( j=i;j>0&&compare(t,p[j-1]);j--)
            p[j]=p[j-1];
        p[j]=t;
    }
}
int main()
{
    int n,k,m;
    int x,score,t;
    int a[5];
    
    scanf("%d%d%d",&n,&k,&m);
    
    
    for(int i=0;i<k;i++)
        scanf("%d",&a[i]);
    
    for(int i=0;i<n;i++)
    {
        p[i].sum=0;
        p[i].flag=0;
        p[i].id=i+1;
        p[i].prefect=0;
        
        for(int j=0;j<k;j++)
            p[i].c[j]=-5;
    }
    
    
    for(int i=0;i<m;i++)
    {
        scanf("%d%d%d",&x,&t,&score);
        
        --x;
        
        p[x].id=x+1;
        
        --t;
        
        p[x].c[t]=max(p[x].c[t],score);
    }
    
    for(int i=0;i<n;i++)
    {
        
        for(int j=0;j<k;j++)
        { if(p[i].c[j]>=0)
        { p[i].sum+=p[i].c[j];
            p[i].flag=1;
        }
            if(p[i].c[j]==a[j])
                p[i].prefect++;
            
        }
        
    }
    sort1(n,k);
    int h=1;
    score=p[0].sum;
    for(int i=0;i<n;i++)
    {
        if(!p[i].flag) continue;
        if(i!=0&&p[i].sum!=score)
        { h=i+1;
            score=p[i].sum;
        }
        
        
        printf("%d %05d %d",h,p[i].id,p[i].sum);
        
        for(int j=0;j<k;j++)
            if(p[i].c[j]>=0)
                printf(" %d",p[i].c[j]);
            else if(p[i].c[j]==-1)
                printf(" 0");
            else
                printf(" -");
        printf("\n");
    }
    return 0;
}
