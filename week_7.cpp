#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include<ctime>
#include <stdlib.h>
#include <vector>
using namespace std;
struct node {
  int no;
  double w;
  node(int _no=-1, double _w=0) {
    no = _no;
    w=_w;
  }
};
struct strip {
  int smallno;
  int largeno;
  double line;
  strip(int _smallno=-1, int _largeno=-1, double _line=0) {
    smallno = _smallno;
    largeno = _largeno;
    line=_line;
  }
};
int main(int argc,char* argv[]) {
  clock_t start,end;
  srand((int)time(NULL));
  fstream fin;
  fin.open(argv[1]);
  if (fin.is_open() == false) {
    cout << "read in error";
    exit(-1);
  }
  int N, k;
  int i, j;
  double standard;
  double epsilon = 0.000001;
  double W=0;
  fin >> N >> k;
  vector<node> v(N);
  list<node> large;
  list<node> small;
  for (i = 0; i < N; i++){
    fin >> v[i].no >> v[i].w;
    W += v[i].w;
  }
  start=clock();
  standard=((double)1) / ((double)N);
  for (i = 0; i < N; i++){
    v[i].w = v[i].w / W;
    if (v[i].w > standard)
      large.push_back(v[i]);
    else
      small.push_back(v[i]);
  }
  vector<strip> alias;
  while(small.empty()==false && large.empty()==false){
    strip temp;
    temp.smallno = small.front().no;
    temp.largeno = large.front().no;
    temp.line = small.front().w;
    large.front().w -= (standard-small.front().w);
    if(large.front().w<=epsilon){
      large.pop_front();
    }
    else if(large.front().w<=standard){
      small.push_back(node(large.front().no, large.front().w));
      large.pop_front();
    }
    small.pop_front();
    alias.push_back(temp);
  }
  while(large.empty()==false){
    strip temp;
    temp.smallno = -1;
    temp.largeno = large.front().no;
    temp.line = 0;
    large.front().w -= standard;
    if(large.front().w<=epsilon)
      large.pop_front();
    alias.push_back(temp);
  }
  end=clock();
  //for (i = 0;i<alias.size();i++)
  //  cout << alias[i].smallno << " " << alias[i].line << "  " << alias[i].largeno << endl;
  for (i = 0; i < k; i++) {
    
    int row = rand() % N;
    double col = ((double)(rand() % N)) / ((double)N);
    //cout<<"row:"<<row<<"col:"<<col<<"  ";
    if(col<alias[row].line)
      cout << alias[row].smallno << endl;
    else
      cout << alias[row].largeno << endl;
  }
  double totaltime = (double)(end-start) / CLOCKS_PER_SEC;
  cout << "run time is " << totaltime * 1000 << "ms" << endl;
}