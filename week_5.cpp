#include<iostream>
#include <fstream>
#include <sstream>
#include<algorithm>
#include <string>
#include <time.h>
#include<vector>
#include<map>
#include<cstdio>
#include<algorithm>
#include<ctime>
using namespace std;
int main(int argc,char* argv[]) {
  fstream fin;
  clock_t start, end;
  string line;
  int nnode, nset;
  int i=0,j=0;
  fin.open(argv[1]);
  if (fin.is_open() == false)
    cout << "file open error";
  fin >> nnode >> nset;
  vector<vector<int> > cover(nset);
  vector<vector<int> > in(nnode);
  vector<bool>covered(nnode,false);
  vector<int> remain(nset);
  vector<int> ans;
  for (i = 0; i < nset; i++) {
    getline(fin,line);
    stringstream sin(line);
    int temp;
    while (sin >> temp) {
      cover[i].push_back(temp);
      in[temp].push_back(i);
      remain[i]++;
    }
  }
  start = clock();
  while (1) {
    int max = 0, max_no = -1;
    for (i = 0; i < nset;i++){
      if(remain[i]>max){
        max = remain[i];
        max_no = i;
      }
    }
    if(max<=0)
      break;
    ans.push_back(max_no);
    for (i = 0; i < cover[max_no].size(); i++) {
      if (covered[cover[max_no][i]])
        continue;
      covered[cover[max_no][i]]=true;
      for (j = 0; j < in[cover[max_no][i]].size(); j++) {
        remain[in[cover[max_no][i]][j]]--;
      }
    }
  }
  end=clock();
  double totaltime = (double)(end-start) / CLOCKS_PER_SEC;
  cout << "run time is " << totaltime * 1000 << "ms" << endl;
  cout << ans.size()<<endl;
  return 0;
  for (i = 0; i < ans.size(); i++) {
    for (j = 0; j < cover[ans[i]].size(); j++) {
      cout<<cover[ans[i]][j]<<" ";
    }
    cout<<endl;
  }
  
}