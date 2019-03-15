#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

struct Node
{
    int adrs;
    int data;
    int adrsnext;
    Node* next;
    Node(int ad, int d, int nx){adrs = ad; data = d;
        adrsnext = nx; next = NULL;}
    Node(){adrs = -1; data = -1; adrsnext = -1; next = NULL;}
    Node(vector<int> &v3){adrs = v3[0]; data = v3[1];
        adrsnext = v3[2]; next = NULL;}
};

typedef struct Node* List;

void printlist(vector<vector<int>>& vvdata, int num)
{
    for(int l1 = 0; l1 < num; l1++)
    {
        if(vvdata[l1][2] >=0)
            printf("%05d %d %05d\n", vvdata[l1][0], vvdata[l1][1], vvdata[l1][2]);
        else
            printf("%05d %d %d\n", vvdata[l1][0], vvdata[l1][1], vvdata[l1][2]);
    }
}

void printlist(List reslist, int num)
{
    List head = reslist;
    int n = 0;
    while(head != NULL && ++n<num)
    {
        printf("%05d %d %05d\n", head->adrs, head->data, head->next->adrs);
        head = head->next;
    }
    printf("%05d %d -1\n", head->adrs, head->data);
}

int main()
{
    int start_adrs=0;
    int k = 0;
    int num = 0;
    printf("I enter program!\n");
    cin >> start_adrs;
    cin >> num;
    cin >> k;
    printf("start address: %05d, number is %d, K is %d\n", start_adrs, num, k);
    vector<vector<int>> vvdata(num,vector<int>(3,0));
    unordered_map<int,int> umap;
    for(int l1 = 0; l1 < num; l1++)
    {
        cin>>vvdata[l1][0]>>vvdata[l1][1]>>vvdata[l1][2];
        umap.insert(make_pair(vvdata[l1][0],l1));
    }
    printf("Get numbers!\n");
    if(num<k||k<=1||num<=1)
    {
        printlist(vvdata, num);
        return 0;
    }
    printf("My list is as follows:\n");
    printlist(vvdata, num);
    List inputlist = new Node();
    List head = inputlist;
    int idnow = 0;
    while(start_adrs != -1)
    {
        auto it = umap.find(start_adrs);
        if(it == umap.end())
        {
            break;
        }
        idnow = it->second;
        List newpnode = new Node(vvdata[idnow]);
        inputlist->next = newpnode;
        inputlist = inputlist->next;
        start_adrs = vvdata[idnow][2];
    }
    printf("Generate list is done!\n");
    List pre = head;
    List cur = head->next;
    List nex = cur->next;
    int nleft = num;
    int nflip = 1;
    while(cur != NULL)
    {
        nex = cur->next;
        cur->next = nex->next;
        nex->next = pre->next;
        pre->next = nex;
        nflip++;
        if(nflip == k)
        {
            nleft -= k;
            if(nleft<k)
                break;
            pre = cur;
            if(cur->next == NULL)
                break;
            cur = cur->next;
            nflip = 1;
        }
        nleft--;
    }
    printlist(head->next, num);
    
    return 0;
}
