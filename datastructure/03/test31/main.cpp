#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#define MAXSIZE 10
#define Null -1
typedef int Tree;

using namespace std;
struct TreeNode
{
    Tree left;
    Tree right;
    char data;
};
TreeNode T1[MAXSIZE];
TreeNode T2[MAXSIZE];

Tree generateTree(struct TreeNode T[], int &num);
bool isSimilar(Tree R1, Tree R2);
int main()
{
    Tree root1 = Null;
    Tree root2 = Null;
    int n1 = 0;
    int n2 = 0;
    root1 = generateTree(T1,n1);
    root2 = generateTree(T2,n2);
    if((n1==n2) && isSimilar(root1, root2))
    {
        cout<<"Yes"<<endl;
    }
    else
    {
        cout<<"No"<<endl;
    }
    return 0;
}

Tree generateTree(TreeNode *T, int &num)
{
//    printf("Loadding datas!!\n");
    Tree rootid = Null;
    num = 0;
    cin>>num;
//    printf("I get %d numbers!\n", num);
    int check[MAXSIZE];
    if(num)
    {
        char cl;
        char cr;
        for(int l1 = 0; l1 < num; l1++)
            check[l1]= 0;
        for(int l1 = 0; l1 < num; l1++)
        {
            cin >>T[l1].data>>cl>>cr;
            if(cl=='-')
            {
                T[l1].left = Null;
            }
            else
            {
                T[l1].left = cl - '0';
                check[T[l1].left] = 1;
            }
            
            if(cr=='-')
            {
                T[l1].right = Null;
            }
            else
            {
                T[l1].right = cr - '0';
                check[T[l1].right] = 1;
            }
//            printf("%c %d %d\n", T[l1].data, T[l1].left, T[l1].right);
        }
        for(int l1 = 0; l1 < num; l1++)
        {
            if(!check[l1])
            {
                rootid = l1;
                break;
            }
        }
    }
//    printf("Root is %d\n", rootid);
    return rootid;
}
bool isSimilar(Tree R1, Tree R2)
{
    if((R1 == Null) && (R2 == Null))
        return true;
    if((R1 == Null) && (R2 != Null))
        return false;
    if((R1 != Null) && (R2 == Null))
        return false;
    if(T1[R1].data != T2[R2].data)
        return false;
    if(T1[R1].left == Null && T2[R2].left == Null)
        return isSimilar(T1[R1].right, T2[R2].right);
    if((T1[R1].left != Null) && (T2[R2].left != Null) &&
       (T1[T1[R1].left].data == T2[T2[R2].left].data))
    {
        return isSimilar(T1[R1].left,T2[R2].left)&&
        isSimilar(T1[R1].right,T2[R2].right);
    }
    else
    {
        return isSimilar(T1[R1].left,T2[R2].right)&&
        isSimilar(T1[R1].right,T2[R2].left);
    }
}
