#include<iostream>
#include<fstream>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<ctime>
using namespace std;
const int w = 30000;
const int d = 15;
int main(int argc,char* argv[]){
    fstream fin;
    clock_t start, end;
    fin.open(argv[1]);
    if(fin.is_open()==false){
        cout << "read in error" << endl;
        return 0;
    }
    vector<vector<int> > v(d, vector<int>(w, 0));
    vector<int> a(d, 0);
    vector<int> b(d, 0);
    vector<int> a0(d, 0);
    vector<int> a1(d, 0);
    int p = 13;
    srand((unsigned)time(NULL));
    int i, j,sign;
    for (i = 0; i < d;i++){
        a[i] = rand() % p;
        b[i] = rand() % p;
        a0[i] = rand() % p;
        a1[i] = rand() % p;
        srand(rand());
    }
    int temp,delta,range=0;
    start = clock();
    while(fin>>temp>>delta){
        if(temp>=range)
            range = temp;
        for (i = 0; i < d;i++){
            sign = a0[i]+a1[i]*temp;
            if(sign%2)
                sign = 1;
            else
                sign = -1;
            j = ((a[i] * temp + b[i])%p)%w;
            v[i][j] += sign * delta;
        }
    }
    int query = 0,standard;
    for (query = 0; query < range;query++){
        vector<int> ans;
        for (i = 0; i < d;i++){
            sign = a0[i] + a1[i] * query;
            if(sign%2)
                sign = 1;
            else
                sign = -1;
            j = ((a[i] * query + b[i])%p)%w;
            ans.push_back(sign * v[i][j]);
        }
        sort(ans.begin(), ans.end());
        cout << query << ":" << ans[7] << endl;
    }
    end = clock();
    double totaltime = (double)(end-start) / CLOCKS_PER_SEC;
    cout << "run time is " << totaltime * 1000 << "ms" << endl;
}