#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#define MAXSIZE 51
using namespace std;
int num[MAXSIZE];

int main()
{
    int n;
    cin >> n;
    memset(num,0,MAXSIZE*sizeof(int));
    int a;
    for(int l1 = 0; l1 < n; l1++)
    {
        cin >> a;
        num[a]++;
    }
    for(int l1 = 0; l1 < MAXSIZE; l1++)
    {
        if(num[l1])
        {
            printf("%d:%d\n",l1,num[l1]);
        }
    }
    return 0;
}
