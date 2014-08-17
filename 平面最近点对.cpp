#include <bits/stdc++.h>
#ifdef ONLINE_JUDGE
	#define out(x)
#else
	#define out(x) cerr<<#x"="<<(x)<<endl
#endif
using namespace std;
#define REP(i,n) for(int i=0; i<int(n); i++)
#define pb push_back
#define X first
#define Y second
typedef long long LL;
typedef pair<int, int> pii;
typedef vector<pii> vpii;
pii p[112345];
inline LL sqr(int x){
	return x*(LL)x;
}
inline LL dis(const pii &a, const pii &b){
	return sqr(a.X-b.X)+sqr(a.Y-b.Y);
}
LL gao(int l, int r){
	if(r-l<=1)return 1LL<<62;
	if(r-l==2){
		if(p[l].Y>p[l+1].Y)swap(p[l], p[l+1]);
		return dis(p[l], p[l+1]);
	}
	int m=(l+r)/2, mx=p[m].X;
	LL dd=min(gao(l,m), gao(m,r));
	inplace_merge(p+l, p+m, p+r, [&](pii a, pii b){return a.Y<b.Y;});
	vpii tmp;
	for(int i=l; i<r; i++)
		if(sqr(p[i].X-mx)<dd)
			tmp.pb(p[i]);
	REP(i,tmp.size())
		for(int j=i+1; j<tmp.size() && sqr(tmp[j].Y-tmp[i].Y)<dd; j++)
			dd=min(dd, dis(tmp[i], tmp[j]));
	return dd;
}
int main(){
	int n;
	scanf("%d", &n);
	REP(i,n){
		int xx;
		scanf("%d", &xx);
		p[i].Y=i?p[i-1].Y+xx:xx;
		p[i].X=i;
	}
	LL ans=gao(0,n);
	printf("%I64d\n", ans);
}
