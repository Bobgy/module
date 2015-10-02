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
int main(){
    srand(time(0));
    int T=1;
    while(T--){
        int n;
        n=100000;
        printf("%d\n", n);
        REP(i,n)printf("%d %d %d\n", rand(), rand(), rand());
    }
}
