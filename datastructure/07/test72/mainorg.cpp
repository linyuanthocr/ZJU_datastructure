#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <climits>
#include <math>
#include <map>
#include <string.h>


#define MAXSIZE 100
#define ISLAND_RADIUS 7.5

using namespace std;
typedef int Vertex;

int cnum = 0;
int maxdis = 0;

struct data
{
    Vertex v;
    double dist;
    data(Vertex id, double d) {v = id; dist = d;}
    data() {v = -1; dist = -1;}
};

struct node
{
    data d;
    node* next;
    node(int val, double dis) {d.v = val; d.dist = dis; next = NULL;}
};

typedef node* PNode;

struct pos
{
    int x;
    int y;
    pos() = {x = 0; y = 0;}
};

struct graph
{
    int nv;
    int ne;
    PNode links[MAXSIZE];
    pos loc[MAXSIZE];
    bool completes[MAXSIZE];
    graph(){nv = 0; ne = 0;}
};

typedefine *graph PGraph;

struct
struct minheap
{
    int size;
    data D[MAXSIZE];
    minheap() {size = 0;}
};
typedef minheap* PHeap;

PGraph generategraph();
void updateconnections(PGraph pgraph);
void addedge(PGraph pgraph, Vertex v1, Vertex v2, double dis);
bool getfirst(PGraph pgraph, vector<Vertex> & vfirsts);
double dmethod(PGraph pgraph, Vertex firstid, vector<Vertex>& vexits);
bool isSafe(pos loc, double &dis);
bool isConnected(pos loc1, pos loc2, double &dis, doulbe thdis);
double getdis(pos loc1, pos loc2);
void resetgraphcompletes(PGraph pgraph);
PHeap create();
void addtoheap(PHeap pheap, Vertex v, double val);
data deleteheap(PHeap pheap);

int main()
{
    cin >> cnum;
    cin >> maxdis;
    PGraph pgraph = generategraph();
    updateconnections();
    vector<Vertex> vfirsts;
    vector<vector<Vertex>> vvexits;
    bool bgetf = getfirst(pgraph, vfirsts);
    if(!bgetf)
    {
        printf("0\n");
        return 0;
    }
    vvexits.resize(vfirsts.size());
    double mindist = DOUBLE_MAX;
    double locdist = DOUBLE_MAX;
    int selectid = -1;
    for(int l1 = 0; l1 < vfirsts.size(); l1++)
    {
        locdist = dmethod(pgraph, vfirsts[l1], vvexits[l1]);
        if(locdist<mindist)
        {
            mindist = locdist;
            selectid = l1;
        }
        resetgraphcompletes(pgraph);
    }
    if(locdist < DOUBLE_MAX)
    {
        int nexit = vvexits[selectid].size();
        printf("%d\n",nexit);
        Vertex v;
        for(int l1 = 0; l1 < nexit; l1++)
        {
            v = vvexits[selectid][l1];
            printf("%d %d\n", pgraph->loc[v].x, pgraph->loc[v].y);
        }
    }
    else
    {
            printf("0\n");
    }
    return 0;
}


PGraph generategraph()
{
    PGraph pgraph = new PGraph();
    pgraph->nv = cnum;
    for(int l1= 0; l1 < cnum; l1++)
    {
        pgraph->links[l1] = new node(l1, 0);
    }
    for(int l1 = 0; l1 < cnum; l1++)
    {
        cin >> pgraph->loc[l1].x >> pgraph->loc[l1].y;
    }
    resetgraphcompletes(pgraph);
    return pgraph;
}
void updateconnections(PGraph pgraph)
{
    for(Vertex v = 0; v < pgraph->nv; v++)
    {
        for(Vertex w = v + 1; w < pgraph->nv; w++)
        {
            if(isConnected(pgraph->loc[v], pgraph->loc[w],maxdis))
            {
                addedge(pgraph, v, w, dis);
            }
        }
    }
}

bool isConnected(pos loc1, pos loc2, double &dis, double thdis)
{
    dis = getdis(loc1, loc2);
    if(dis > thdis)
        return false;
    else
        return true;
}

void addedge(PGraph pgraph, Vertex v1, Vertex v2, double dis)
{
    PNode node2(v2, dis);
    node2->next = pgraph->links[v1]->next;
    pgraph->links[v1] = node2;
    
    PNode node1(v1, dis);
    node1->next = pgraph->links[v2]->next;
    pgraph->links[v2] = node1;
}

bool isSafe(pos loc, double &dis)
{

    if((50-loc.x)<=maxdis)
    {
        dis = 50-loc.x;
        return true;
    }
    if((loc.x+50)<=maxdis)
    {
        dis = loc.x+50;
        return true;
    }
    if((50-loc.y)<=maxdis)
    {
        dis = 50-loc.y;
        return true;
    }
    if((loc.y+50)<=maxdis)
    {
        dis = loc.y+50;
        return true;
    }
    return false;
}


double getdis(pos loc1, pos loc2)
{
    return sqrt((loc1.x-loc2.x)*(loc1.x-loc2.x)+(loc1.y-loc2.y)*(loc1.y-loc2.y));
}


struct CmpByDis
{
    bool operator()(const double& d1, const double& d2)
    {
        return d1<=d2;
    }
};

bool getfirst(PGraph pgraph, vector<Vertex> & vfirsts)
{
    pos c(0,0);
    double dis;
    map<Vertex, double, CmpByDis> dismap;
    for(Vertex v = 0; v < pgraph->nv; v++)
    {
        if(isConnected(c,pgraph->loc[v],dis,maxdis+ISLAND_RADIUS))
        {
            dismap.insert(make_pair(v,dis));
        }
    }
    for(auto mit:dismap)
    {
        vfirsts.push_back(mit.first);
        pgraph->links[mit.first] = mit.second;
    }
    if(vfirsts.empty())
        return false;
    else
        return true;
}

double dmethod(PGraph pgraph, Vertex v, vector<Vertex>& vexits)
{
    vector<double> vdis(pgraph->nv, DOUBLE_MAX);
    vector<Vertex> vpath(pgraph->nv, -1);
    PNode neighbor = pgraph->links[v]->next;
    pos floc = pgraph->loc[v];
    pgraph->completes[v] = true;
    double lastdis;
    PHeap pheap;
    pheap = create();
    addtoheap(pheap, v, 0);
    
    if(isSafe(floc, lastdis))
    {
        vexits.push_back(v);
        return pgraph->links[v].dis+lastdis;
    }
    while(!neighbor||)
    {
        
        Vertex w = neighbor->v;
        if(pgraph->completes[w] == false)
        {
            pgraph->completes[w] = true;
            
        }
    }
}

void resetgraphcompletes(PGraph pgraph)
{
    memset(pgraph->completes, 0, pgraph->nv*sizeof(bool));
}

PHeap create()
{
    PHeap pheap = new minheap();
    pheap->size = 0;
    pheap->D[0] = data(0,DOUBLE_MIN);
}
void addtoheap(PHeap pheap, Vertex v, double val)
{
    Vertex i = ++pheap->size;
    for(;pheap->D[i/2].dist>pheap->D[i].dist;i = i/2)
    {
        pheap->D[i] = pheap->D[i/2];
    }
    pheap->D[i] = data(v, val);
}
data deleteheap(PHeap pheap)
{
    data dtop = pheap->D[1];
    data tmp = pheap->D[pheap->size--];
    Vertex parent;
    Vertex child;
    for(parent = 1; 2*parent<=pheap->size; parent = child)
    {
        child = 2 * parent;
        if(child != pheap->size && pheap->D[child].dist > pheap->D[child+1].dist)
        {
            child ++;
        }
        if(tmp<pheap->D[child])
            break;
        else
            pheap->D[parent] = pheap->D[child];
        pheap->D[parent] = tmp;
    }
    return dtop;
}
















