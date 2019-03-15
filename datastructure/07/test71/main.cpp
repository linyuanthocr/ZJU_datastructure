#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#define MAXSIZE 100

using namespace std;

long dmap[MAXSIZE][MAXSIZE];
int vnum;

void generatemap();
void flord();
void getopt();

int main()
{
    cin >>vnum;
    if(vnum==1)
    {
        printf("1 0");
        return 0;
    }
    generatemap();
    flord();
    getopt();
    return 0;
}

//void printgraph()
//{
//    for(int l1 = 0; l1 < vnum; l1++)
//    {
//        for(int l2 = 0; l2 < vnum; l2++)
//        {
//            printf("%ld ", dmap[l1][l2]);
//        }
//        printf("\n");
//    }
//}

void generatemap()
{
    int ne;
    cin >> ne;
    for(int l1 = 0; l1 < vnum; l1++)
    {
        for(int l2 = 0; l2 < vnum; l2++)
        {
            if(l1 == l2)
                dmap[l1][l2] = 0;
            else
                dmap[l1][l2] = INT_MAX;
        }
    }
    int v1, v2, val;
    for(int l1 = 0; l1 < ne; l1++)
    {
        cin >> v1 >> v2 >> val;
        dmap[v1-1][v2-1] = val;
        dmap[v2-1][v1-1] = val;
    }
    //printgraph();
}

void flord()
{
    for(int k = 0; k < vnum; k++)
    {
        for(int i = 0; i < vnum; i++)
        {
            for(int j = 0; j < vnum; j++)
            {
                if(dmap[i][j]>dmap[i][k]+dmap[k][j])
                {
                    dmap[i][j]=dmap[i][k]+dmap[k][j];
                }
            }
        }
    }
//    printgraph();
}

void getopt()
{
    int resid = 0;
    int resmindis = INT_MAX;
    int locmindis = 0;
    bool bget = false;
    for(int l1 = 0; l1 < vnum; l1++)
    {
        locmindis = -1;
        bget = false;
        for(int l2 = 0; l2 < vnum; l2++)
        {
            if(dmap[l1][l2]>locmindis)
            {
                locmindis = dmap[l1][l2];
                bget = true;
            }
        }
        if(bget && locmindis<resmindis)
        {
            resmindis = locmindis;
            resid = l1;
        }
    }
    if(resmindis == INT_MAX)
    {
        printf("0\n");
    }
    else
    {
        printf("%d %d\n", resid+1, resmindis);
    }
}














