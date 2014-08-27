#include <bits/stdc++.h>
#ifdef ONLINE_JUDGE
    #define out(x)
#else
    #define out(x) cerr<<#x"="<<(x)<<endl
#endif
using namespace std;
typedef long long LL;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector<pii> vpii;
#define REP(i,n) for(int i=0; i<int(n); i++)
#define pb push_back
#define mp make_pair
#define X first
#define Y second
double x[112345], y[112345], z[112345];
inline double sqr(double x){return x*x;}
int main(){
    int n;
    while(scanf("%d",&n)==1){
        REP(i,n)
            scanf("%lf%lf%lf",x+i,y+i,z+i);
        double res=1e9;
        REP(i,n)REP(j,i){
            res=min(res, sqrt(sqr(x[i]-x[j])+sqr(y[i]-y[j])+sqr(z[i]-z[j])));
        }
        printf("%.3f\n", res);
    }
}
