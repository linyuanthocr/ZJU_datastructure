#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;
#define MAXSIZE 1001
#define MINNUM -10001

struct heapnode
{
    int size;
    int *H;
    heapnode() {
        size = 0;
        H = NULL;
    }
};

heapnode* generateMinheap(int num);
heapnode* insert(heapnode *pheap, int val);
void printpath(heapnode* pheap, int id);

int main()
{
    int num;
    cin >> num;
    int shownum;
    cin >> shownum;
    heapnode *pheap = NULL;
    pheap = generateMinheap(num);
    int showid;
    for(int l1 = 0; l1 < shownum; l1++)
    {
        cin >> showid;
        printpath(pheap, showid);
    }
}

heapnode* generateMinheap(int num)
{
    heapnode *pheap = new heapnode();
    pheap->H = new int[num+1];
    pheap->H[0] = MINNUM;
    int val = 0;
    for(int l1 = 1; l1 <= num; l1++)
    {
        cin>> val;
        pheap = insert(pheap, val);
    }
    return pheap;
}

heapnode *insert(heapnode* pheap, int val)
{
//    printf("I am going to insert %d\n", val);
    pheap->H[++pheap->size] = val;
    int i = pheap->size;
    for(;pheap->H[i/2]>val;i = i/2)
    {
        pheap->H[i] = pheap->H[i/2];
    }
    pheap->H[i] = val;
//    printf("I am insert %d done!!\n", val);
    return pheap;
}

void printpath(heapnode* pheap, int id)
{
    if(id == 0)
        printf("\n");
    else
    {
        printf("%d", pheap->H[id]);
        while(id/2>0)
        {
            id /= 2;
            printf(" %d", pheap->H[id]);
        }
        printf("\n");
    }
}

