#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;
struct polynode
{
    int coff;
    int expo;
    polynode(int c, int e) {coff = c; expo = e;}
};

bool compare(const polynode& st1,const polynode& st2)
{
    return st1.expo > st2.expo;
}

void printlist(unordered_map<int, int> res)
{
    if(res.empty())
    {
        printf("0 0\n");
        return;
    }
    vector<polynode> vres;
    for(auto it = res.begin(); it != res.end(); ++it)
    {
        if(it->second != 0)
            vres.push_back(polynode(it->second, it->first));
    }
    if(vres.empty())
    {
        printf("0 0\n");
        return;
    }
    sort(vres.begin(),vres.end(),compare);
    for(int l1 = 0; l1 < vres.size(); l1++)
    {
        printf("%d %d ", vres[l1].coff, vres[l1].expo);
    }
    printf("\n");
}

int main()
{
    // read inputs:
    int n1 = 0;
    cin>>n1;
    vector<polynode> vpfirst;
    int c = 0;
    int e = 0;
    for(int l1 = 0; l1 < n1; l1++)
    {
        cin >> c >> e;
        vpfirst.push_back(polynode(c,e));
    }
    int n2 = 0;
    cin>>n2;
    vector<polynode> vpsecond;
    for(int l1 = 0; l1 < n2; l1++)
    {
        cin >> c >> e;
        vpsecond.push_back(polynode(c,e));
    }
    
    // multiple
    unordered_map<int, int> mulres;
    for(int l1 = 0; l1 < n1; l1++)
    {
        for(int l2 = 0; l2 < n2; l2++)
        {
            int rese = vpfirst[l1].expo+vpsecond[l2].expo;
            int resc = vpfirst[l1].coff*vpsecond[l2].coff;
            if(mulres.empty()||mulres.find(rese)==mulres.end())
            {
                mulres.insert(make_pair(rese, resc));
            }
            else
            {
                mulres[rese] += resc;
            }
        }
    }
    
    printlist(mulres);
    
    // sum
    unordered_map<int, int> addres;
    for(int l1 = 0; l1 < n1; l1++)
    {
        int rese = vpfirst[l1].expo;
        int resc = vpfirst[l1].coff;
        addres.insert(make_pair(rese, resc));
    }
    for(int l2 = 0; l2 < n2; l2++)
    {
        int rese = vpsecond[l2].expo;
        int resc = vpsecond[l2].coff;
        if(addres.empty()||addres.find(rese)==addres.end())
        {
            addres.insert(make_pair(rese, resc));
        }
        else
        {
            addres[rese] += resc;
        }
    } 
    
    printlist(addres);
    
    return 0;
}
