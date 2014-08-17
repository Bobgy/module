#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>
#include <map>
#include <queue>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <cstring>
#include <cctype>
#include <utility>
#include <cstdlib>
#include <cassert>

/*
#define rep(i,n) for(int (i)=0;(i)<(int)(n);++(i))
#define foreach(c,itr) for(__typeof((c).begin()) itr=(c).begin();itr!=(c).end();itr++)
#define rer(i,l,u) for(int (i)=(int)(l);(i)<=(int)(u);++(i))
#define reu(i,l,u) for(int (i)=(int)(l);(i)<(int)(u);++(i))
#define all(o) (o).begin(), (o).end()
#define pb(x) push_back(x)
#define mp(x,y) make_pair((x),(y))
#define mset(m,v) memset(m,v,sizeof(m))
#define EPS 1e-9
#define gi(a) int a; cin>>a
#define gi2(a,b) int a,b; cin>>a>>b
#define gi3(a,b,c) int a,b,c; cin>>a>>b>>c
#define read(_type,name) _type name; cin>>name
#define read2(_type,name1,name2) _type name1,name2; cin>>name1>>name2
#define read3(_type,name1,name2,name3) _type name1,name2,name3; cin>>name1>>name2>>name3
#define pi 3.141592653589793238
#define INT_INF 0x7fffffff
#define UI_INF 0xffffffff
*/

using namespace std;

typedef vector<int> vi; typedef pair<int,int> pii; typedef vector<pair<int,int> > vpii;
typedef long long ll; typedef pair<double,double> pdd; typedef unsigned int ui;

#define MAXN 4
const int mod=10000;

struct matrix
{
    int d[MAXN][MAXN];
    int n,m;
    matrix(void)
    {
        memset(d,0,sizeof d);
        n=0,m=0;
    }
    matrix(int nn, int mm)
    {
        memset(d,0,sizeof d);
        n=nn, m=mm;
    }
    matrix(const matrix &b)
    {
        n=b.n; m=b.m;
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                d[i][j]=b.d[i][j];
    }
    matrix operator*(const matrix &b)
    {
        assert(m==b.n);
        matrix res(n,b.m);
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<b.m;j++)
            {
                res.d[i][j]=0;
                for(int k=0;k<m;k++)
                {
                    res.d[i][j]+=(d[i][k]*b.d[k][j])%mod;
                    res.d[i][j]%=mod;
                }
            }
        }
        return res;
    }
};

void print(const matrix &a)
{
    for(int i=0;i<a.n;i++){
        for(int j=0;j<a.m;j++)
            cout<<a.d[i][j]<<' ';
        cout<<endl;
    }
}

main()
{
    //std::ios::sync_with_stdio(false);
    int n;
    matrix a(2,2);
    a.d[0][0]=0;
    a.d[0][1]=1;
    a.d[1][1]=1;
    a.d[1][0]=1;
    cin>>n;
    while(n!=-1)
    {
        matrix x(a);
        matrix m(a);
        matrix b(2,1);
        b.d[0][0]=0;
        b.d[1][0]=1;
        for(int i=0;i<m.n;i++)
            for(int j=0;j<m.m;j++)
                m.d[i][j]=i==j;
        while(n)
        {
            //print(x);
            if(n&1)m=m*x;
            n=n>>1;
            x=x*x;
        }
        //print(m);
        b=m*b;
        //print(b);
        cout<<b.d[0][0]<<endl;
        cin>>n;
    }
}


