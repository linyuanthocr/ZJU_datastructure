#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <map>
#include <vector>

#define MAXSIZE 50

using namespace std;

struct Treenode
{
    char c;
    Treenode* left;
    Treenode* right;
    Treenode(){
        c = '\0';
        left = NULL;
        right = NULL;
    }
    Treenode(char ch)
    {
        c = ch;
        left = NULL;
        right = NULL;
    }
};

typedef Treenode* Tree;
map<char,int> inmap;
int calheight(Tree mytree);
Tree generateTree(vector<char>&vpreorder, int preid, int istart, int iend);

int main()
{
    int num;
    cin >> num;
    vector<char> vpreorder(num,0);
    vector<char> vinorder(num,0);
    for(int l1 = 0; l1 < num; l1++)
    {
        cin>>vpreorder[l1];
    }
    for(int l1 = 0; l1 < num; l1++)
    {
        cin>>vinorder[l1];
        inmap[vinorder[l1]] = l1;
    }
    Tree mytree = NULL;
    mytree =  generateTree(vpreorder, 0, 0, num-1);
    int height = calheight(mytree);
    printf("%d\n",height);
    return 0;
}

Tree generateTree(vector<char>&vpreorder, int preid, int istart, int iend)
{
    if(istart>iend)
        return NULL;
    char c = vpreorder[preid];
    auto it = inmap.find(c);
    if(it == inmap.end())
        return NULL;
    int pos = it->second;
    Treenode *root = new Treenode(c);
    root->left = generateTree(vpreorder, preid+1, istart, pos-1);
    root->right = generateTree(vpreorder, preid+1+pos-istart, pos+1, iend);
    return root;
}

int calheight(Tree mytree)
{
    if(mytree==NULL)
        return 0;
    int left = calheight(mytree->left);
    int right = calheight(mytree->right);
    return max(left,right)+1;
}


















