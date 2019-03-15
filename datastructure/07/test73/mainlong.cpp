#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <climits>
#define MAXSIZE 500

using namespace std;

long D[MAXSIZE][MAXSIZE];
long C[MAXSIZE][MAXSIZE];

void flord(long D[MAXSIZE][MAXSIZE], long C[MAXSIZE][MAXSIZE], int n);

int main()
{
    int n, m, s, d;
    cin >> n >> m >> s >> d;
    int c,l;
    for(c = 0; c < n; c++)
    {
        for(l = 0; l < n; l++)
        {
            D[c][l] = INT_MAX;
            C[c][l] = INT_MAX;
        }
    }
    for(int l1 = 0; l1 < m; l1++)
    {
        cin>>c>>l;
        cin >> D[c][l] >> C[c][l];
        D[l][c] = D[c][l];
        C[l][c] = C[c][l];
    }
    flord(D,C,n);
    printf("%ld %ld\n",D[s][d],C[s][d]);
}

void flord(long D[MAXSIZE][MAXSIZE], long C[MAXSIZE][MAXSIZE], int n)
{
    int i, j, k;
    for(k = 0; k < n; k++)
    {
        for(i = 0; i < n; i++)
        {
            for(j = 0; j < n; j++)
            {
                if((D[i][k]+D[k][j]<D[i][j])||(D[i][k]+D[k][j]==D[i][j]&&(C[i][k]+C[k][j]<C[i][j])))
                {
                    D[i][j] = D[i][k]+D[k][j];
                    C[i][j] = C[i][k]+C[k][j];
                }
            }
        }
    }
}
