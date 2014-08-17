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

using namespace std;

typedef vector<int> vi; typedef pair<int,int> pii; typedef vector<pair<int,int> > vpii;
typedef long long ll; typedef pair<double,double> pdd; typedef unsigned int ui;
typedef unsigned long long ull;

//#define _DEBUG

const int mod=1000000009;

ll tmp[120][120];

ll C(int n, int k)
{
    //if(n<0||k<0)return 0;
    assert(n>=0&&k>=0);
    if(k>n)return 0;
    if(tmp[n][k]!=0)return tmp[n][k];
    if(k==0||k==n){
        tmp[n][k]=1;
    } else {
        tmp[n][k]=C(n-1,k)+C(n-1,k-1);
    }
    tmp[n][k]%=mod;
    return tmp[n][k];
}

int main()
{
    //std::ios::sync_with_stdio(false);
    /*
    #ifdef _DEBUG
    {
        int n,k;
        while(cin>>n>>k)
            cout<<C(n,k)<<endl;
    }
    #endif
    */
    int n,k,m;
    while(cin>>n>>k>>m)
    {
        string s1, s2;
        getchar();
        getline(cin,s1);
        getline(cin,s2);
        assert(s1.size()==s2.size());
        assert(s1.size()==(unsigned int)n);
        int cnt[2]={0,0};
        rep(i,s1.size())
            cnt[(s1[i]-'0')^(s2[i]-'0')]++;
        #ifdef _DEBUG
        cout<<cnt[0]<<' '<<cnt[1]<<endl;
        #endif
        assert(cnt[0]+cnt[1]==n);
        ll f[110][110];
        memset(f,0,sizeof f);
        f[0][cnt[0]]=1; //f[k step][num(0)]
        rep(i,k)
        {
            rep(j,n+1) //num 0
            {
                if(f[i][j]<=0)continue;
                for(int l=max(m+j-n,0);l<=min(j,m);l++) //num 0 to change
                {
                    int t=j-l+(m-l);
                    //if(j<0||l<0||(n-j<0)||(m-l<0))cout<<j<<' '<<l<<' '<<n<<' '<<m<<endl;
                    f[i+1][t]+=(C(j,l)*C(n-j,m-l)%mod)*f[i][j];
                    f[i+1][t]%=mod;
                }
            }
        }
        cout<<f[k][n]<<endl;
    }
}

