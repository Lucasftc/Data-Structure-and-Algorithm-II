#include<string>
#include <iostream>
#include<sstream>
#include<fstream>
#include<set>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "MD5.h"
using namespace std;

class LSH{
private:
    const int doc = 39861; /*39861;*/
    const int dic = 28102;
    const int arrange_n = 100;
    const int band = 20;
    const int row=5;
    const int hashroom=1835811;
    int bucket_cnt;
    string filename;
    vector<vector<bool>> shingle;// store the shingle of one document
    vector<unsigned short> bucket_no;//a projection from docid to bucketid
    vector<vector<unsigned short> > bucket;//store the bucket content
    vector<unsigned short> h;//hash table
    vector<vector<string> > test;
    vector<vector<unsigned short> > sig;//signatrue of all document
    vector<vector<unsigned short> > arrange;
public:
    LSH(string _filename);
    int myhash(string raw);
    void permution();
    void signature();
    void local_sensitive();
    void show_bucket();
};
LSH::LSH(string _filename):shingle(doc+1, vector<bool>(dic,false)),bucket_no(doc+1, -1),h(hashroom,-1),
sig(doc+1, vector<unsigned short>(arrange_n, 0)),arrange(arrange_n,vector<unsigned short>(dic, 0)){
    srand(time(NULL));
    filename = _filename;
}
//receive a contataion string as a document
//get its hash value
int LSH::myhash(string raw) {
  int ans = 0;
  int i;
  string code = getMD5(raw);
  for (i = 0; i < code.size(); i++)
    ans=(ans*131+(int)(code[i]))%hashroom;
  return ans;
}
// generate random permutation
void LSH::permution(){
    int i, j;
    for (i = 0; i < arrange_n; i++) 
        for (j = 0; j < dic; j++)
            arrange[i][j]=j;
    for (i = 0; i < arrange_n; i++)
        for (j = 0; j < dic; j++)
            swap(arrange[i][j], arrange[i][rand() % (j + 1)]);
}
void LSH::signature(){
    fstream fin;
    int i, j, k;
    fin.open(filename);
    if (fin.is_open() == false) {
        cout << "read in error" << endl;
    }
    int docid, wordid, cnt;
        while (fin >> docid >> wordid >> cnt) {
        shingle[docid-1][wordid]=true;
        }
    for (i = 0; i <= doc; i++){
        for (j = 0; j < arrange_n; j++) {
        for (k = 0; k < dic; k++) {
            if (shingle[i][arrange[j][k]])
            break;
        }
        sig[i][j]=k;
        }
    }
}
//need no input
//local sensitive hash to bucket
void LSH::local_sensitive(){
    int i, j,k;
    int bucket_cnt = 0;
  for (i = 0; i < band; i++)
  {
    for (j = 0; j <= doc; j++)
    {
      string raw, code;
      stringstream ss;
      for (k = 0; k < row; k++)
        ss << sig[j][i * row + k];
      ss >> raw;
      int hashvalue = myhash(raw);
      if (h[hashvalue] == (unsigned short)-1)
        h[hashvalue] = j;
      else if (bucket_no[h[hashvalue]] == (unsigned short)-1 && bucket_no[j] == (unsigned short)-1)
      {
        bucket_no[h[hashvalue]] = bucket_cnt;
        bucket_no[j] = bucket_cnt;
        bucket.push_back(vector<unsigned short>());
        bucket[bucket_cnt].push_back(h[hashvalue]);
        bucket[bucket_cnt].push_back(j);
        bucket_cnt++;
      }
      else if(bucket_no[h[hashvalue]]!=(unsigned short)-1
      && bucket_no[j]==(unsigned short)-1){
        bucket_no[j] = bucket_no[h[hashvalue]];
        bucket[bucket_no[j]].push_back(j);
      }
    }
    h.assign(h.size(), -1);
    bucket_no.assign(bucket_no.size(),-1);
    //cout << "band" << i << "finished" << endl;  
  }
}
void LSH::show_bucket(){
    int i, j,total=0;
    for (i = 0; i < bucket_cnt; i++) {
        cout<<"bucket"<<i<<"   :";
        for (j = 0; j < bucket[i].size(); j++)
            cout << bucket[i][j]<<" ";
        total += bucket[i].size();
    }
    cout << total;
}
int main(){
    LSH lsh("docword.txt");
    lsh.permution();
    lsh.signature();
    lsh.local_sensitive();
    lsh.show_bucket();
}