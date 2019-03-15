#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>    // std::sort

using namespace std;
int i = 0;
void generateCBST(int root, int num, vector<int> &vdata, vector<int> &b);

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
    vector<int> b(num+1,0);
    generateCBST(1, num, vdata, b);
    for(int l1 = 1; l1 < num; l1++)
    {
        printf("%d ", b[l1]);
    }
    printf("%d\n", b[num]);
    return 0;
}

void generateCBST(int root, int num, vector<int> &vdata, vector<int> &b)
{
    if(root<=num)
    {
        generateCBST(2*root, num, vdata, b);
        b[root] = vdata[i++];
        generateCBST(2*root+1, num, vdata, b);
    }
}
