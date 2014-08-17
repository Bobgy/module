#include <cstdio>
#include <vector>
#include <cassert>
#include <ctime>
#include <cstdlib>

using namespace std;

template<class T>
class prime_siever{
public:
    vector<T> p;
    //find prime numbers not greater than n
    void work(T n){
        p.clear();
        vector<bool> f(n+1,true);
        for(T i=2;i<=n;i++){
            if(f[i]){
                p.push_back(i);
                for(T j=i+i;j<=n;j+=i)f[j]=false;
            }
        }
    }
};

typedef long long LL;

inline LL add(LL a, LL b, LL mod){
    LL res=a+b;
    res%=mod;
    return res;
}

//复杂度log2(min(a,b)),避免溢出,用于替换原来的mul
inline LL mul(LL a, LL b, LL mod){
    a=a%mod; b=b%mod;
    LL res=0; if(a<b)swap(a,b);
    for(;b;b>>=1,a=add(a,a,mod))
        if(b&1)res=add(res,a,mod);
    return res;
}

//普通mul
/*
inline LL mul(LL a, LL b, LL mod){
    return (long long)a*b%mod;
}
*/

LL modExp(LL a, LL n, LL mod){
    LL res=1;
    a=a%mod;
    for(;n;n>>=1,a=mul(a,a,mod))
        if(n&1)res=mul(res,a,mod);
    return res;
}

bool mr_test(LL a, LL n, LL d, int k){
    LL r=modExp(a,d,n);
    if(r==1)return true;
    while(k--){
        if(r==n-1)return true;
        r=mul(r,r,n);
    }
    return false;
}

bool easy_prime(LL n){
    switch(n){
        case 2: case 3: case 5: case 7: case 11: case 13: case 17: return true;
        default: return false;
    }
}

bool easy_comp(LL n){
    if(n%2==0||n%3==0||n%5==0||n%7==0||n%11==0||n%13==0||n%17==0)return true;
    return false;
}

//!!if n < 1,373,653, it is enough to test a = 2 and 3;         //verified
//!!if n < 9,080,191, it is enough to test a = 31 and 73;       //verified
//!!if n < 4,759,123,141, it is enough to test a = 2, 7, and 61;//mostly verified
//!!if n < 1,122,004,669,633, it is enough to test a = 2, 13, 23, and 1662803;
//!!if n < 2,152,302,898,747, it is enough to test a = 2, 3, 5, 7, and 11;
//!!if n < 3,474,749,660,383, it is enough to test a = 2, 3, 5, 7, 11, and 13;
//!!if n < 341,550,071,728,321, it is enough to test a = 2, 3, 5, 7, 11, 13, and 17.

const int prime_num=4, p[]={2,13,23,1662803};
bool miller_rabin_fixed(LL n){
    if(n==0||n==1)return false;
    if(easy_prime(n))return true;
    if(easy_comp(n))return false;
    int k=0; LL d=n-1;
    while(~d&1)d>>=1,k++;
    for(int i=0;i<prime_num;i++){
        if(p[i]==n)return true;
        if(!mr_test(p[i]%n,n,d,k))return false;
    }
    return true;
}

bool miller_rabin_random(LL n, int time){
    if(n==0||n==1)return false;
    if(easy_prime(n))return true;
    if(easy_comp(n))return false;
    int k=0; LL d=n-1;
    while(~d&1)d>>=1,k++;
    for(int i=0;i<time;i++){
        LL p=rand()%(n-1)+1;
        if(!mr_test(p%n,n,d,k))return false;
    }
    return true; //probability=1-(1/4)^time
}

int main(){
    //srand(time(0));
    LL a,b,l,u; int cn=0;
    while(scanf("%lld%lld%lld%lld",&a,&b,&l,&u)==4){
        int cnt=0; cn++;
        for(LL i=l;i<=u;i++)
            if(miller_rabin_fixed(a*i+b))cnt++;
        printf("Case %d: %d\n",cn,cnt);
    }
}

int main(){
    srand(time(0));
    prime_siever<int> obj;
    int t0=clock();
    int n=9000000;
    obj.work(n);
    int t1=clock();
    printf("Sieve used %.2lf seconds\n",(t1-t0)/(double)CLOCKS_PER_SEC);
    vector<int> &p=obj.p;
    t0=clock();
    for(int i=2, j=0;i<=n;i++){
        while(j<p.size()&&p[j]<i)j++;
        if(miller_rabin_fixed(i)){
            if(j<p.size()&&p[j]!=i){
                printf("T %d %d\n",p[j],i);
                break;
            }
        } else {
            //assert(j<p.size()&&p[j]!=i);
            if(j<p.size()&&p[j]==i){
                printf("F %d %d\n",p[j],i);
                break;
            }
        }
    }
    t1=clock();
    printf("Miller-Rabin used %.2lf seconds\n",(t1-t0)/(double)CLOCKS_PER_SEC);
}

//fast
LL gcd(LL a, LL b){
    if(a<b)swap(a,b); //now a>=b
    if(a&1){
        if(b&1)return gcd(b, a-b);
        else return gcd(a, b>>1);
    } else {
        if(b&1)return gcd(a>>1, b);
        else return gcd(a>>1, b>>1)<<1;
    }
}

LL gcdNormal(LL a, LL b){
    return b?a:gcd(b, a%b);
}

