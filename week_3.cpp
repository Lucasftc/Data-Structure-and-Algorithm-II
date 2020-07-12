#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<ctime>
using namespace std;
const int N = 10000;
int dtime = 0;
int totalnode;
bool finish = false;
vector<vector<int> > g(N);
vector<int> visted(N,0);
vector<int> no(N, 0);
vector<int> findstart(N, 0);
vector<int> maxno(N, -1);
void dfs(int v,int end){
    no[v] = dtime;
    if(maxno[v]==-1)
        maxno[v] = dtime;
    else if (maxno[v]<dtime) {
        maxno[v] = dtime;
    }
    else {
        return;
    }
    if(v==end && dtime!=totalnode-1)
        return;
    if(v==end && dtime == totalnode-1)
        finish = 1;
    for (int i = 0; i < g[v].size();i++){
        if(finish)
            return;
        if(visted[g[v][i]]==0){
            visted[g[v][i]] = 1;
            dtime++;
            dfs(g[v][i],end);
            visted[g[v][i]] = 0;
            dtime--;
        }        
    }
}
int main(int argv,char* argc[])
{
    clock_t begin,over;
    fstream fin;
    fin.open(argc[1]);
    if(fin.is_open()==false)
        exit(-1);
    int i,count=0;
    int u, v;
    int start, end;
    fin >> totalnode;
    while(fin>>u>>v){
        findstart[v] = 1;
        g[u].push_back(v);
    }
    begin = clock();
    for (i = 0; i < totalnode;i++){
        if(findstart[i]==0){
            start = i;
            count++;
        }
    }
    if(count!=1){
        cout << 0;
        return 0;
    }
    count = 0;
    for (i = 0; i < totalnode;i++){
        if(g[i].size()==0){
            end = i;
            count++;
        }
    }
    if(count!=1){
        cout << 0;
        return 0;
    }
    visted[start] = 1;
    dfs(start,end);
    double totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
    cout << "run time is " << totaltime * 1000 << "ms" << endl;
    if(finish==0){
        cout << 0;
        return 0;
    }
    cout << 1 << std::endl;
    over = clock();
    vector<int> ans(totalnode);
    for (i = 0; i < totalnode;i++)
        ans[no[i]] = i;
    for (i = 0; i < totalnode;i++)
        cout << ans[i] << "  ";
    cout << endl;
    
}

