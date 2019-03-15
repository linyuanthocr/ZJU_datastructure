#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int num;
    cin >> num;
    vector<int> vin;
    vin.resize(num);
    for(int l1 = 0; l1 < num; l1++)
    {
        cin >> vin[l1];
    }
    sort(vin.begin(),vin.end());
    for(int l1 = 0; l1 < num-1; l1++)
        printf("%d ", vin[l1]);
    printf("%d\n", vin[num-1]);
    return 0;
}
