#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <queue>
#include <vector>
#include <string>

#define MAXSIZE 10
#define Null -1
using namespace std;

typedef int Tree;

struct TreeNode
{
    Tree left;
    Tree right;
};

Tree loadtree(TreeNode *tree, int &num);
void printleaves(TreeNode *tree, Tree rootid, int num);

int main()
{
    TreeNode mytree[MAXSIZE];
    int num = 0;
    Tree rtid = loadtree(mytree, num);
    printleaves(mytree, rtid, num);
    return 0;
}

Tree loadtree(TreeNode *tree, int &num)
{
    Tree troot = Null;
    num = 0;
    cin>>num;
    char cl;
    char cr;
    bool check[MAXSIZE];
    memset(check, 0 , sizeof(bool)*MAXSIZE);
    for(int l1 = 0; l1 < num; l1++)
    {
        cin>>cl>>cr;
        if(cl =='-')
        {
            tree[l1].left = Null;
        }
        else
        {
            tree[l1].left = cl - '0';
            check[tree[l1].left] = true;
        }
        
        if(cr =='-')
        {
            tree[l1].right = Null;
        }
        else
        {
            tree[l1].right = cr - '0';
            check[tree[l1].right] = true;
        }
    }
    for(int l1 = 0; l1 < num; l1++)
    {
        if(!check[l1])
        {
            troot = l1;
            break;
        }
    }
    return troot;
}

void printleaves(TreeNode *tree, Tree rootid, int num)
{
    queue<Tree> qtree;
    vector<Tree> leaves;
    if(rootid == Null || num == 0)
    {
        printf("\n");
        return;
    }
    qtree.push(rootid);
    
    while(!qtree.empty())
    {
        int qtop = qtree.front();
        qtree.pop();
        if(tree[qtop].left != Null)
            qtree.push(tree[qtop].left);
        if(tree[qtop].right != Null)
            qtree.push(tree[qtop].right);
        if(tree[qtop].left == Null && tree[qtop].right==Null)
            leaves.push_back(qtop);
    }
    for(int l1 = 0; l1 < leaves.size()-1; l1++)
    {
        printf("%d ", leaves[l1]);
    }
    printf("%d\n", leaves[leaves.size()-1]);
}





































