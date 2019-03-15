#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
using namespace std;

struct TreeNode
{
    int data;
    TreeNode* left;
    TreeNode* right;
    int height;
    TreeNode(int val) {data = val; left = NULL; right = NULL; height = 0;}
};

TreeNode *insert(TreeNode *T, int val);
TreeNode *RRAVL(TreeNode*a);
TreeNode *RLAVL(TreeNode*a);
TreeNode *LLAVL(TreeNode*a);
TreeNode *LRAVL(TreeNode*a);

int height(TreeNode* P);
int MAX(int x,int y);

int main()
{
    int num = 0;
    cin >> num;
    int val = 0;
    TreeNode *T = NULL;
    for(int l1 = 0; l1 < num; l1++)
    {
        cin >> val;
        //printf("Get num %d, begin insert...\n", val);
        T = insert(T, val);
        //printf("Insert num %d done !! Tree height is %d\n", val, T->height);
    }
    if(T)
        printf("%d\n", T->data);
    else
        printf("0\n");
    return 0;
}

TreeNode *insert(TreeNode *T, int val)
{
    if(!T)
    {
        T = new TreeNode(val);
    }
    else
    {
        if(val < T->data)
        {
            T->left = insert(T->left, val);
            if(height(T->left)-height(T->right)==2)
            {
                if(val<T->left->data)
                {
                    T = LLAVL(T);
                }
                else
                {
                    T = LRAVL(T);
                }
            }
        }
        else
        {
            T->right = insert(T->right, val);
            if(height(T->right)-height(T->left)==2)
            {
                if(val>T->right->data)
                {
                    T = RRAVL(T);
                }
                else
                {
                    T = RLAVL(T);
                }
            }
        }
    }
    T->height = MAX(height(T->left), height(T->right)) + 1;
    //printf("Insert %d\n", T->data);
    return T;
}

int height(TreeNode *P)
{
    if(P==NULL)
        return -1;
    return P->height;
}

TreeNode *LLAVL(TreeNode *a)
{
    //printf("Begin LLAVL\n");
    TreeNode *b = a->left;
    a->left = b->right;
    b->right = a;
    //printf("LLAVL process height ..\n");
    a->height = MAX(height(a->left), height(a->right))+1;
    b->height = MAX(height(b->left), height(b->right))+1;
    //printf("End LLAVL\n");
    return b;
    
}

TreeNode *RRAVL(TreeNode *a)
{
    //printf("Begin RRAVL\n");
    TreeNode *b = a->right;
    a->right = b->left;
    b->left = a;
    a->height = MAX(height(a->left), height(a->right))+1;
    b->height = MAX(height(b->left), height(b->right))+1;
    //printf("End RRAVL\n");
    return b;
}

TreeNode *RLAVL(TreeNode *a)
{
    //printf("Begin RLAVL\n");
    TreeNode *b = a->right;
    TreeNode *bl = b->left;
    TreeNode *bll = bl->left;
    TreeNode *blr = bl->right;
    a->right = bll;
    bl->left = a;
    b->left = blr;
    bl->right = b;
    a->height = MAX(height(a->left), height(a->right))+1;
    b->height = MAX(height(b->left), height(b->right))+1;
    bl->height = MAX(a->height, b->height)+1;
    //printf("End RLAVL\n");
    return bl;
}


TreeNode *LRAVL(TreeNode *a)
{
    //printf("Begin LRAVL\n");
    TreeNode *b = a->left;
    TreeNode *br = b->right;
    TreeNode *brl = br->left;
    TreeNode *brr = br->right;
    a->left = brr;
    br->right = a;
    b->right = brl;
    br->left = b;
    a->height = MAX(height(a->left), height(a->right))+1;
    b->height = MAX(height(b->left), height(b->right))+1;
    br->height = MAX(a->height, b->height)+1;
    //printf("End LRAVL\n");
    return br;
}

int MAX(int x,int y)
{
    return x>y?x:y;
}
