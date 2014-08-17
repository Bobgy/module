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
#define read(_type,name) _type name; cin>>name
#define read2(_type,name1,name2) _type name1,name2; cin>>name1>>name2
#define pi 3.141592653589793238

using namespace std;

typedef vector<int> vi; typedef pair<int,int> pii; typedef vector<pair<int,int> > vpii;
typedef long long ll; typedef pair<double,double> pdd; typedef unsigned int ui;
typedef unsigned long long ull;

int gcd(int a, int b) //a>0&&b>0
{
    if(a<b)swap(a,b);
    int r=a%b;
    if(r==0)return b;
    else return gcd(b,r);
}

pii exgcd(int a, int b) //a>0&&b>0
{
    bool f=a<b;
    if(f)swap(a,b);
    int r=a%b,q=a/b;
    if(r==0)return mp(0,1);
    else {
        pii t=exgcd(b,r);
        pii res=mp(t.second,t.first-q*t.second);
        if(f)swap(res.first,res.second);
        return res;
    }
}

ll go(ll n, int num, int i, vi &primes)
{
    ll res=0;
    if(num<=0||i>=primes.size())return 1;
    rep(j,num){
        res+=go(n, j, i+1, primes);
        n/=primes[i];
        if(!n)break;
    }
    if(res>100000000)cout<<n<<' '<<num<<' '<<i<<' '<<endl;
    return res;
}

main()
{
    vi primes;
    ull n=1;
    rep(i,63)n*=2;
    ull ans=0;
    int x;
    while(cin>>x){
        primes.pb(x);
    }
    ans=go(n,63,0,primes);
    cout<<ans<<endl;
    /*
    gi2(x,y);
    pii t=exgcd(x,y);
    cout<<t.first<<' '<<t.second<<endl;
    */
}
