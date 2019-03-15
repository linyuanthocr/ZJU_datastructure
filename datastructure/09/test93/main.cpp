#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#define MAXSIZE 100

using namespace std;

bool insertion_sort(int A[], int TmpA[], int OutA[], int n);
void printres(int A[], int n);
bool isSame(int A[], int B[], int n);
bool heap_sort(int A[], int TmpA[], int OutA[], int n);
void creat_heap(int A[], int TmpA[], int n);
void add_element(int A[], int TmpA[], int ntemp);
void adjust_maxheap(int A[], int n);

int main()
{
    int num;
    cin >> num;
    int* A = new int[num];
    int *Ares = new int[num];
    int *Aout = new int[num];
    
    for(int i = 0; i < num; i++)
    {
        cin >> A[i];
    }
    for(int i = 0; i < num; i++)
    {
        cin >> Aout[i];
    }
    
    memset(Ares,0,sizeof(int)*num);
    
    if(insertion_sort(A,Ares,Aout,num))
    {
        printf("Insertion Sort\n");
        printres(Ares,num);
    }
    else if(heap_sort(A,Ares,Aout,num))
    {
        printf("Heap Sort\n");
        printres(Ares,num);
    }
    else
    {
        printf("Error\n");
    }
    delete [] A;
    delete [] Ares;
    delete [] Aout;
    return 0;
}

void printres(int A[], int n)
{
    if(n<=0)
    {
        printf("\n");
        return;
    }
    for(int i = 0; i < n-1; i++)
    {
        printf("%d ", A[i]);
    }
    printf("%d\n", A[n-1]);
}


bool insertion_sort(int A[], int TmpA[], int OutA[], int n)
{
    if(n==1)
    {
        TmpA[0] = A[0];
        return true;
    }
    bool isinsert = false;
    memcpy(TmpA, A, sizeof(int)*n);
    int tmp;
    int i, j;
    for(i = 1; i < n; i++)
    {
        tmp = A[i];
        for(j = i-1; j >= 0; j--)
        {
            if(TmpA[j]>tmp)
                TmpA[j+1] = TmpA[j];
            else
                break;
        }
        TmpA[j+1] = tmp;
        
        //printf("Round %d\n",i);
        //printres(TmpA,n);
        if(isinsert)
            break;
        if(isSame(TmpA, OutA,n))
        {
            //printf("Same with intersection!!!\n");
            isinsert = true;
        }
    }
    return isinsert;
}

bool isSame(int A[], int B[], int n)
{
    for(int i = 0; i < n; i ++)
    {
        if(A[i]!=B[i])
            return false;
    }
    return true;
}

bool heap_sort(int A[], int TmpA[], int OutA[], int n)
{
    bool isheap = false;
    creat_heap(A, TmpA, n);
    //printres(TmpA,n);
    for(int i = n; i>=1; i--)
    {
        swap(TmpA[i-1],TmpA[0]);
        //printres(TmpA,n);
        adjust_maxheap(TmpA,i-1);
        //printres(TmpA,n);
        //printf("##########################\n");
        if(isheap)
            break;
        if(isSame(TmpA,OutA,n))
        {
            isheap = true;
        }
    }
    memcpy(A,TmpA,n*sizeof(int));
    return isheap;
}

void creat_heap(int A[], int TmpA[], int n)
{
    for(int l1 = 0; l1 < n; l1++)
    {
        add_element(A, TmpA, l1);
    }
}

void add_element(int A[], int TmpA[], int ntemp)
{
    int tmp = A[ntemp];
    int i = ntemp;
    TmpA[i] = tmp;
    for(;(i>=1);i=(i-1)/2)
    {
        if(TmpA[(i-1)/2]<tmp)
            TmpA[i] = TmpA[(i-1)/2];
        else
            break;
    }
    if(i>=0)
        TmpA[i] = tmp;
}

void adjust_maxheap(int A[], int n)
{
    int parent = 0;
    int child;
    int tmp = A[parent];
    for(;2*parent+1<n;parent = child)
    {
        child = 2*parent+1;
        if(child!=n-1 && A[child+1]>A[child])
            child++;
        if(A[child]>tmp)
        {
            A[parent] = A[child];
        }
        else
            break;
    }
    A[parent] = tmp;
}





















