#include <bits/stdc++.h>
using namespace std;
#define REP(i,n) for(int i=0; i<int(n); i++)
#define pb push_back
#define mp make_pair
#define X first
#define Y second
typedef long long LL;
typedef pair<int, int> pii;
typedef vector<pii> vpii;
double eps=1e-9;
struct CMP;
typedef double TData;
const int nDim=3;
template <class T>
T sqr(T x){return x*x;}
struct Pt{
    TData x[nDim];
    int id;
    friend CMP;
    friend TData dis(Pt a, Pt b){
        TData res=0;
        for(int i=0; i<nDim; ++i)
            res+=sqr(a.x[i]-b.x[i]);
        return sqrt(res);
    }
};
vector<Pt> v;
Pt pts[112345];
bool cmp_dis_accurately(pii a, pii b){
    return dis(pts[a.X], pts[a.Y])<dis(pts[b.X], pts[b.Y]);
}
struct CMP{
    int dim;
    bool operator()(Pt l, Pt r) const {
        return l.x[dim] < r.x[dim];
    }
} cmp;
//find the closest pair in v[l, r)
//make sure v is sorted by dimension[0] in ascending order before calling closest_pair()
TData min_dis=1e9; //This number should be large enough
pii best_pair=mp(-1,-1); //stores the closest pair
void take_best(Pt a, Pt b){
    if(a.id>b.id)swap(a, b);
    if(best_pair.X==-1 || cmp_dis_accurately(mp(a.id, b.id), best_pair)){
        best_pair=mp(a.id, b.id);
        min_dis=dis(a, b)+eps;
    }
}
void closest_pair(vector<Pt> &v, int l, int r, int dim=0){
    if(r-l<=3){
        for(int i=l+1; i<r; ++i)
            for(int j=l; j<i; ++j)
                take_best(v[i], v[j]);
        return;
    }
    if(dim+1==nDim){
        int z=nDim-1;
        REP(i, v.size()){
            for(int j=1; i+j<v.size() && v[j].x[z]-v[i].x[z]<=min_dis; ++j)
                take_best(v[i], v[i+j]);
        }
        return;
    }
    int m=(l+r)/2;
    closest_pair(v, l, m, dim);
    closest_pair(v, m, r, dim);
    vector<Pt> vtmp;
    REP(i,v.size())if(abs(v[i].x[dim]-v[m].x[dim])<=min_dis)
        vtmp.pb(v[i]);
    cmp.dim=dim+1;
    sort(vtmp.begin(), vtmp.end(), cmp);
    closest_pair(vtmp, 0, vtmp.size(), dim+1);
}
int main(){
    int n;
    while(scanf("%d",&n)==1){
        min_dis=1e9;
        best_pair=mp(-1, -1);
        v.clear();
        REP(i,n){
            TData x, y, z;
            scanf("%lf%lf%lf",&x,&y,&z);
            pts[i].x[0]=x;
            pts[i].x[1]=y;
            pts[i].x[2]=z;
            pts[i].id=i;
            v.pb(pts[i]);
        }
        cmp.dim=0;
        sort(v.begin(), v.end(), cmp);
        closest_pair(v, 0, v.size());
        printf("%.3f\n", min_dis);
        assert(~best_pair.X);
        TData dist=dis(pts[best_pair.X], pts[best_pair.Y]);
        assert((dist-min_dis)<eps);
    }
}
