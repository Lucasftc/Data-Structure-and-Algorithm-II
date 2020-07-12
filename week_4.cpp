#include<iostream>
#include <time.h>
#include<vector>
#include<fstream>
#include<set>
#include<ctime>
using namespace std;
int prelong(vector<vector<int> > &g, int i, vector<int> &pal,vector<int>& visted){
    int j;
    for (j = 0; j < g[i].size();j++){
        if(visted[g[i][j]])
            continue;
        visted[g[i][j]] = 1;
        if(pal[g[i][j]]==-1 || prelong(g,pal[g[i][j]],pal,visted)){
            pal[i] = g[i][j];
            pal[g[i][j]] = i;
            return 1;
        }
    }
    return 0;
} 
int main(int argc,char* argv[])
{
    clock_t sta, end;
    int node, edge;
    int i,j;
    int sum = 0;
    fstream fin;
    fin.open(argv[1]);
    if(fin.is_open()==false){
        cout << "read in error";
        return 0;
    }
    fin >> node >> edge;
    vector<vector<int> > g(node);
    vector<int> pal(node,-1);
    vector<int> visted(node, 0);
    for (i = 0; i < edge;i++){
        int u, v;
        fin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    sta = clock();
    for (i = 0; i < node;i++)
        if(pal[i]==-1){
            for (j = 0; j < node;j++)
                visted[i] = 0;
            sum += prelong(g, i, pal, visted);
        }
    vector<int> single_neighbor(node, 0);
    for (i = 0; i < node;i++){
        if(pal[i]==-1)
            continue;
        for (j = 0; j < g[i].size();j++){
            if(pal[g[i][j]]==-1)
                single_neighbor[i]++;
        }
    }
    set<int> vc;
    for (i = 0; i < node;i++){
        if(pal[i]==-1)
            continue;
        if(vc.find(pal[i])!=vc.end() || vc.find(i)!=vc.end())
            continue;
        if(single_neighbor[i]>single_neighbor[pal[i]])
            vc.insert(i);
        else if (single_neighbor[i]<single_neighbor[pal[i]])
            vc.insert(pal[i]);
        else if(g[i].size()>=g[pal[i]].size())
            vc.insert(i);
        else
            vc.insert(pal[i]);
    }
    end = clock();
    double totaltime = (double)(end-sta) / CLOCKS_PER_SEC;
    cout << "run time is " << totaltime * 1000 << "ms" << endl;
    cout << "The size of independent set is" << node - vc.size() << endl;
    for (i = 0; i < node;i++)
        if(vc.find(i)==vc.end())
            cout << i << endl;
}