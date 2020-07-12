#include <iostream>
#include <fstream>
#include <stdint.h>
#include <stdlib.h>
#include <vector>
#include<cstdlib>
#include <string>
#include <ctime>
using namespace std;
const int d = 5;
const int w = 2000;
const int p=11981;
int main(int argc,char* argv[]) {
  clock_t start, end;
  fstream fin,fq,fout;
  srand(unsigned(time(NULL)));
  fq.open(argv[1]);
  fout.open("output_10000_1000.txt");
  fin.open("data_10000_1000.txt");
  if (fin.is_open() == false || fq.is_open()==false) {
    cout << "fin error";
    return 0;
  }
  vector<int> a(d, 0);
  vector<int> b(d, 0);
  int i, j, index,delta;
  for (i = 0; i < d; i++) {
    a[i] = rand();
    b[i] = rand();
    srand(unsigned(time(NULL)));
  }
  vector<vector<int> > hash(d, vector<int>(w, 0));
  start = clock();
  while (fin >> index >> delta) {
    for (i = 0; i < d; i++) {
      j = ((a[i] * index) % p + b[i] % p) % w;
      hash[i][j]+=delta;
    }
  }
  int query = 0;
  while (query<10) {
    int ans = 2147483647;
    for (i = 0; i < d; i++) {
      j = ((a[i] * query) % p + b[i] % p) % w;
      ans=min(ans,hash[i][j]);
    }
    fout >> i >> j;
    cout<<query<<":"<<ans-j<<endl;
    query++;
  }
  end = clock();
  fout.close();
  double totaltime = (double)(end-start) / CLOCKS_PER_SEC;
  cout << "run time is " << totaltime * 1000 << "ms" << endl;
}
