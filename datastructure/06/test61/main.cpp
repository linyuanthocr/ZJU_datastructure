#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <queue>

#define MAXSIZE 10
using namespace std;


typedef int Vertex;
struct graph
{
    int nv;
    int ne;
    int D[MAXSIZE][MAXSIZE];
    bool visit[MAXSIZE];
    graph(){nv = 0; ne = 0;
        memset(D,0,MAXSIZE*MAXSIZE*sizeof(int));
        memset(visit, 0, MAXSIZE*sizeof(bool));
    }
};
typedef graph* MGraph;

enum print_method {USE_DFS, USE_BFS};

MGraph create(int num)
{
    MGraph pgraph = new graph();
    pgraph->nv = num;
    return pgraph;
}

void resetvisit(MGraph pgraph);

void insertedge(MGraph pgraph);

void printgraph(MGraph pgraph, print_method pm);

void BFS(MGraph pgraph, Vertex v);
void DFS(MGraph pgraph, Vertex v);

int main()
{
    int vnum;
    cin >> vnum;
    MGraph pgraph = create(vnum);
    cin>> pgraph->ne;
    for(int l1 = 0; l1 < pgraph->ne; l1++)
    {
        insertedge(pgraph);
    }
    printgraph(pgraph, USE_DFS);
    resetvisit(pgraph);
    printgraph(pgraph, USE_BFS);
    return 0;
}

void resetvisit(MGraph pgraph)
{
    memset(pgraph->visit, 0,  MAXSIZE*sizeof(bool));
}

void insertedge(MGraph pgraph)
{
    Vertex v1, v2;
    cin >> v1 >> v2;
    pgraph->D[v1][v2] = 1;
    pgraph->D[v2][v1] = 1;
}

void printgraph(MGraph pgraph, print_method pm)
{
    for(Vertex l1 = 0; l1 < pgraph->nv; l1++)
    {
        if(!pgraph->visit[l1])
        {
            printf("{ ");
            switch (pm) {
                case USE_DFS:
                    DFS(pgraph, l1);
                    break;
                case USE_BFS:
                    BFS(pgraph, l1);
                default:
                    break;
            }
            printf("}\n");
        }
    }
}

void BFS(MGraph pgraph, Vertex v)
{
    queue<Vertex> qvetx;
    pgraph->visit[v] = true;
    printf("%d ", v);
    qvetx.push(v);
    while(!qvetx.empty())
    {
        Vertex v = qvetx.front();
        qvetx.pop();
        for(Vertex w = 0; w < pgraph->nv; w++)
        {
            if(pgraph->D[v][w] && !pgraph->visit[w])
            {
                pgraph->visit[w] = true;
                printf("%d ", w);
                qvetx.push(w);
            }
        }
    }
}
void DFS(MGraph pgraph, Vertex v)
{
    pgraph->visit[v] = true;
    printf("%d ", v);
    for(Vertex w = 0; w < pgraph->nv; w++)
    {
        if(pgraph->D[v][w] && !pgraph->visit[w])
        {
            DFS(pgraph, w);
        }
    }
}















