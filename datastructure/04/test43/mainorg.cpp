#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct TreeNode
{
    int id;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int val){id = val; left = NULL; right = NULL;}
};

TreeNode *constructCBSTree(TreeNode* T, int num);
void printTree(vector<int> &vdata, TreeNode* T);
int calid(int totalnum, int &leftnum, int &rightnum, int &baseid);

int main()
{
    int num = 0;
    cin >> num;
    int val = 0;
    vector<int> vdata;
    for(int l1 = 0; l1 < num; l1 ++)
    {
        cin >> val;
        vdata.push_back(val);
    }
    sort(vdata.begin(),vdata.end());
    TreeNode *T = NULL;
    constructCBSTree(T, num);
    printTree(v, T);
    return 0;
}

void printTree(vector<int> &vdata, TreeNode* T)
{
    if(!T)
    {
        printf("\n");
        return;
    }
    queue<int> qtree;
    vector<int> res;
    qtree.push(T);
    int item = 0;
    while(!qtree.empty())
    {
        item = qtree.front();
        qtree.pop();
        if(item->left)
            qtree.push(item->left);
        if(item->right)
            qtree.push(item->right);
        res.push_back(vdata[item->data]);
    }
    for(int l1 = 0; l1 < res.size()-1; l1++)
    {
        printf("%d ", res[l1]);
    }
    printf("%d\n", res[res.size()-1]);
}

TreeNode *constructCBSTree(TreeNode* T, int num)
{
    
}



















