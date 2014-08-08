#include <bits/stdc++.h>
#define ONLINE_JUDGE
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
struct SegTree{
    int L, R, C;
    struct node{
		int c;
		LL s;
    } v[112345*4];
    inline void rep0(int x, int l, int m, int r){
        if(v[x].c){//caution: multiple modifications
			node &a=v[x*2], &b=v[x*2+1];
			assert(a.c==b.c && a.c);
			LL stmp=v[x].s-a.s-b.s;
			assert(stmp%(r-l+1)==0);
			stmp/=r-l+1;
			a.s+=stmp*(m-l+1);
			b.s+=stmp*(r-m);
			assert(a.s+b.s==v[x].s);
			a.c=b.c=v[x].c;
		}
    }
    inline void rep1(int x, int l, int m, int r){
        v[x].s=v[x*2].s+v[x*2+1].s;
        if(v[x*2].c==v[x*2+1].c)
			v[x].c=v[x*2].c;
		else v[x].c=0;
    }
	void print(int x, int l, int r){
#ifndef ONLINE_JUDGE
		int m=(l+r)/2;
		if(l<r){
			print(x*2, l, m);
			print(x*2+1, m+1, r);
		}
		printf("range=[%d, %d], s=%lld, c=%d\n", l, r, v[x].s, v[x].c);
#endif
	}
	void build(int x, int l, int r){
		v[x].s=0;
		if(l==r){
			v[x].c=l;
			return;
		}
		v[x].c=0;
		int m=(l+r)/2;
		build(x*2, l, m);
		build(x*2+1, m+1, r);
	}
    void update(int x, int l, int r){
        if(l>R || r<L)return;
        if(L<=l && r<=R && v[x].c){
            v[x].s+=(r-l+1)*(LL)abs(C-v[x].c);
			v[x].c=C;
            return;
        }
        int m=(l+r)/2;
        rep0(x, l, m, r);
        update(x*2, l, m);
        update(x*2+1, m+1, r);
        rep1(x, l, m, r);
    }
    LL query(int x, int l, int r){
        if(l>R || r<L)return 0;
        if(L<=l && r<=R)return v[x].s;
        int m=(l+r)/2;
        rep0(x, l, m, r);
        LL res=query(x*2, l, m)+query(x*2+1, m+1, r);
        rep1(x, l, m, r);
        return res;
    }
} seg;
int main(){
    int n, m;
    scanf("%d%d",&n,&m);
	seg.build(1, 1, n);
    while(m--){
        int t, l, r;
        scanf("%d%d%d",&t,&l,&r);
        seg.L=l;
		seg.R=r;
        if(t==1){
			scanf("%d",&seg.C);
            seg.update(1, 1, n);
        } else {
            assert(t==2);
            LL res=seg.query(1, 1, n);
            printf("%lld\n", res);
        }
    }
}
