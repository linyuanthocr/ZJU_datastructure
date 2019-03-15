#include <stdlib.h>
#include <stdio.h>
#include <stack>
#include <queue>
#include <iostream>
#include <vector>
#include <string>

#define MAXSIZE 30
using namespace std;
typedef int Tree;
struct TreeNode
{
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) {data = val; left = NULL; right = NULL;}
};
TreeNode* generateTree();
void printPostTraverse(TreeNode*T);

int main()
{
    TreeNode* mytree = NULL;
    int num = 0;
    mytree = generateTree();
    printPostTraverse(mytree);
    return 0;
}

TreeNode* generateTree()
{
    int num = 0;
    cin >> num;
    string temp;
    Tree pushid;
    Tree popid;
    stack<TreeNode*> stree;
    string spush("Push");
    bool bgetroot = false;
    TreeNode* root = NULL;
    TreeNode* father = NULL;
    bool islastoppop = false;
    for(int l1 = 0; l1 < num*2; l1++)
    {
        cin>>temp;
        if(temp == spush)
        {
            cin >> pushid;
            TreeNode* tnode = new TreeNode(pushid);
            if(!bgetroot)
            {
                root = tnode;
                bgetroot = true;
            }
            else
            {
                if(!islastoppop)
                {
                    father = stree.top();
                }
                if(father->left == NULL)
                    father->left = tnode;
                else
                    father->right = tnode;
            }
            stree.push(tnode);
            islastoppop = false;
        }
        else
        {
            father = stree.top();
            stree.pop();
            islastoppop = true;
        }
    }
    return root;
}

void printPostTraverse(TreeNode*T)
{
    stack<TreeNode*> stree;
    vector<int> res;
    stree.push(T);
    TreeNode* cur = NULL;
    TreeNode* pre = NULL;
    while(!stree.empty())
    {
        cur = stree.top();
        if((cur->left == NULL&&cur->right==NULL)||(pre!=NULL&&(pre==cur->left||pre==cur->right)))
        {
            res.push_back(cur->data);
            stree.pop();
            pre = cur;
        }
        else
        {
            if(cur->right != NULL)
                stree.push(cur->right);
            if(cur->left != NULL)
                stree.push(cur->left);
        }
    }
    for(int l1 = 0; l1 < res.size()-1; l1++)
    {
        printf("%d ", res[l1]);
    }
    printf("%d\n", res[res.size()-1]);
}
