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
template<class T> T sqr(T x){return x*x;}
typedef double flt;
const flt EPS=1e-9;
const int MAXN=1001;
const flt PI=acos(-1.0);
struct CIRU{
    int x[MAXN],y[MAXN],r[MAXN],n;
    void clear(){n=0;}
    void add_circle(int xx,int yy,int rr){
        x[n]=xx,y[n]=yy,r[n++]=rr;
    }
    int sqdis(int i, int j){
        return sqr(x[i]-x[j])+sqr(y[i]-y[j]);
    }
    flt fix(flt x){
        if(x<-PI)x+=2*PI;
        if(x>PI)x-=2*PI;
        return x;
    }
    pair<flt,int> v[MAXN*4+9];
    flt calc_area(){
        flt area=0;
        for(int i=0;i<n;++i){
            bool ok=1;
            int tot=2;
            v[0]=mp(-PI,0);
            v[1]=mp(PI,0);
            for(int j=0;j<n;++j)if(j!=i){
                if(x[j]==x[i]&&y[j]==y[i]&&r[j]==r[i]&&j<i){ok=0;break;}
                int dis=sqdis(i,j);
                if(r[i]<r[j]&&dis<sqr(r[i]-r[j])){ok=0;break;}
                if(dis>=sqr(r[i]+r[j]))continue;
                flt delta = (sqr(r[i])-sqr(r[j])+dis)*0.5;
                delta = acos(delta / (sqrt(flt(dis))*r[i]));
                flt dir = atan2(flt(y[j]-y[i]),flt(x[j]-x[i]));
                flt bg = dir-delta, ed=dir+delta;
                bg=fix(bg),ed=fix(ed);
                v[tot++]=make_pair(bg,1);
                v[tot++]=make_pair(ed,-1);
                if(bg>ed+EPS){
                    v[tot++]=mp(PI,-1);
                    v[tot++]=mp(-PI,1);
                }
            }
            if(tot==0){
                area+=PI*sqr(r[i]); //与其他圆不相交
            } else {
                sort(v,v+tot);
                int cnt=0;
                REP(j,tot-1){
                    cnt+=v[j].second;
                    flt a1=v[j].first,a2=v[j+1].first;
                    if(cnt==0&&a2-a1>EPS){
                        area+=(a2-a1)*sqr(r[i]); //扇形面积
                        /*
                        area+=(a2-a1-sin(a2-a1))*sqr(r[i]) //弓形面积
                        flt x1=x[i]+cos(a1), y1=y[i]+sin(a1);
                        flt x2=x[i]+cos(a2), y2=y[i]+sin(a2);
                        area+=(x1*y2-x2*y1)*0.5; //被包围的多边形面积
                        */
                        area += r[i] * (y[i]*(cos(a1)-cos(a2)) + x[i]*(sin(a2)-sin(a1)));
                    }
                }
            }
        }
        return area*0.5;
    }
} cu;
int main(){
    int n;
    scanf("%d",&n);
    cu.clear();
    REP(i,n){
        int x,y,r;
        scanf("%d%d%d",&x,&y,&r);
        cu.add_circle(x,y,r);
    }
    printf("%.3f\n",cu.calc_area());
}
