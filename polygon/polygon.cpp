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
#define rer(i,l,u) for(int (i)=(int)(l);(i)<=(int)(u);++(i))
#define reu(i,l,u) for(int (i)=(int)(l);(i)<(int)(u);++(i))
#define all(o) (o).begin(), (o).end()
#define pb(x) push_back(x)
#define mp(x,y) make_pair((x),(y))
#define EPS 1e-9
#define FINF 1e8
#define PI 3.14159265358979

using namespace std;

typedef vector<int> vi; typedef pair<int,int> pii; typedef vector<pair<int,int> > vpii;
typedef long long ll; typedef pair<double,double> pdd; typedef vector<pdd> vpdd;
typedef vector<double> vd;

const int MAX=10000;

int round_(const double &x){return (int)(floor(x+0.5));}

struct vctr;
double dist(const vctr &x, const vctr &y);
double dot_mul(const vctr &x, const vctr &y);
vctr num_mul(const double &k, const vctr &x);
vctr add(const vctr &x, const vctr &y);
vctr sub(const vctr &x, const vctr &y);

struct vctr
{
    double x,y;
    vctr(const double &xx, const double &yy){x=xx;y=yy;}
    vctr(void){}
    vctr(const vctr &t){x=t.x;y=t.y;}
    vctr operator+(const vctr &a)const{return add(*this,a);}
    vctr operator-(const vctr &a)const{return sub(*this,a);}
    vctr operator*(const double &c)const{return vctr(this->x*c,this->y*c);}  //num product
    vctr operator/(const double &c)const{return vctr(this->x/c,this->y/c);}  //num fraction
    double operator*(const vctr &a)const{return dot_mul(*this,a);}           //dot product
    double operator^(const vctr &a)const{return this->x*a.y-this->y*a.x;}    //cross product
    double operator!(void)const{return sqrt(pow(this->x,2)+pow(this->y,2));} //modulus of the vec
    double operator&(const vctr &a)const{return !(*this-a);}             //distance between *this and a
    bool operator/(const vctr &a)const{return fabs(*this^a)<EPS;}        //parralel
    bool operator<(const vctr &b) const    //equivalent to "<" for pair<double, double>, EPS considered
        {return fabs(this->x-b.x)<EPS?(fabs(this->y-b.y)<EPS?false:this->y<b.y):this->x<b.x;}
    bool operator==(const vctr &b) const {return (*this&b)<EPS;} //*this and b is the same
    vctr operator=(const vctr &a){this->x=a.x; this->y=a.y; return *this;}
};

typedef vector<vctr> vvctr; typedef pair<double, int> pdi;
typedef vector<pdi> vpdi;
typedef vector<vpdi> vvpdi;

double dist(const vctr &x, const vctr &y){return sqrt(pow(x.x-y.x,2)+pow(x.y-y.y,2));}
double dist_point_line(const vctr &p, const vctr &a, const vctr &b){return ((p-a)^(b-a))/(b&a);}//p到ab
bool point_on_line(const vctr &p, const vctr &a, const vctr &b){return dist_point_line(p,a,b)<EPS;}
bool point_on_segment(const vctr &p, const vctr &a, const vctr &b)
    {return point_on_line(p,a,b)&&fabs((p&a)+(p&b)-(a&b))<EPS;}
double dot_mul(const vctr &x, const vctr &y){return x.x*y.x+x.y*y.y;}
vctr num_mul(const double &k, const vctr &x){return vctr(k*x.x,k*x.y);}
vctr add(const vctr &x, const vctr &y){return vctr(x.x+y.x,x.y+y.y);}
vctr sub(const vctr &x, const vctr &y){return vctr(x.x-y.x,x.y-y.y);}

//two points on the same side of segment s1-s2
bool same_side(const vctr &a, const vctr &b, const vctr &s1, const vctr &s2)
    {return ((a-s1)^(s2-s1))*((b-s1)^(s2-s1))>EPS;}

void print(const vctr &a){printf("(%.2lf,%.2lf)",a.x,a.y);}

void print(const vd &a){rep(i,a.size())printf("%.2lf%c",a[i],i==a.size()-1?'\n':' ');}

//a1x1+a2x2+a3=0
//b1x1+b2x2+b3=0
vctr solve(vd &a, vd &b)
{
    assert(a.size()==b.size()&&a.size()==3);
    if(fabs(b[0])>fabs(a[0]))swap(a,b);
    assert(fabs(a[0])>EPS);
    double k=b[0]/a[0];
    rep(i,3)b[i]-=a[i]*k;
    assert(fabs(b[1])>EPS);
    double x2=-b[2]/b[1];
    double x1=-(a[2]+a[1]*x2)/a[0];
    return vctr(x1,x2);
}

//Ax+By+C=0
vd equation_of_line(const vctr &b, const vctr &e)
{
    vd res;
    res.pb(e.y-b.y); //A
    res.pb(b.x-e.x); //B
    res.pb(-res[0]*b.x-res[1]*b.y); //C
    return res;
}

pair<bool, vctr> two_segment_intersect(const vctr &b1, const vctr &e1, const vctr &b2, const vctr &e2)
{
    if(!same_side(b1,e1,b2,e2)&&!same_side(b2,e2,b1,e1))
    {
        vctr v1(e1-b1),v2(e2-b2);
        if(v1/v2){ //v1 is parralel to v2 : no intersection
            return mp(false,vctr());
        } else {
            vd l1(equation_of_line(b1,e1)), l2(equation_of_line(b2,e2));
            return mp(true,solve(l1,l2));
        }
    }
    return mp(false,vctr());
}

int point_on_poly(const vctr &a, const vvctr &p)
{
	rep(i,p.size())
		if(point_on_segment(a,p[i],p[(i+1)%p.size()]))return i;
	return -1;
}

int pos_point_polygon(const vctr &a ,const vvctr &p) //result: >=0: index of the edge that point a is on, -1: out, -2: in
{
    int pos=point_on_poly(a,p);
	if(pos>=0)return pos;
    vctr inf;
    int cnt=0;
    bool flag;
    do{
        double theta=(rand()*rand()%100000)/100000.0*2*PI;
        inf=a+vctr(cos(theta),sin(theta))*FINF;        //draw a ray from the point
        flag=true;
        rep(i,p.size())
            if(point_on_segment(p[i],a,inf)||(inf-a)/(p[i]-p[(i+1)%p.size()])){flag=false;break;}
        if(flag)
            rep(i,p.size()){
                pair<bool, vctr> tmp=two_segment_intersect(p[i],p[(i+1)%p.size()],a,inf);
                if(tmp.first)cnt++;
            }
    } while (!flag);
    if(cnt%2)return -2; else return -1;
    //if the ray has odd number of intersections, it is inside the polygon, otherwise outside
}

vctr triangle_circum_center(const vctr &A, const vctr &B, const vctr &C)
{
    double a=dist(B,C);
    double b=dist(A,C);
    double c=dist(A,B);
    double P=(a*a+b*b+c*c)/2;
    double Q=1/(1/(P-a*a)+1/(P-b*b)+1/(P-c*c));
    double k1=Q/(P-a*a),k2=Q/(P-b*b),k3=Q/(P-c*c);
    return add(add(num_mul((1-k1)/2,A),num_mul((1-k2)/2,B)),num_mul((1-k3)/2,C));
}

vctr triangle_perp_center(const vctr &A, const vctr &B, const vctr &C)
{
    double a=dist(B,C);
    double b=dist(A,C);
    double c=dist(A,B);
    double P=(a*a+b*b+c*c)/2;
    double Q=1/(1/(P-a*a)+1/(P-b*b)+1/(P-c*c));
    double k1=Q/(P-a*a),k2=Q/(P-b*b),k3=Q/(P-c*c);
    return add(add(num_mul(k1,A),num_mul(k2,B)),num_mul(k3,C));
}

//寻找p1,p2两个多边形的所有交点
void find_intersections_of_two_polygons(const vvctr &p1, const vvctr &p2, vvpdi &q1, vvpdi &q2)
{
    int n=p1.size(), m=p2.size();
    q1.clear(); q2.clear(); //q1[i][j]:i~i+1边的第j个交点，距i double，交另一个多边形的int~int+1边
    q1.resize(p1.size()); q2.resize(p2.size()); 
    rep(i,n){         //find all intersection points
        rep(j,m){
            pair<bool,vctr> tmp=two_segment_intersect(p1[i],p1[(i+1)%n],p2[j],p2[(j+1)%m]);
            if(tmp.first){
                q1[i].pb(mp(tmp.second&p1[i],j));
                q2[j].pb(mp(tmp.second&p2[j],i));
            }
        }
    }
    return;
}

bool cmpr(const pdi &x, const pdi &y)
    {return fabs(x.first-y.first)<EPS ? x.second<y.second : x.first<y.first;}

void add_edge(const vctr &p1, const vctr &p2, map<vctr, int> &h, int &hn,
            vector<set<int> > &E, vvctr &V)
{
    if(h.find(p1)==h.end()){h[p1]=hn++;V.pb(p1);assert(V.size()==h.size());}
    if(h.find(p2)==h.end()){h[p2]=hn++;V.pb(p2);assert(V.size()==h.size());}
    E.resize(hn);
    E[h[p1]].insert(h[p2]);
}

int nxt(int i, int n){return i==n-1?0:i+1;}

vctr edge(int i, const vvctr &p)
{
    i%=p.size();
    return p[nxt(i,p.size())]-p[i];
}

void find_overlapping_edges(const vvctr &p1, const vvctr &p2, vvpdi &q1,
                            map<vctr, int> &h, int &hn, vector<set<int> > &E, vvctr &V)
{
    int n=p1.size(), m=p2.size();
    rep(i,n){    //find edges caused by intersection
        int next=(i+1)%n;
        vctr curr_edge(p1[next]-p1[i]);
        q1[i].pb(mp(p1[i]&p1[next],-1));
        sort(all(q1[i]),cmpr);
		int j=0;
		vctr curr_p=p1[i];
		for(;j<q1[i].size();j++){
			vctr next_p;
			if(q1[i][j].second==-1)next_p=p1[next];
			else next_p=two_segment_intersect(p1[i],p1[next],p2[q1[i][j].second],p2[(q1[i][j].second+1)%m]).second;
            if(curr_p==next_p)continue;
			int f=pos_point_polygon((curr_p+next_p)/2,p2);
            switch(f){
				case -1: break;//out
				case -2: add_edge(curr_p, next_p, h, hn, E, V); break; //in
				default:
					assert(f>=0);
					vctr e(edge(f,p2));
					assert(e/curr_edge);
					if(e*curr_edge>EPS)add_edge(curr_p, next_p, h, hn, E, V);
					break;
			}
            if(q1[i][j].second==-1)break;
            curr_p=next_p;
		}
    }
}

int go(int i, vector<set<int> > &E, vvctr &V, vector<bool> &vis, vector<vvctr> &op)
{
    assert(E[i].size());
    vis[i]=true;
	for(set<int>::iterator it=E[i].begin();it!=E[i].end();it++){
        if(vis[*it]){ //found new one
            int k=*it;
            E[i].erase(it);
            op.pb(vvctr(1,V[k]));
			op.back().pb(V[i]);
            vis[i]=false;
            return k;
        } else {
            int k=go(*it, E, V, vis, op);
            assert(k>=0);
            if(k!=i){
                op.back().pb(V[i]);
                E[i].erase(it);
                vis[i]=false;
                return k;
            } else {
                reverse(all(op.back()));
            }
        }
    }
    vis[i]=false;
    E[i].clear();
    return -1;
}

vector<vvctr> poly_intersect(const vvctr &p1, const vvctr &p2)
{
    vector<vvctr> p;
    int n=p1.size(), m=p2.size();
    vvpdi q1, q2;
    find_intersections_of_two_polygons(p1,p2,q1,q2);
    int hn=0;
    map<vctr, int> h; //record all points that occured, h[x]=i means the point x's label is i
    vector<set<int> > E; //record edges that shape an intersection region
//E[i][j]=k means the jth point that the Point i can go (with an overlapped region to the left) to is Point k.
    vvctr V; //record all vertices involved
    
    find_overlapping_edges(p1,p2,q1,h,hn,E,V); //find the edges for the overlapping regions
    find_overlapping_edges(p2,p1,q2,h,hn,E,V);
    vector<bool> vis(hn,false);
    vector<vvctr> op;
    rep(i,hn)
        if(E[i].size())go(i,E,V,vis,op);
    return op;
}

void format(vvctr &a)
{
	int k=0;
	rep(i,a.size())if(a[i]<a[k])k=i;    //找到横坐标最小，若重复则其中纵坐标的顶点
	rotate(a.begin(),a.begin()+k,a.end());//将这个点转到开头
	rep(i,a.size()){
		int j=nxt(i,a.size()),k=nxt(j,a.size());
		if((a[j]-a[i])/(a[k]-a[j])){ //相临两边夹角为0度
			a.erase(a.begin()+j);    //去掉中间的无用点
		}
	}
}

bool check_poly_validity(const vvctr &p){
	rep(i,p.size()-1)
		reu(j,i+2,p.size())
			if(nxt(j,p.size())!=i){
				vctr a(p[i]),b(p[nxt(i,p.size())]),c(p[j]),d(p[nxt(j,p.size())]);
				if(two_segment_intersect(a,b,c,d).first)return false;
				else {
					if((b-a)/(d-c)&&point_on_line(a,c,d)){
						double l=(a&b)+(c&d);
						if((a&c)-l>EPS||(a&d)-l>EPS||(b&c)-l>EPS||(b&d)-l>EPS);
						else return false;
					}
				}
			}
	return true;
}

int main()
{
    srand(time(NULL));
    int n,m=0;
    vector<vvctr> P; //P[i]: 第i个多边形， P[i][j]: 第i个多边形的第j个顶点
    while((cin>>n)&&n){
		P.push_back(vvctr());
        rep(i,n){
            double x,y;
            cin>>x>>y;
            P[m].pb(vctr(x,y));
        }
		if(!check_poly_validity(P[m])){
			printf("该点序不符合条件！自动忽略\n");
			P.pop_back();
		} else {
			format(P[m]);
			m++;
		}
    }
    rep(i,m-1){
        reu(j,i+1,m){
            vector<vvctr> ans(poly_intersect(P[i],P[j]));
			printf("第%d和%d多边形的交集包含%d个多边形\n",i+1,j+1,ans.size());
            rep(i,ans.size())
            {
				printf("多边形%d的顶点序列为：",i+1);
				format(ans[i]);
                rep(j,ans[i].size())
                    print(ans[i][j]);
                printf("\n");
            }
			printf("\n");
        }
    }
	system("pause");
    return 0;
}
