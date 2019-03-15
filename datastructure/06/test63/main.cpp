#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <queue>
#include <string.h>

using namespace std;
#define MAXSIZE 10000

typedef int Vertex;

struct GNode
{
    Vertex v;
    GNode* next;
    GNode(int val)
    {
        v = val;
        next = NULL;
    }
    GNode()
    {
        v = 0;
        next = NULL;
    }
};
typedef GNode* PGnode;
struct Graph
{
    int nv;
    int ne;
    PGnode gnodes[MAXSIZE];
    bool visit[MAXSIZE];
    Graph()
    {
        nv = 0;
        ne = 0;
        memset(visit,0,MAXSIZE*sizeof(bool));
        memset(gnodes, 0, MAXSIZE*sizeof(GNode));
    }
};
typedef Graph* LGraph;

LGraph create(int num);
void addEdge(LGraph pgraph, Vertex v1, Vertex v2);
void printfSixDegPercent(LGraph pgraph);
int BFS(LGraph pgraph, Vertex v);
void resetvisit(LGraph pgraph);

int main()
{
    int vnum;
    cin >> vnum;
    LGraph pgraph = create(vnum);
    cin >> pgraph->ne;
    for(int l1 = 0; l1 < pgraph->ne; l1++)
    {
        Vertex v1, v2;
        cin >> v1 >> v2;
        addEdge(pgraph, v1-1, v2-1);
    }
    int connectnum = 0;
    for(Vertex v = 0; v < pgraph->nv; v++)
    {
        connectnum = BFS(pgraph, v);
        printf("%d: %.2f%%\n", v+1, double(connectnum)/pgraph->nv*100.0);
        resetvisit(pgraph);
    }
    return 0;
}


LGraph create(int num)
{
    LGraph pgraph = new Graph();
    pgraph->nv = num;
    return pgraph;
}

int BFS(LGraph pgraph, Vertex v)
{
    int count = 0;
    count = 1;
    pgraph->visit[v] = true;
    Vertex w;
    Vertex last = v;
    Vertex tail = v;
    int level = 0;
    queue<Vertex> qv;
    qv.push(v);
    PGnode neighbor;
    while(!qv.empty())
    {
        v = qv.front();
        qv.pop();
        neighbor = pgraph->gnodes[v];
        while(neighbor!=NULL)
        {
            Vertex w = neighbor->v;
            if(!pgraph->visit[w])
            {
                pgraph->visit[w] = true;
                count++;
                qv.push(w);
                tail = w;
            }
            neighbor = neighbor->next;
        }
        if(v == last)
        {
            level++;
            last = tail;
        }
        if(level == 6)
            return count;
    }
    return count;
}

void addEdge(LGraph pgraph, Vertex v1, Vertex v2)
{
    PGnode e2 = new GNode(v2);
    e2->next = pgraph->gnodes[v1];
    pgraph->gnodes[v1] = e2;
    
    PGnode e1 = new GNode(v1);
    e1->next = pgraph->gnodes[v2];
    pgraph->gnodes[v2] = e1;
}

void resetvisit(LGraph pgraph)
{
    memset(pgraph->visit, 0, MAXSIZE*sizeof(bool));
}








