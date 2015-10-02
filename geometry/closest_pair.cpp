#include <bits/stdc++.h>
using namespace std;
#define rer(i,L,R) for(int i=int(L);i<=int(R);++i)
#define pb push_back
typedef pair<int,int> pii;

const double EPS=1e-9, INF=1e9;
const int DIM=3, MAXN=112345;

template <class T> T sqr(T x) {return x*x;}

int fcmp(double x) {
    return fabs(x)<EPS ? 0 : (x<0 ? -1 : 1);
}

struct Point {
    double x[DIM];
    int id;
    double &operator[](int i) {return x[i];}
    friend double dis(Point a, Point b) {
        double res = 0;
        for(int i = 0; i < DIM; ++i)
            res += sqr(a[i] - b[i]);
        return sqrt(res);
    }
};

struct Comp {
    int dim;
    bool operator()(Point l, Point r) const {
        return l.x[dim] < r.x[dim];
    }
    Comp(int dim): dim(dim) {}
};

// call work() to find the closest pair
// require all points to be different in order to ensure approximately
// O(n*log(n)) complexity
struct ClosestPair {
    double min_dis; //stores the minimum distance
    pii best_pair;  //stores the closest pair
    vector<Point> vtmp[DIM];

    void init() {
        min_dis = INF;
        best_pair = pii(-1,-1);
        for(int i=0; i<DIM; ++i)
            vtmp[i].clear();
    }

    // check Point a and Point b, update best_pair and min_dis with (a, b)
    void take_best(Point a, Point b) {
        if (a.id > b.id) swap(a, b);
        int cmp_res = fcmp(dis(a, b) - min_dis);
        if (
            best_pair.first==-1 || cmp_res<0 ||
            (cmp_res==0 && pii(a.id, b.id)<best_pair)
        ) {
            best_pair = pii(a.id, b.id);
            min_dis = dis(a, b);
        }
    }

    //find the closest pair in v[l, r]
    void closest_pair(vector<Point> &v, int l, int r, int dim=0) {
        if (r-l <= 6) {
            for (int i=l+1; i<=r; ++i)
                for (int j=l; j<i; ++j)
                    take_best(v[i], v[j]);
            return;
        }

        if (dim+1 == DIM) {
            int z = dim - 1;
            for (int i=l; i<r; ++i) {
                for (int j=i+1; j<=r && v[j][z]-v[i][z]<min_dis; ++j)
                    take_best(v[i], v[j]);
            }
            return;
        }

        int m = (l+r) / 2;
        closest_pair(v, l, m, dim);
        closest_pair(v, m+1, r, dim);

        vector<Point> &u = vtmp[dim];
        u.clear();
        for(int i=l; i<=r; ++i)
            if (fcmp(abs(v[i][dim]-v[m][dim]) - min_dis) <= 0) {
                u.pb(v[i]);
            }

        sort(u.begin(), u.end(), Comp(dim+1));
        if(!u.empty())closest_pair(u, 0, (int)u.size()-1, dim+1);
    }
public:
    double work(vector<Point> &v) {
        init();
        sort(v.begin(), v.end(), Comp(0));
        closest_pair(v, 0, (int)v.size()-1);
        return min_dis;
    }
} closest_pair;
