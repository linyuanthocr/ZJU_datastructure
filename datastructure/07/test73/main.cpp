#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <climits>
#include <vector>
#include <string.h>
#define MAXSIZE 500

using namespace std;

long D[MAXSIZE][MAXSIZE];
long C[MAXSIZE][MAXSIZE];
bool flag[MAXSIZE];
double dis[MAXSIZE];
int nv;

void dijkstra(int s);
int findmindist();
int main()
{
    int n, m, s, d;
    cin >> n >> m >> s >> d;
    nv = n;
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
    memset(flag,0,MAXSIZE*sizeof(bool));
    dijkstra(s);
    printf("%ld %ld\n", D[s][d], C[s][d]);
}

int findmindist(int s)
{
    int minDist = INT_MAX;
    int v = -1;
    for(int i = 0; i < nv; i++)
    {
        if(!flag[i]&&D[s][i]<minDist)
        {
            minDist = D[s][i];
            v = i;
        }
    }
    return v;
}

void dijkstra(int s)
{
    D[s][s] = 0;
    flag[s] = true;
    while(1)
    {
        int v = findmindist(s);
        if(v==-1)
            break;
        flag[v] = true;
        for(int i = 0; i < nv; i++)
        {
            if(!flag[i]&&D[v][i]<INT_MAX)
            {
                if(D[s][v]+D[v][i]<D[s][i])
                {
                    D[s][i] = D[s][v]+D[v][i];
                    C[s][i] = C[s][v]+C[v][i];
                }
                else if((D[s][v]+D[v][i]==D[s][i])&&(C[s][v]+C[v][i]<C[s][i]))
                {
                    C[s][i] = C[s][v]+C[v][i];
                }
            }
        }
    }
}











