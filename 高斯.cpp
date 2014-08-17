#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cassert>

using namespace std;
/*
class Z2 {
public:
    int v;
    Z2(int x){if(x)v=1;else v=0;}
    Z2(long long x){if(x)v=1; else v=0;}
    Z2(){v=0;}
    Z2(const Z2 &x):v(x.v){}
    void print()const{
        printf("%2d",v);
    }
} ZERO(0);
inline Z2 operator+(const Z2 &a, const Z2 &b){
    return a.v ^ b.v;
}
inline Z2 operator-(const Z2 &x){
    return x;
}
inline Z2 operator-(const Z2 &a, const Z2 &b){
    return a.v ^ b.v;
}
inline Z2 operator*(const Z2 &a, const Z2 &b){
    return a.v & b.v;
}
inline Z2 operator*=(Z2 &a, const Z2 &b){
    return a = a * b;
}
inline Z2 operator+=(Z2 &a, const Z2 &b){
    return a = a + b;
}
inline int sgn(Z2 x){
    return x.v ? 1 : 0;
}
inline Z2 operator/(const Z2 &a, const Z2 &b){
    assert(b.v); //除数非零
    return a.v;
}
inline bool operator<(const Z2 &a, const Z2 &b){
    return a.v < b.v;
}
typedef Z2 Num;
*/
const int p=23;
class modp{
public:
    int v;
    modp(int x){v=x%p;}
    modp(){v=0;}
    modp(const modp &x):v(x.v){}
    void print()const{printf("%3d",v);}
} ZERO(0), ONE(1);
inline modp operator+(const modp &a, const modp &b){
    return (a.v + b.v) % p;
}
inline modp operator-(const modp &x){
    return (-x.v + p) % p;
}
inline modp operator-(const modp &a, const modp &b){
    return (a.v - b.v + p) % p;
}
inline modp operator*(const modp &a, const modp &b){
    return (a.v * b.v) % p;
}
inline modp operator*=(modp &a, const modp &b){
    return a = a * b;
}
inline modp operator^(const modp &a, int n)
{
    modp t(a), res(ONE);
    for(; n; n>>=1, t*=t)
        if(n&1)res*=t;
    return res;
}
inline modp operator+=(modp &a, const modp &b){
    return a = a + b;
}
inline int sgn(modp x){
    return x.v ? 1 : 0;
}
inline modp operator/(const modp &a, const modp &b){
    assert(b.v); //除数非零
    return a * (b ^ (p-2));
}
inline bool operator<(const modp &a, const modp &b){
    return a.v < b.v;
}
typedef modp Num;
typedef vector<Num> VN;
typedef vector<VN> VVN;
#define REP(i,n) for(int i=0; i<int(n); i++)
#define eps 1e-10
inline int sgn(double x){
    if(fabs(x) < eps)return 0;
    else return x > 0 ? 1 : -1;
}

class Matrix{
public:
    VVN v;
    vector<size_t> f; //records the position of the first one in a row, -1 means all zeros
    VN x; //answer to solve 
    VN &operator[](size_t i){return v[i];}
    Matrix(size_t n, size_t m, bool one=0){
        v=VVN(n,VN(m,0));
        if(one){
            int nn=min(n,m);
            REP(i, nn)v[i][i]=1;
        }
    }
    Matrix(const VVN &d):v(d){}
    Matrix(const Matrix &A):v(A.v){}
    
    size_t size() const {return v.size();}
    
    void print(void) const {
        for(size_t i = 0; i < v.size(); i++){
            for(size_t j = 0; j < v[i].size(); j++)
                v[i][j].print();
            printf("\n");
        }
    }
    
    bool isSquare() const {
        if(v.size()==0 || (v.size()==v[0].size()) )return true;
        else return false;
    }
    
    //return value means whether this method is working properly
    bool transpose(void){
        if(!isSquare())return false;
        for(size_t i = 0; i < v.size(); i++){
            for(size_t j = i + 1; j < v.size(); j++)
                swap(v[i][j], v[j][i]);
        }
        return true;
    }
    
    void swapRow(size_t i, size_t j){swap(v[i], v[j]);}
    void mulRow(size_t i, Num times){REP(j, v[i].size())v[i][j] *= times;}
    //add times*Row i to row j
    void addMulRow(Num times, size_t i, size_t j)
    {REP(k,v[i].size())v[j][k]+=v[i][k]*times;}
    
    void toReducedRowEchelonForm(){
        if(v.size()==0)return;
        f.clear();
        int n=v.size(), m=v[0].size();
        f.resize(n, -1);
        int r=0, c=0; //rth row, cth column
        for(;r<n && c<m; r++, c++){
            Num maxv=v[r][c];
            size_t row=r;
            for(size_t i=r+1; i<n; i++)
                if(maxv < v[i][c])
                    maxv = v[row = i][c];
            if(sgn(maxv)==0){
                r--;
                continue;
            }
            f[r]=c;
            swapRow(r, row);
            for(size_t i=r+1; i<n; i++){
                Num t=-v[i][c]/maxv;
                if(sgn(t))addMulRow(t, r, i);
            }
            mulRow(r, 1/maxv);
        }
    }
    
    // -1无解， 0唯一解， >=1自由元个数，有解的话x中存某一组解
    int solve(){
        if(v.size()==0)return 0;
        int n=v.size(), m=v[0].size();
        x.resize(m-1);
        int k=m-2;
        int cnt=0;
        for(int i=n-1; i>=0; i--){
            if(f[i]==-1)continue;
            if(f[i]==m-1)return -1;
            Num sum=v[i][m-1];
            for(int j=m-1; j>k; j--)
                sum=sum - x[j] * v[i][j];
            for(int j=k; j>f[i]; j--)
                x[j]=ZERO, cnt++;
            k=f[i];
            x[k--]=sum;
        }
        for(int j=k; j>=0; j--)
        	x[j]=ZERO, cnt++;
        return cnt;
    }
};
