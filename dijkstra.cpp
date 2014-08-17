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
#define read1(_type,a) _type a; cin>>a
#define read2(_type,a,b) _type a,b; cin>>a>>b
#define read3(_type,a,b,c) _type a,b,c; cin>>a>>b>>c
#define pi 3.141592653589793238

using namespace std;

typedef vector<int> vi; typedef pair<int,int> pii; typedef vector<pair<int,int> > vpii;
typedef long long ll; typedef pair<double,double> pdd;

//dijkstra

const int MAX_N = 1005, MAX_M = 1005, INF = 0x3F3F3F3F;
int n, m, k;

//n: number of vertices, s: start point, e: end point (-1 == none) E[i]=vector of points(i->)
void dijkstra(int n, int s, int e, const vector<vpii> &E, vi &dist, vi &pre)  //pair<destiny, cost>
{                  //0 index
    int v1;
	dist=vi(n,0x7ffffffe);
	pre=vi(n,-1);
	priority_queue <pii, vector <pii>, greater <pii> > heap;
	dist[s] = 0;
	heap.push(make_pair(0, s));
	
	while (!heap.empty())
	{
		int v0 = heap.top().second;
		int d0 = heap.top().first;
		heap.pop();
        rep(i,E[v0].size())
        {
            if(dist[v1 = E[v0][i].first] > d0 + E[v0][i].second)
            {
                dist[v1] = d0 + E[v0][i].second;
                pre[v1] = v0;
                heap.push(make_pair(dist[v1], v1));
            }
        }
	}
}

main()
{
    //std::ios::sync_with_stdio(false);
    gi2(n,m);
    gi2(b,e);
    vector<vpii> E(n);
    rep(i,m)
    {
        gi3(s,t,c);
        E[s].pb(mp(t,c));
        E[t].pb(mp(s,c));
    }
    vi dist,pre;
    dijkstra(n,b,e,E,dist,pre);
    int j=e;
    rep(i,n)printf("%d%c",dist[i],i==n-1?'\n':' ');
    printf("%d",e);
    while(pre[j]>=0)
        printf(" <= %d",j=pre[j]);
    cout<<endl;
    return 0;
}

