#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX_NUM 5

class PTAscore
{
public:
    PTAscore();
    ~PTAscore();
    void init();
    void printf_results();
private:
    int _h_num;
    int _p_num;
    int _s_num;
    vector<vector<int>> totalscore;
    vector<vector<int>> scoremat;
    vector<int> fullscore;
    void generate_rank();
};

int main()
{
    PTAscore ptas;
    ptas.init();
    ptas.printf_results();
    return 0;
}


PTAscore::PTAscore()
{
    _h_num = 0;
    _p_num = 0;
}

PTAscore::~PTAscore()
{
    if(!totalscore.empty())
    {
        vector<vector<int>>(0,vector<int>()).swap(totalscore);
    }
    if(!scoremat.empty())
    {
        vector<vector<int>>(0,vector<int>()).swap(scoremat);
    }
    if(!fullscore.empty())
    {
        vector<int>().swap(fullscore);
    }
}

void PTAscore::init()
{
    cin>>_h_num>>_p_num>>_s_num;
    totalscore = vector<vector<int>>(_h_num,vector<int>(3,-1));
    for(int l1 = 0; l1 < _h_num; l1++)
    {
        totalscore[l1][0] = 0;
        totalscore[l1][1] = l1;
    }
    fullscore = vector<int>(_p_num,0);
    scoremat = vector<vector<int>>(_h_num,vector<int>(_p_num,-1));
    for(int i = 0; i < _p_num; i++)
    {
        cin>>fullscore[i];
    }
    int hid,pid,score,diff;
    for(int i = 0; i < _s_num; i++)
    {
        cin>>hid>>pid>>score;
        diff = score-max(0,scoremat[hid-1][pid-1]);
        if(diff>=0)
        {
            scoremat[hid-1][pid-1] = score;
            totalscore[hid-1][0] += diff;
        }
    }
//    printf_results();
//    printf("$$$$$$$$$$$$$$$$$$$$\n");
    sort(totalscore.rbegin(),totalscore.rend());
//    printf_results();
//    printf("####################\n");
    generate_rank();
}

void PTAscore::printf_results()
{
    int id;
    for(int l1 = 0; l1 < _h_num; l1++)
    {
        if(totalscore[l1][0]<=0)
            return;
        printf("%d %05d %d ", totalscore[l1][2], totalscore[l1][1]+1, totalscore[l1][0]);
        id = totalscore[l1][1];
        for(int i = 0; i < _p_num-1; i++)
        {
            if(scoremat[id][i]<0)
                printf("- ");
            else
                printf("%d ",scoremat[id][i]);
        }
        if(scoremat[id][_p_num-1]<0)
            printf("-\n");
        else
            printf("%d\n",scoremat[id][_p_num-1]);
        
    }
}

void PTAscore::generate_rank()
{
    int nrank = 1;
    totalscore[0][2] = nrank;
    for(int l1 = 1; l1 < _h_num; l1++)
    {
        if(totalscore[l1][0]==totalscore[l1-1][0])
        {
            totalscore[l1][2] = nrank;
        }
        else
        {
            totalscore[l1][2] = ++nrank;
        }
    }
}
