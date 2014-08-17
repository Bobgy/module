#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
#define REP(i,n) for(int i=0; i<int(n); i++)
#define RER(i,l,r) for(int i=l; i<(int)r; i++)
#define out(x) cout<<(#x)<<'='<<x<<endl
#define MAXN 8123
#define X first
#define Y second
#define pb push_back
typedef vector<int> vi;
struct seg{
	int y0, y1, x;
	seg(bool t){scanf("%d%d%d", &y0, &y1, &x);y0*=2;y1*=2;}
	seg(){}
	bool operator<(const seg &rhs) const {return x<rhs.x;}
} s[MAXN];
map<int, int> mm;
map<int, int>::iterator it, itt;
int c;
void insert(int l, int r, int x){
	it=mm.lower_bound(l);
	itt=mm.upper_bound(r);
	bool f=itt->X>r+1;
	if(f){
		itt--;
		c=itt->Y;
		itt++;
	}
	mm.erase(it, itt);
	if(f)mm[r+1]=c;
	mm[l]=x;
}
void find(int l, int r, vi &res){
	it=mm.upper_bound(l);
	for(it--; it!=mm.end() && it->X<=r; it++)
		if(~it->Y)res.pb(it->Y);
	sort(res.begin(), res.end());
	res.resize(unique(res.begin(), res.end())-res.begin());
}
vi e[MAXN];
unsigned int g[MAXN][MAXN/32];
void set(int i, int j){
	g[i][j/32]|=1<<(j%32);
	
}
bool get(int i, int j){
	return g[i][j/32]&(1<<(j%32));
}
int main(){
	int d, ans;
	scanf("%d", &d);
	while(d--){
		int n;
		scanf("%d", &n);
		REP(i,n){
			s[i]=seg(true);
			e[i].clear();
		}
		sort(s, s+n);
		mm.clear();
		mm[16001]=mm[0]=-1;
		REP(i,n){
			find(s[i].y0, s[i].y1, e[i]);
			vi &v=e[i];
			REP(j,v.size())set(i,v[j]),set(v[j],i);
			insert(s[i].y0, s[i].y1, i);
		}
		ans=0;
		for(int i=n-1; ~i; i--){
			vi &v=e[i];
			for(int j=0;j<v.size();j++)
				for(int k=0; k<j; k++)
					if(get(v[j], v[k]))ans++;
		}
		printf("%d\n", ans);
		REP(i,n)
			memset(g[i], 0, sizeof(g[i]));
	}
}
