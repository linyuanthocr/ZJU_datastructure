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
}

heapnode* generateMinheap(int num);
heapnode* adjustToMinheap(heapnode *pheap);

int main()
{
    int num;
    cin >> num;
    int shownum;
    cin >> shownum;
    heapnode *pheap = NULL;
    pheap = generateMinheap(num);
}

heapnode* generateMinheap(int num)
{
    heapnode *pheap = new heapnode();
    pheap->H = new int[num+1];
    pheap->H[0] = MINNUM;
    for(int l1 = 1; l1 <= num; l1++)
    {
        cin>> pheap->H[++pheap->size];
    }
    pheap = adjustToMinheap(pheap);
    return pheap;
}
heapnode* adjustToMinheap(heapnode *pheap)
{
    int hsize = pheap->size;
    
}
