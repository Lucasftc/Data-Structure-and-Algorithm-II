#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include<set>
#include <map>
#include <ctime>
using namespace std;
map<int, int> m;
int main() {
  clock_t start, end;
  fstream fin, fdata;
  int N, k;
  string addr[]={"data_100_10.txt","data_10000_100.txt","data_100000_100.txt"};
  fin.open("in.txt");
  if (fin.is_open() == false) {
    exit(0);
  }
  fin >> N >> k;
  if (N == 100) {
    fdata.open(addr[0].c_str());
  } else if (N == 10000) {
    fdata.open(addr[1].c_str());
  } else {
    fdata.open(addr[2].c_str());
  }
  int i, temp;
  map<int, int>::iterator j;
  vector<int> q;
  start = clock();
  while(fdata>>temp) {
    if (m.find(temp) != m.end()) {
      m[temp]++;
      continue;
    }
    if (m.size() < k-1)
      m[temp] = 1;
    else {
      for ( j = m.begin(); j != m.end(); j++) {
        j->second--;
        if (j->second == 0)
          q.push_back(j->first);
      }
      while (q.empty() == false) {
          m.erase(q.back());
          q.pop_back();
      }

    }
  }
  //for (j = m.begin(); j != m.end();j++)
  //  cout << j->first << ":" << j->second<<endl;

    while (fin >> temp)
    {
      if (m.find(temp) == m.end())
        cout << "0" << endl;
      else
        cout << m[temp] << endl;
    }
    end = clock();
    double totaltime = (double)(end-start) / CLOCKS_PER_SEC;
    cout << "run time is " << totaltime * 1000 << "ms" << endl;
}