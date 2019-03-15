#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#define MAXSIZE 10000
using namespace std;

struct setNode
{
    int *data;
    int size;
    setNode() {data = NULL; size = 0;}
};

setNode* connect(setNode* S, int l1, int l2);
void checkconnect(setNode* S, int l1, int l2);
int findroot(setNode*S, int val);
void getcomponents(setNode *S);
setNode* create(int num);
setNode* setunion(setNode *S, int root1, int root2);
int main()
{
    int num;
    cin >> num;
    setNode *pset = create(num);
    char copt;
    int c1, c2;
    do {
        cin >> copt;
        switch (copt) {
            case 'I':
                cin>>c1>>c2;
                pset = connect(pset, c1-1, c2-1);
                break;
            case 'C':
                cin>>c1>>c2;
                checkconnect(pset, c1-1, c2-1);
                break;
            case 'S':
                getcomponents(pset);
                break;
        }
    } while (copt != 'S');
    
    return 0;
}

setNode* create(int num)
{
    setNode * pset = new setNode();
    pset->data = new int[num];
    pset->size = num;
    for(int l1 = 0; l1 < num; l1++)
    {
        pset->data[l1] = -1;
    }
    return pset;
}

setNode* connect(setNode* S, int l1, int l2)
{
    int root1 = findroot(S, l1);
    int root2 = findroot(S, l2);
    if(root1 != root2)
        S = setunion(S, root1, root2);

    return S;
}

int findroot(setNode* S, int val)
{
    if(S->data[val]>=0)
        return S->data[val] = findroot(S,S->data[val]);
    else
        return val;
}

void checkconnect(setNode* S, int l1, int l2)
{
    int root1 = findroot(S, l1);
    int root2 = findroot(S, l2);
    if(root1 == root2)
        printf("yes\n");
    else
        printf("no\n");
}

void getcomponents(setNode *S)
{
    int num = 0;
    for(int l1 = 0; l1 < S->size; l1++)
    {
        //printf("data %d is %d\n", l1, S->data[l1]);
        if(S->data[l1]<0)
            num++;
    }
    if(num == 1)
        printf("The network is connected.\n");
    else
        printf("There are %d components.\n", num);
}

setNode* setunion(setNode *S, int root1, int root2)
{
    if(S->data[root1] < S->data[root2])
    {
        S->data[root1] += S->data[root2];
        S->data[root2] = root1;
    }
    else
    {
        S->data[root2] += S->data[root1];
        S->data[root1] = root2;
    }
    return S;
}

