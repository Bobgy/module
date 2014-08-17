#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <string>
using namespace std;
#define MAXN 11234
#define REP(i,n) for(int i=0; i<(int)n; i++)
#define RER(i,l,r) for(int i=l; i<=r; i++)
#define out(x) cout<<(#x)<<"="<<x<<endl
char s[MAXN], buf[1000];
struct node{
	int ex, p[2];
} a[MAXN*80];
int tot;
const char *c[26]={
	"01", "1000", "1010", "100", "0", "0010", "110", "0000",
	"00", "0111", "101", "0100", "11", "10", "111", "0110",
	"1101", "010", "000", "1", "001", "0001", "011", "1001",
	"1011", "1100"
};
void insert(int x, string &s){
	REP(i,s.size()){
		int t=s[i]-'0';
		if(~a[x].p[t])x=a[x].p[t];
		else {
			x=a[x].p[t]=tot;
			a[x].p[0]=a[x].p[1]=-1;
			a[x].ex=0;
			tot++;
		}
	}
	a[x].ex++;
}
void clear(){
	a[0].p[0]=a[0].p[1]=-1;
	a[0].ex=0; tot=1;
}
int dp[MAXN];
int main(){
	int d;
	scanf("%d ", &d);
	while(d--){
		clear();
		gets(s);
		int n=strlen(s), m;
		scanf("%d ", &m);
		REP(i,m){
			string st;
			gets(buf);
			int tm=strlen(buf);
			REP(j,tm)
				st+=c[buf[j]-'A'];
			insert(0, st);
		}
		memset(dp, 0, n*sizeof(int)+100);
		dp[0]=1;
		REP(i,n)s[i]=s[i]=='-'?1:0;
		REP(i,n)if(dp[i]){
			int x=0;
			for(int j=i; j<n && ~a[x].p[s[j]]; j++){
				x=a[x].p[s[j]];
				dp[j+1]+=a[x].ex*dp[i];
			}
		}
		printf("%d\n", dp[n]);
	}
}
