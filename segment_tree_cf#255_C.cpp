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
const int MOD=1e9+9;
const int sr5=616991993;
int power(int x, int n){
    int r=1;
    for(; n; x=x*(LL)x%MOD, n>>=1)
        if(n&1)r=r*(LL)x%MOD;
    return r;
}
int inv(int x){
    return power(x,MOD-2);
}
int fix(int x){
    return x<0?x+MOD:x;
}
void add(int &x, int y){
    x=(x+y)%MOD;
}
int mul(int x, int y){
    return x*(LL)y%MOD;
}
int r5=inv(sr5);
int xx=(1+sr5)*(LL)inv(2)%MOD;
int yy=(1-sr5)*(LL)inv(2)%MOD;
struct SegTree{
    int Q, L, R, a, iQ;
    int q[312345];
    struct node{
        int s, a0;
    } v[312345*4];
    void init(int _Q){
        Q=_Q;
        q[0]=1;
        iQ=inv(Q-1);
        for(int i=1; i<312345; ++i)
            q[i]=mul(q[i-1],Q);
    }
    inline int calc(int x, int l, int r){
        int res=v[x].s;
        if(v[x].a0)add(res, mul(mul(v[x].a0, q[r-l+1]-1), iQ));
        return res;
    }
    inline void rep0(int x, int l, int m, int r){
        if(v[x].a0){
            add(v[x*2].a0, v[x].a0);
            add(v[x*2+1].a0, v[x].a0*(LL)q[m+1-l]%MOD);
            v[x].a0=0;
        }
    }
    inline void rep1(int x, int l, int m, int r){
        v[x].s=calc(x*2, l, m);
        add(v[x].s, calc(x*2+1, m+1, r));
    }
    void update(int x, int l, int r){
        if(l>R || r<L)return;
        if(L<=l && r<=R){
            add(v[x].a0, mul(a, q[l-L]));
            return;
        }
        int m=(l+r)/2;
        rep0(x, l, m, r);
        update(x*2, l, m);
        update(x*2+1, m+1, r);
        rep1(x, l, m, r);
    }
    int query(int x, int l, int r){
        if(l>R || r<L)return 0;
        if(L<=l && r<=R)return calc(x, l, r);
        int m=(l+r)/2;
        rep0(x, l, m, r);
        int res=query(x*2, l, m);
        add(res, query(x*2+1, m+1, r));
        rep1(x, l, m, r);
        return res;
    }
} sx, sy;
int fn(int n){return r5*(LL)(power(xx, n)-power(yy, n))%MOD;}
int s[312345];
int main(){
    sx.init(xx);
    sy.init(yy);
    sx.a=mul(r5, xx);
    sy.a=mul(r5, yy);
    int n, m;
    scanf("%d%d",&n,&m);
    REP(i,n){
        scanf("%d",s+i+1);
        add(s[i+1], s[i]);
    }
    while(m--){
        int t, l, r;
        scanf("%d%d%d",&t,&l,&r);
        sx.L=sy.L=l;
        sx.R=sy.R=r;
        if(t==1){
            sx.update(1, 1, n);
            sy.update(1, 1, n);
        } else {
            assert(t==2);
            int res=(s[r]-s[l-1])%MOD;
            add(res, sx.query(1, 1, n));
            add(res, -sy.query(1, 1, n));
            printf("%d\n", fix(res));
        }
    }
}
