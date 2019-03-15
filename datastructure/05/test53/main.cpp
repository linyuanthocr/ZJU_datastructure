#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
#define MAX_SIZE 64
#define MIN_VAL -1
#define CHAR_NUM 256
#define MAX_CODE_LENGTH 100

struct MinHeap
{
    int data[MAX_SIZE];
    int size;
    MinHeap(){size=0;data[0]=MIN_VAL;}
};

int calWPL(int* freq);
MinHeap* generateMinHeap(int* freq);
MinHeap* create();
MinHeap* insert(MinHeap* pmh, int val);
int deletemhp(MinHeap* pmh);
bool isPrefix(char *s1, char *s2);
bool hasPrefixCode(char s[][MAX_CODE_LENGTH], int n);

int main()
{
    int num = 0;
    cin >> num;
    int freq[CHAR_NUM] = {0};
    char c;
    for(int l1 = 0; l1 < num; l1++)
    {
        cin>>c;
        cin>>freq[c];
    }
    int wpl = calWPL(freq);
    int subnum;
    cin >> subnum;

    for(int l1 = 0; l1 < subnum; l1++)
    {
        char ch[CHAR_NUM];
        char s[CHAR_NUM][MAX_CODE_LENGTH];
        int thisWPL = 0;
        for(int i = 0; i < num; i++)
        {
            cin>>ch[i]>>s[i];
            thisWPL += freq[ch[i]] * strlen(s[i]);
        }
        if(thisWPL==wpl && !hasPrefixCode(s,num))
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}

int calWPL(int* freq)
{
    MinHeap* pmh = NULL;
    //printf("BF GENERATE\n");
    pmh = generateMinHeap(freq);
    //printf("GENERATE HEAP DONE!!!\n");
    int wpl = 0;
    while(pmh->size>=2)
    {
        int v1 = deletemhp(pmh);
        int v2 = deletemhp(pmh);
        wpl += v1+v2;
        pmh = insert(pmh, v1+v2);
    }
    return wpl;
}

MinHeap* generateMinHeap(int* freq)
{
    MinHeap* pmh = new MinHeap();
    for(int l1 = 0; l1 < CHAR_NUM; l1++)
    {
        if(freq[l1]>0)
            pmh = insert(pmh, freq[l1]);
    }
    return pmh;
}

MinHeap* insert(MinHeap* pmh, int val)
{
    pmh->data[++pmh->size] = val;
    int i = pmh->size;
    for(;pmh->data[i/2]>val;i = i/2)
    {
        pmh->data[i] = pmh->data[i/2];
    }
    pmh->data[i] = val;
    //printf("insert %d\n", val);
    return pmh;
}

int deletemhp(MinHeap* pmh)
{
    if(pmh==NULL||pmh->size==0)
        return MIN_VAL;
    int minnum = pmh->data[1];
    int val = pmh->data[pmh->size--];
    int parent;
    int child;
    for(parent=1; 2*parent <= pmh->size; parent = child)
    {
        child = 2 * parent;
        if(child<pmh->size && pmh->data[child]>pmh->data[child+1])
        {
            child++;
        }
        if(val<=pmh->data[child])
        {
            break;
        }
        else
        {
            pmh->data[parent] = pmh->data[child];
        }
    }
    pmh->data[parent] = val;
    return minnum;
}

bool isPrefix(char *s1, char *s2)
{
    while(s1&&s2&&(*s1==*s2))
    {
        s1++;
        s2++;
    }
    if(*s1=='\0' || *s2 =='\0')
    {
        return true;
    }
    else
        return false;
}
bool hasPrefixCode(char s[][MAX_CODE_LENGTH], int n)
{
    for(int l1 = 0; l1 < n; l1++)
    {
        for(int l2 = l1+1; l2< n; l2++)
        {
            if(isPrefix(s[l1], s[l2]))
                return true;
        }
    }
    return false;
}
