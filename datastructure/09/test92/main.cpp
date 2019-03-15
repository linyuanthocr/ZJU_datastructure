#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#define MAXSIZE 100

using namespace std;

bool insertion_sort(int A[], int TmpA[], int OutA[], int n);
void mergesort(int A[], int TmpA[], int OutA[], int L, int R, int T);
bool merge_sort(int A[], int TmpA[], int OutA[], int n);
void printres(int A[], int n);
bool isSame(int A[], int B[], int n);
void merge(int A[], int TmpA[], int L, int R, int RightEnd);
void merge_pass(int A[], int TmpA[], int N, int length);
bool mergesort2(int A[], int TmpA[], int OutA[], int N);
bool ismerge = false;
bool firstaftermerge = false;

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
    else if(mergesort2(A,Ares,Aout,num))
    {
        printf("Merge Sort\n");
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

bool merge_sort(int A[], int TmpA[], int OutA[], int n)
{
    mergesort(A,TmpA,OutA,0,n-1,n);
    return ismerge;
}
void mergesort(int A[], int TmpA[], int OutA[], int L, int R, int T)
{
    if(L<R &&!firstaftermerge)
    {
        int mid = (L+R)/2;
        mergesort(A,TmpA,OutA,L,mid,T);
        mergesort(A,TmpA,OutA,mid+1,R,T);
        if(ismerge)
            firstaftermerge = true;
        merge(A, TmpA, L, mid+1, R);
        printf("L is %d, mid is %d, R is %d\n", L, mid+1, R);
        printres(A,T);
        if(isSame(A,OutA,T))
        {
            ismerge = true;
        }
    }
}
void merge(int A[], int TmpA[], int L, int R, int RightEnd)
{
    int LeftEnd = R-1;
    int Tmp = L;
    int n = RightEnd - L +1;
    while(L<=LeftEnd&&R<=RightEnd)
    {
        if(A[L]<=A[R])
        {
            TmpA[Tmp++] = A[L++];
        }
        else
        {
            TmpA[Tmp++] = A[R++];
        }
    }
    while (L<=LeftEnd) {
        TmpA[Tmp++] = A[L++];
    }
    while (R<=RightEnd) {
        TmpA[Tmp++] = A[R++];
    }
    for(int i = 0; i < n; i++, RightEnd--)
    {
        A[RightEnd] = TmpA[RightEnd];
    }
}


void merge_pass(int A[], int TmpA[], int N, int length)
{
    int i = 0;
    int j = 0;
    for(i = 0; i <= N-2*length; i+=2*length)
    {
        merge(A,TmpA,i,i+length,i+2*length-1);
    }
    if(i+length<N)
    {
        merge(A,TmpA,i,i+length,N-1);
    }
    else
    {
        for(j = i; j < N; j++)
            TmpA[j] = A[j];
    }
}

bool mergesort2(int A[], int TmpA[], int OutA[], int N)
{
    int length = 1;
    while(length<N && !firstaftermerge)
    {
        merge_pass(A,TmpA,N,length);
        if(!ismerge&&isSame(A,OutA,N))
        {
            ismerge = true;
        }
        else if(ismerge)
        {
            firstaftermerge = true;
        }
        else if(firstaftermerge)
        {
            break;
        }
        length *=2;
    }
    return ismerge;
}
