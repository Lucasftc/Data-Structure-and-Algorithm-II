#include<iostream>
#include<fstream>
#include <stdlib.h>
#include<vector>
#include<set>
#include<cstdlib>
#include<ctime>
using namespace std;
int main(int argc,char* argv[]){
    srand((int)time(NULL));
    fstream fin;
    fin.open("argv[1]");
    if(fin.is_open()==false)
        return 0;
    int n;
    clock_t start, end;
    fin >> n;
    set<int> ans;
    set<int>::iterator it;
    vector<vector<int> > g(n);
    vector<int> weight(n, 0);
    vector<int> state(n, 0);
    int i,j,k,u,v;
    while(fin>>u>>v){
        g[u].push_back(v);
        g[v].push_back(u);
    }
    start = clock();
    for (int pass = 1; pass < 30;pass++){
        srand(rand());
        for (i = 0; i < n;i++){
            weight[i] = rand();
            state[i] = 0;
        }
        while (1)
        {
            int flag = 0;
            for (i = 0; i < n; i++)
                if (state[i] == 0)
                    flag = 1;
            if (flag == 0)
                break;
            for (i = 0; i < n; i++)
            {
                if (state[i] == 1 || state[i] == -1)
                    continue;
                for (j = 0; j < g[i].size(); j++)
                {
                    if (state[g[i][j]] == 0 && weight[g[i][j]] > weight[i])
                        break;
                }
                if (j == g[i].size())
                {
                    state[i] = 1;
                    for (k = 0; k < g[i].size(); k++)
                        state[g[i][k]] = state[g[i][k]] == 0 ? -1 : state[g[i][k]];
                }
            }
        }
        int count = 0;
        for (i = 0; i < n;i++)
            if(state[i]==1)
                count++;
        if(count>ans.size()){
            ans.clear();
            for (i = 0; i < n;i++)
                if(state[i]==1)
                    ans.insert(i);
        }
    }
    end = clock();
    double totaltime = (double)(end-start) / CLOCKS_PER_SEC;
    cout << "run time is " << totaltime * 1000 << "ms" << endl;
    cout << ans.size();
    //for ( it = ans.begin(); it != ans.end();it++)
    //    cout << *it<<" ";
}
