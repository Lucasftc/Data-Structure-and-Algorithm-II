#include <functional>
#include <iostream>
#include<fstream>
#include <time.h>
#include <vector>
#include <string>
#include <algorithm>
#include<ctime>
using namespace std;
const int N=1138500;
clock_t start,finish;
vector<vector<int> > g(N);
int check_edge(string filename);
int triangle(string filename);
int main(int argc,char* argv[]) {
  int totalnode;
  int u, v;
  int i,j,k;
  fstream fin;
  fin.open(argv[1]);
  if (fin.is_open() == false)
  {
    cout << "can't open the graph file."<<endl;
    cout << argv[1];
    return 0;
  }
  fin >> totalnode;
  while (fin >> u >> v) {
    g[u].push_back(v);
    g[v].push_back(u);
  }
  for (i = 0; i < N; i++)
    std::sort(g[i].begin(), g[i].end());
  cout<<"read in "<<endl;
  start = clock();
  if(argv[2][0]=='2')
    check_edge(argv[3]);
  if(argv[2][0]=='3')
    triangle(argv[3]);
  finish = clock();
  double totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
  cout << "run time is " << totaltime * 1000 << "ms" << endl;
}
bool binary_search(int v1, int v2) {
  if (g[v1].size() == 0)
    return false;
  vector<int> a = g[v1];
  int middle = a.size() / 2;
  int left = 0, right = a.size() - 1;
  while (left < right) {
    if (a[middle] == v2)
      return true;
    else if (a[middle] < v2) {
      left = middle+1;
      middle = (left + right) / 2;
      continue;
    }
    else if (a[middle]> v2) {
      right = middle-1;
      middle = (left + right) / 2;
      continue;
    }
  }
  if (a[left] == v2 || a[right] == v2)
    return true;
  return false;
  

}
int check_edge(string filename) {
  fstream fin;
  fin.open(filename.c_str());
  if (fin.is_open() == false)
    return -1;
  int v1,v2;
  while (fin >> v1 >> v2) {
    if (binary_search(v1, v2) == true) {  
      cout << 1 << endl;
      return 1;
    } else {
      cout << 0 << endl;
      return 0;
    }
      
    }
}
int triangle(string filename) {
  fstream fin;
  int i=0,j=0,k;
  fin.open(filename.c_str());
  if (fin.is_open() == false)
    return -1;
  int v1, v2;
  while (fin >> v1 >> v2) {
    i = 0;
    j=0;
    cout<<v1<<" "<<v2<<endl;
    if (binary_search(v1, v2) == false)
      continue;
    while (i < g[v1].size() && j < g[v2].size()) {
      if (g[v1][i] == g[v2][j])
        {
        cout << g[v1][i] << endl;
        j++;
        i++;
      }
      if (g[v1][i] > g[v2][j])
        j++;
      if (g[v1][i] < g[v2][j])
        i++;
      }
            
      
    }
 


  
}
  

