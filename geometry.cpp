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

using namespace std;

typedef vector<int> vi; typedef pair<int,int> pii; typedef vector<pair<int,int> > vpii;
typedef long long ll;

const int MAX=10000;

set<pii> h;

int round1(const double &x){return (int)(floor(x+0.5));}

struct vec
{
    double x,y;
    vec(const double &xx, const double &yy){x=xx;y=yy;}
    vec(void){}
    vec(const vec &t){x=t.x;y=t.y;}
};

double dist(const vec &x, const vec &y){return sqrt(pow(x.x-y.x,2)+pow(x.y-y.y,2));}

double dot_mul(const vec &x, const vec &y){return x.x*y.x+x.y*y.y;}

vec num_mul(const double &k, const vec &x){return vec(k*x.x,k*x.y);}

vec add(const vec &x, const vec &y){return vec(x.x+y.x,x.y+y.y);}

vec sub(const vec &x, const vec &y){return vec(x.x-y.x,x.y-y.y);}

vec triangle_circum_center(const vec &A, const vec &B, const vec &C)
{
    double a=dist(B,C);
    double b=dist(A,C);
    double c=dist(A,B);
    double P=(a*a+b*b+c*c)/2;
    double Q=1/(1/(P-a*a)+1/(P-b*b)+1/(P-c*c));
    double k1=Q/(P-a*a),k2=Q/(P-b*b),k3=Q/(P-c*c);
    return add(add(num_mul((1-k1)/2,A),num_mul((1-k2)/2,B)),num_mul((1-k3)/2,C));
}

vec triangle_perp_center(const vec &A, const vec &B, const vec &C)
{
    double a=dist(B,C);
    double b=dist(A,C);
    double c=dist(A,B);
    double P=(a*a+b*b+c*c)/2;
    double Q=1/(1/(P-a*a)+1/(P-b*b)+1/(P-c*c));
    double k1=Q/(P-a*a),k2=Q/(P-b*b),k3=Q/(P-c*c);
    return add(add(num_mul(k1,A),num_mul(k2,B)),num_mul(k3,C));
}

bool check(double x, double y, double t, const vector<vec> &p)
{
    int cnt;
    vec c(x,y);
    rep(i,p.size())
        if(dist(p[i],c)<t-EPS)return false;
    return true;
}

int main()
{
    int n;
    cin>>n;
    vector<vec> p;
    rep(i,n)
    {
        int x,y;
        cin>>x>>y;
        h.insert(mp(x,y));
        p.pb(vec(x,y));
    }
    double ans=-1;
    rep(i,n)
    {
        rep(j,n)if(i!=j)
        {
            rep(k,n)if(i!=k&&j!=k)
            {
                vec l1=sub(p[i],p[j]);
                vec l2=sub(p[k],p[i]);
                vec l3=sub(p[j],p[k]);
                double p1=dot_mul(l1,l2),p2=dot_mul(l2,l3),p3=dot_mul(l3,l1);
                if(fabs(p1*p2*p3)<EPS)
                {
                    vec r;
                    double xx,yy;
                    if(!p1){
                        r=add(p[j],l2);
                    }
                    else if(!p2){
                        r=add(p[i],l3);
                    }
                    else {
                        r=add(p[k],l1);
                    }
                    if(h.find(mp(round1(r.x),round1(r.y)))!=h.end())
                    {
                        vec O=triangle_circum_center(p[i],p[j],p[k]);
                        double t=dist(p[i],O);
                        if(t>ans&&check(O.x,O.y,t,p)){ans=t;/*printf("rec: ans=%lf | %lf %lf | %lf %lf | %lf %lf\n",ans,p[i].x,p[i].y,p[j].x,p[j].y,p[k].x,p[k].y);*/}
                    }
                } else if(p1>EPS||p2>EPS||p3>EPS){
                    continue;
                } else {
                    vec O=triangle_circum_center(p[i],p[j],p[k]);
                    double t=dist(p[i],O);
                    if(t>ans&&check(O.x,O.y,t,p)){ans=t;/*printf("tri: ans=%lf | %lf %lf | %lf %lf | %lf %lf\n",ans,p[i].x,p[i].y,p[j].x,p[j].y,p[k].x,p[k].y);printf("O: x=%lf y=%lf\n",O.x,O.y);*/}
                }
            }
        }
    }
    if(ans<0)cout<<-1<<endl;
    else printf("%.9lf",ans);
    return 0;
}
