#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <queue>
#include <vector>
#include <math.h>
#define MAXSIZE 100
#define ISLANDRADIUS 7.5

using namespace std;
typedef int Vertex;

struct pos
{
    int x;
    int y;
    pos(int m, int n){x = m; y = n;}
    pos(){x = 0; y = 0;}
};

struct FirstEdge
{
    Vertex v;
    FirstEdge* next;
    FirstEdge(Vertex val)
    {
        v = val;
        next = NULL;
    }
};

struct graphnodes {
    pos loc;
    FirstEdge* links;
    graphnodes(int x, int y)
    {
        loc.x = x;
        loc.y = y;
        links = NULL;
    }
    graphnodes()
    {
        loc.x = 0;
        loc.y = 0;
        links = NULL;
    }
};

typedef graphnodes *pgraphnodes;

struct graph
{
    int ne;
    int nv;
    bool visit[MAXSIZE];
    pgraphnodes gnode[MAXSIZE];
    int size;
    graph()
    {
        ne = 0;
        nv = 0;
        size = 0;
        memset(visit, 0, MAXSIZE*sizeof(bool));
        memset(gnode, 0, sizeof(struct graphnodes));
    }
};

typedef graph *LGRAPH;

void insert(LGRAPH pgraph, int x, int y);
void updateconnection(LGRAPH pgraph, int maxdis);
void addedge(LGRAPH pgraph, Vertex v1, Vertex v2);
bool BFS(LGRAPH pgraph, Vertex v, int maxdis);
bool isSafe(pos loc, int maxdis);
bool findexit(LGRAPH pgraph);
LGRAPH create(int vnum);
bool isconnect(pos loc1, pos loc2, int maxdis);
bool findfirststep(LGRAPH pgraph, int maxdis, vector<Vertex> &vstart);

int main()
{
    int vnum;
    cin >> vnum;
    LGRAPH plgraph = NULL;
    plgraph = create(vnum);
    int maxdis;
    cin >> maxdis;
    pos lval;
    for(int l1 = 0; l1 < vnum; l1++)
    {
        cin>>lval.x>>lval.y;
        insert(plgraph, lval.x, lval.y);
    }
    updateconnection(plgraph, maxdis);
    vector<Vertex> vstarts;
    bool bfindfirst = findfirststep(plgraph, maxdis, vstarts);
    bool bout = false;
    for(int l1 = 0; l1 < vstarts.size(); l1++)
    {
        bout = BFS(plgraph, vstarts[l1], maxdis);
        if(bout) break;
    }
    if(bout)
        printf("Yes\n");
    else
        printf("No\n");
    return 0;
}

LGRAPH create(int vnum)
{
    LGRAPH plgraph = new graph();
    plgraph->nv = vnum;
    for(int l1 = 0; l1 < vnum; l1++)
    {
        plgraph->gnode[l1] = new graphnodes();
    }
    return plgraph;
}

void insert(LGRAPH pgraph, int x, int y)
{
    pgraph->gnode[pgraph->size++]->loc = pos(x,y);
}

bool BFS(LGRAPH pgraph, Vertex v, int maxdis)
{
    queue<Vertex> qv;
    pgraph->visit[v] = true;
    if(isSafe(pgraph->gnode[v]->loc, maxdis))
        return true;
    qv.push(v);
    while(!qv.empty())
    {
        Vertex v = qv.front();
        qv.pop();
        FirstEdge *neighbor = pgraph->gnode[v]->links;
        Vertex w;
        while(neighbor != NULL)
        {
            w = neighbor->v;
            if(!pgraph->visit[w])
            {
                pgraph->visit[w] = true;
                if(isSafe(pgraph->gnode[w]->loc, maxdis))
                    return true;
                qv.push(w);
            }
            neighbor = neighbor->next;
        }
    }
    return false;
}


bool isSafe(pos loc, int maxdis)
{
    if((loc.x+50)<=maxdis||(50-loc.x)<=maxdis||(loc.y+50)<=maxdis||(50-loc.y)<=maxdis)
        return true;
    else
        return false;
}


void updateconnection(LGRAPH pgraph, int maxdis)
{
    for(Vertex v = 0; v < pgraph->nv; v++)
    {
        for(Vertex w = v+1; w < pgraph->nv; w++)
        {
            if(isconnect(pgraph->gnode[v]->loc,pgraph->gnode[w]->loc, maxdis))
            {
                addedge(pgraph, v, w);
                addedge(pgraph, w, v);
                pgraph->ne++;
            }
        }
    }
}

bool isconnect(pos loc1, pos loc2, int maxdis)
{
    double dis = sqrt((loc1.x-loc2.x)*(loc1.x-loc2.x)+(loc1.y-loc2.y)*(loc1.y-loc2.y));
    return dis<=maxdis;
}

void addedge(LGRAPH pgraph, Vertex v1, Vertex v2)
{
    FirstEdge *edge = new FirstEdge(v2);
    edge->next = pgraph->gnode[v1]->links;
    pgraph->gnode[v1]->links = edge;
}

bool findfirststep(LGRAPH pgraph, int maxdis, vector<Vertex> &vstart)
{
    pos hloc(0,0);
    vstart.clear();
    for(Vertex v = 0; v < pgraph->nv; v++)
    {
        if(isconnect(pgraph->gnode[v]->loc, hloc, maxdis+ISLANDRADIUS))
        {
            vstart.push_back(v);
        }
    }
    return !vstart.empty();
}
