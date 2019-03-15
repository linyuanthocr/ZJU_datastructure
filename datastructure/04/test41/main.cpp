#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;
struct TreeNode
{
    int data;
    bool flag;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int val) {data = val; left = NULL; right = NULL; flag = false;}
};

TreeNode* generateTree(int num);
void isSameTree(TreeNode* T, int num);
bool check(TreeNode*T, int val);
TreeNode* reset(TreeNode* T);
TreeNode* insert(TreeNode* T, int val);
TreeNode* deleteTree(TreeNode* T);

int main()
{
    int nnode = 0;
    cin>>nnode;
    int ntreenum = 0;
    while(nnode)
    {
        cin>>ntreenum;
        TreeNode *T = generateTree(nnode);
        for(int l1 = 0; l1 < ntreenum; l1++)
        {
            isSameTree(T, nnode);
            T = reset(T);
        }
        deleteTree(T);
        cin>>nnode;
    }
    return 0;
}

TreeNode* generateTree(int num)
{
    int val = 0;
    TreeNode* T = NULL;
    for(int l1 = 0; l1 < num; l1++)
    {
        cin>>val;
        T = insert(T, val);
    }
    return T;
}

TreeNode* insert(TreeNode* T, int val)
{
    if(!T)
    {
        T = new TreeNode(val);
        return T;
    }
    else
    {
        if(val<T->data)
        {
            T->left = insert(T->left, val);
        }
        else
        {
            T->right = insert(T->right, val);
        }
        return T;
    }
}

TreeNode* deleteTree(TreeNode* T)
{
    if(!T)
        return NULL;
    if(T->left)
        T->left = deleteTree(T->left);
    if(T->right)
        T->right = deleteTree(T->right);
    delete [] T;
    return NULL;
}

void isSameTree(TreeNode *T, int num)
{
    bool flag = false;
    int val = 0;
    for(int l1 = 0; l1 < num; l1++)
    {
        cin >> val;
        if(!flag && !check(T,val))
            flag = true;
    }
    if(flag)
        printf("No\n");
    else
        printf("Yes\n");
}

bool check(TreeNode*T, int val)
{
    if(T == NULL)
    {
        return false;
    }
    if(T->data == val && !T->flag)
    {
        T->flag = true;
        return true;
    }
    if(T->data == val && T->flag)
        return false;
    if(val < T->data)
    {
        if(T->flag)
            return check(T->left, val);
        else
            return false;
    }
    else
    {
        if(T->flag)
            return check(T->right, val);
        else
            return false;
    }
}

TreeNode* reset(TreeNode* T)
{
    if(T==NULL)
        return T;
    if(T->left)
        T->left = reset(T->left);
    if(T->right)
        T->right = reset(T->right);
    T->flag = false;
    return T;
}
