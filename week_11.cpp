#include"MD5.h"
#include <bits/c++config.h>
#include <crtdefs.h>
#include <string>
#include<vector>
#include <set>
#include <ctime>
using namespace std;
const int K = 6;
class bit_vector{
  public:
    char *pch;
    size_t size;
    bit_vector(size_t _size);
    ~bit_vector();
    void add(int n);
    bool check(int n);
    void split(string raw);
    bool query(string raw);
};
bit_vector::bit_vector(size_t _size){
  size=_size;
  pch = new char[size];
  for (size_t i = 0; i < _size;i++)
    pch[i] = '\0';
}
bit_vector::~bit_vector(){
  delete[] pch;
}
void bit_vector::add(int n){
  int vi = n / 8;
  int vo = n % 8;
  pch[vi] |= (1 << vo);
}
bool bit_vector::check(int n){
  int vi = n / 8;
  int vo = n % 8;
  int mask = 1 << (vo);
  unsigned u = (unsigned)pch[vi];
  if(mask & u)
    return true;
  return false;
}
void bit_vector::split(string raw){
  int i, j;
  for (i = 0; i < K;i++){
    int sum = 0,weight=1;
    for (j = 4 * i; j < 4 * i + 4; j++){
      if(raw[j]>='0' && raw[j]<='9')
        sum += weight * (raw[j] - '0');
      else if(raw[j]>='a' && raw[j]<='f')
        sum += weight * (raw[j] - 'a' + 10);
      else
        cout << raw[j] << endl;
      weight *= 16;
    }
    add(sum%(size*8));
  }
}
bool bit_vector::query(string raw){
  int i, j;
  for (i = 0; i < K;i++){
    int sum = 0,weight=1;
    for (j = 4 * i; j < 4 * i + 4; j++){
      if(raw[j]>='0' && raw[j]<='9')
        sum += weight * (raw[j] - '0');
      else if(raw[j]>='a' && raw[j]<='f')
        sum += weight * (raw[j] - 'a' + 10);
      else
        cout << raw[j] << endl;
      weight *= 16;
    }
    if(!check(sum%(size*8)))
      return false;
  }
  return true;
}
int main(){
  fstream fin,fq,fa;
  fin.open("f10000.txt");
  fq.open("q10000.txt");
  fa.open("a10000.txt");
  if(fin.is_open()==false || fq.is_open()==false || fa.is_open()==false){
    cout << "error read in";
    exit(-1);
  }
  int i, j, ans, fp = 0, cnt = 0;
  string ch;
  clock_t start, end;
  start=clock();
  bit_vector b(10000);
  while(getline(fin,ch))
    b.split(getMD5(ch));
  while (getline(fq,ch)){
    fa >> ans;
    cout<<ch<<" "<<ans<<" "<<b.query(getMD5(ch))<<endl;
    if(ans==0 && b.query(getMD5(ch)))
      fp++;
  }
  end = clock();
  double totaltime = (double)(end-start) / CLOCKS_PER_SEC;
  cout << "run time is " << totaltime * 1000 << "ms" << endl;
  cout << fp;
}