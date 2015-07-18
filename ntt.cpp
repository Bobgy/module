#include<algorithm>
using namespace std;
typedef long long LL;
LL pm(LL a,LL n,LL m){
    LL r=1;
    for(;n;n>>=1,a=a*a%m)
        if(n&1)r=r*a%m;
    return r;
}
//和FFT类似,仅用于计算卷积,在FFT碰到精度问题或超时时可以考虑换用NTT
//注意传入的n必须为2的幂次,并且计算的结果都是mod P下的结果,
//如果数域范围不够大,可以用多个(P,g)分别计算,再用中国剩余定理还原结果
//如果题目中模的数比较不常见,如果模的数是素数p,且p-1有很多因子2,很可能
//就要用NTT, 几个可替换的(P,g)对:
//(2113929217,5),(1811939329,13),(2130706433,3)
const LL P=2013265921,g=31;
void ntt(LL *a,size_t n,bool inv=false){
    // inv为true时表示逆运算;
    LL w=1,d=pm(g,(P-1)/n,P),t;
    size_t i,j,c,s;
    if(inv){
        for(i=1,j=n-1;i<j;swap(a[i++],a[j--]));
        for(t=pm(n,P-2,P),i=0;i<n;++i)a[i]=a[i]*t%P;
    }
    for(s=n>>1;s;s>>=w=1,d=d*d%P)
    for(c=0;c<s;++c,w=w*d%P)
    for(i=c;i<n;i+=s<<1){
        a[i|s]=(a[i]+P-(t=a[i|s]))*w%P;
        a[i]=(a[i]+t)%P;
    }
    for(i=1;i<n;++i){
        for(j=0,s=i,c=n>>1;c;c>>=1,s>>=1)j=j<<1|s&1;
        if(i<j)swap(a[i],a[j]);
    }
}
// 计算卷积姿势，
// 比如计算a[0..n-1]和b[0..m-1]的卷积:c[0..n+m-1]
// int l=2;
// for(;l<n+m-1;l<<=1);
// ntt(a,l);ntt(b,l);
// for(int i=0;i<l;++i)c[i]=a[i]*b[i];
// ntt(c,l,true);

