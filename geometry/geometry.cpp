#include <bits/stdc++.h>
using namespace std;
#define REP(i,n) for(int i=0; i<int(n); i++)
#define pb push_back
typedef double flt;
const flt PI = acos(-1.0);
const flt EPS = 1e-8, EPS2 = 1e-7;
//fcmp(x, y) is the sign{0, -1, 1} of x-y
int fcmp(flt x, flt y, flt EPS=EPS){
	return fabs(x-y)<EPS ? 0 : (x>y ? 1 : -1);
}
template <class T> flt sqr(T x) {return x*x;}
struct Pt{ //Point
	flt x, y;
	void read() {scanf("%lf%lf",&x,&y);}
	Pt(flt x, flt y):x(x),y(y){}
	Pt(){}
	Pt operator+(Pt r) const {return Pt(x+r.x,y+r.y);}
	Pt operator-(Pt r) const {return Pt(x-r.x,y-r.y);}
	Pt rot(flt a) const {return Pt(x*cos(a)-y*sin(a), x*sin(a)+y*cos(a));} // rotate a rad, counter-clockwise
	flt operator*(Pt r) const {return x*r.x+y*r.y;} //dot product
	flt operator^(Pt r) const {return x*r.y-y*r.x;} //cross product
	flt operator!() const {return hypot(x,y);}      //length
	friend Pt operator*(flt k, Pt r) {return Pt(r.x*k,r.y*k);} //num product
} o;
typedef Pt Vec; //Vector and Point are the same
struct Cir{ //Circle
	Pt o;   //center
	flt r;  //radius
	Cir(Pt o, flt r):o(o),r(r){}
	Cir(){}
	void read(){
		o.read();
		scanf("%lf",&r);
	}
	flt len() const {return 2.0*(PI*r);}
};
struct Seg{
	Pt u, v;
	Seg(Pt u, Pt v):u(u),v(v){}
	flt len() const {return !(u-v);}
};

//solve function A*x^2+B*x+C=0
//returns: -1 -> infinite solutions, 0 -> no solutions, 1 -> A==0 && exist solution, 2 -> A!=0
//x0 and x1 will be assigned the two roots if solutions are found
int solve(flt A, flt B, flt C, flt &x0, flt &x1){
	if(fcmp(A,0)==0){
		if(fcmp(B,0)==0){
			x0=x1=0;
			return fcmp(C,0)==0 ? -1 : 0;
		} else {
			x0=x1=-C/B;
			return 1;
		}
	}
	B*=0.5;
	flt D=B*B-A*C;
	if(fcmp(D,0)<0)return 0;
	D=sqrt(max(D,0.0));
	x0=(-B-D)/A;
	x1=(-B+D)/A;
	return 2;
}

// line function: k*s.v+(1-k)*s.u
// k belongs to [0, 1] is the segment
// k=0 is s.u, k=1 is s.v
// find the part of segment that is inside the circle: k belongs to [max(0.0, k0), min(1.0, k1)]
// returns whether line s.u s.v intersects circle c (includes tangency)
bool intersect(Seg s, Cir c, flt &k0, flt &k1){
	Pt u=s.u, v=s.v, o=c.o;
	flt A, B, C;
	A = sqr(v-u);
	B = (v-u)*(u-o)*2.0;
	C = sqr(u-o)-sqr(c.r);
	return solve(A, B, C, k0, k1)==2;
}

// intersect circle with circle
// return 0: apart, 1: c0 includes c1, 2: c1 includes c0, 3: intersect
int intersectCC(Cir c0, Cir c1, Pt &p1, Pt &p2){
	flt dis=!(c0.o-c1.o);
	if(fcmp(dis,c0.r+c1.r) > 0)return 0; //apart
	if(fcmp(dis+c1.r,c0.r) < 0)return 1; //c0 includes c1
	if(fcmp(dis+c0.r,c1.r) < 0)return 2; //c1 includes c0
	Pt u, v;
	flt t = (sqr(c0.r)-sqr(c1.r)) / sqr(dis) + 1.0, k0, k1;
	u = c0.o + 0.5*t*(c1.o-c0.o);
	v = u + (c1.o-c0.o).rot(PI*0.5);
	if (intersect(Seg(u,v), c0, k0, k1) == 0) return 0;
	p1 = k0*v + (1-k0)*u;
	p2 = k1*v + (1-k1)*u;
	return 3;
}

