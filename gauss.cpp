#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
//#define DEBUG
typedef double flt;
const flt eps=1e-9;
const int MAXN=512, MAXM=512;

flt e[MAXN][MAXM], x[MAXM];
int pos[MAXM];

//n*(m+1) matrix
//-1 means no solution; otherwise return rank
int solve(int n, int m){
    int r=0;
    //c for column, r for row
    for(int c=0,i,j,k;c<=m && r<n;++c){
        for(i=k=r;i<n;++i)if(fabs(e[i][c])>fabs(e[k][c]))k=i;
        if(k!=r)
            for(j=c;j<=m;++j)swap(e[k][j],e[r][j]);
        if(fabs(e[r][c])<eps)continue;
        pos[r]=c;
        for(i=r+1;i<n;++i){
            flt t=-e[i][c]/e[r][c];
            for(int j=c;j<=m;++j)e[i][j]+=t*e[r][j];
        }
        r++;
    }
#ifdef DEBUG
    REP(i,n)REP(j,m+1)printf("%4.2f%c",(double)e[i][j],j==m?'\n':' ');
    puts("=========");
#endif
    if(r>0 && pos[r-1]==m)return -1; //no solution
    for(int i=0;i<m;++i)x[i]=0;
    for(int i=r-1;i>=0;--i){
        int c=pos[i];
        x[c]=e[i][m]/e[i][c];
        for(int j=0;j<i;++j)e[j][m]-=e[j][c]*x[c];
    }
    return r;
}
