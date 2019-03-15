#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <float.h>
#include <math.h>
#include <map>
#include <string.h>
#include <stack>


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
    pos(){x = 0; y = 0;}
    pos(int x0, int y0) {x = x0; y = y0;}
};

struct graph
{
    int nv;
    int ne;
    PNode links[MAXSIZE];
    pos loc[MAXSIZE];
    double firstjump[MAXSIZE];
    bool completes[MAXSIZE];
    graph(){nv = 0; ne = 0;}
};

typedef graph* PGraph;

PGraph generategraph();
void updateconnections(PGraph pgraph);
void addedge(PGraph pgraph, Vertex v1, Vertex v2, double dis);
bool getfirst(PGraph pgraph, vector<Vertex> & vfirsts);
Vertex findmindist(PGraph pgraph, vector<double>&dist);
double dmethod(PGraph pgraph, Vertex firstid, vector<Vertex>& vexits);
bool isSafe(pos loc, double &dis);
bool isConnected(pos loc1, pos loc2, double &dis, double thdis);
double getdis(pos loc1, pos loc2);
void resetgraphcompletes(PGraph pgraph);

int main()
{
    cin >> cnum;
    cin >> maxdis;
    PGraph pgraph = generategraph();
    //printf("S1\n");
    updateconnections(pgraph);
    //printf("S2\n");
    vector<Vertex> vfirsts;
    vector<vector<Vertex>> vvexits;
    bool bgetf = getfirst(pgraph, vfirsts);
    //printf("S3\n");
    if(!bgetf)
    {
        printf("0\n");
        return 0;
    }
    if(maxdis>50-ISLAND_RADIUS)
    {
        printf("1\n");
        return 0;
    }
    vvexits.resize(vfirsts.size());
    double mindist = DBL_MAX;
    double locdist = DBL_MAX;
    int selectid = -1;
    for(int l1 = 0; l1 < vfirsts.size(); l1++)
    {
        locdist = dmethod(pgraph, vfirsts[l1], vvexits[l1]);
        if(locdist<mindist)
        {
            mindist = locdist;
            selectid = l1;
            //printf("mindist = %f, selectid = %d\n", mindist, selectid);
        }
        resetgraphcompletes(pgraph);
        //printf("S4\n");
    }
    if(locdist < DBL_MAX)
    {
        int nexit = vvexits[selectid].size();
        printf("%d\n",nexit+1);
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
    PGraph pgraph = new graph();
    pgraph->nv = cnum;
    for(int l1 = 0; l1 < cnum; l1++)
    {
        pgraph->links[l1] = NULL;
        cin >> pgraph->loc[l1].x >> pgraph->loc[l1].y;
        pgraph->firstjump[l1] = DBL_MAX;
    }
    resetgraphcompletes(pgraph);
    return pgraph;
}
void updateconnections(PGraph pgraph)
{
    double dis;
    for(Vertex v = 0; v < pgraph->nv; v++)
    {
        for(Vertex w = v + 1; w < pgraph->nv; w++)
        {
            if(isConnected(pgraph->loc[v], pgraph->loc[w], dis, maxdis))
            {
                addedge(pgraph, v, w, dis);
                ////printf("Add edge between %d and %d\n", v,w);
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
    PNode node2 = new node(v2, dis);
    node2->next = pgraph->links[v1];
    pgraph->links[v1] = node2;
    
    PNode node1 = new node(v1, dis);
    node1->next = pgraph->links[v2];
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

typedef pair<Vertex,double> PAIR;

bool paircmp(const PAIR& x, const PAIR& y)
{
    return x.second < y.second;
}

void sortMapByValue(map<Vertex, double>& tMap,vector<PAIR>& tVector)
{
    for (map<Vertex, double>::iterator curr = tMap.begin(); curr != tMap.end(); curr++)
        tVector.push_back(make_pair(curr->first, curr->second));
    
    sort(tVector.begin(), tVector.end(), paircmp);
}

bool getfirst(PGraph pgraph, vector<Vertex> & vfirsts)
{
    pos c(0,0);
    double dis;
    map<Vertex, double> dismap;
    for(Vertex v = 0; v < pgraph->nv; v++)
    {
        if(isConnected(c,pgraph->loc[v],dis,maxdis+ISLAND_RADIUS))
        {
            dismap.insert(make_pair(v,dis));
        }
    }
    vector<PAIR> tVector;
    sortMapByValue(dismap, tVector);
    for(auto it:tVector)
    {
        vfirsts.push_back(it.first);
        pgraph->firstjump[it.first] = it.second;
    }
    if(vfirsts.empty())
        return false;
    else
        return true;
}

Vertex findmindist(PGraph pgraph, vector<double>&dist)
{
    Vertex minv, v;
    double mindist = DBL_MAX;
    for(v = 0; v < pgraph->nv; v++)
    {
        if(pgraph->completes[v]==false && dist[v]<mindist)
        {
            mindist = dist[v];
            minv = v;
        }
    }
    if (mindist < DBL_MAX)
    {
        return minv;
    }
    else
        return -1;
}

double dmethod(PGraph pgraph, Vertex v, vector<Vertex>& vexits)
{
    vector<double> vdis(pgraph->nv, DBL_MAX);
    vector<Vertex> vpath(pgraph->nv, -1);
    PNode neighbor = pgraph->links[v];
    pos floc = pgraph->loc[v];
    ////printf("set neibor of %d\n", v);
    double lastdis;
    Vertex w;
    while(neighbor)
    {
        w = neighbor->d.v;
        ////printf("get neibor input %d\n", w);
        vdis[w] = 1;
        vpath[w] = v;
        neighbor = neighbor->next;
        ////printf("neibor input %d, dis %f\n", w, vdis[w]);
    }
    vdis[v] = 0;
    pgraph->completes[v] = true;
    vexits.push_back(v);
    stack<Vertex> spath;
    Vertex s = v;
    ////printf("enter D!\n");
    double firstjump = pgraph->firstjump[v];
    while(1)
    {
        v = findmindist(pgraph, vdis);
        ////printf("vdismin vertex %d\n",v);
        if(v == -1)
            break;
        pgraph->completes[v] = true;
        floc = pgraph->loc[v];
        if(isSafe(floc, lastdis))
        {
            double exitdis = vdis[v];
            while(v!=s)
            {
                spath.push(v);
                v = vpath[v];
            }
            while(!spath.empty())
            {
                s = spath.top();
                spath.pop();
                vexits.push_back(s);
            }
            return 1+exitdis+1;
        }
        neighbor = pgraph->links[v];
        while (neighbor) {
            w = neighbor->d.v;
            if(pgraph->completes[w]==false)
            {
                if(vdis[v]+1<vdis[w])
                {
                    vdis[w] = vdis[v]+1;
                    vpath[w] = v;
                    ////printf("vpath from %d to %d\n", v, w);
                }
            }
            neighbor = neighbor->next;
        }
    }
    return DBL_MAX;
}

void resetgraphcompletes(PGraph pgraph)
{
    memset(pgraph->completes, 0, pgraph->nv*sizeof(bool));
}

















