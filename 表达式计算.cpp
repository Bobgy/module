#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
using namespace std;
#define REP(i,n) for(int i=0; i<int(n); i++)
#define out(x) cout<<(#x)<<'='<<x<<endl
string num[100], op[100], n2[100];
int ss[256];
int t1, t2;
bool ex(char c, const char *p){
	for(int i=0; p[i]; i++)
		if(c==p[i])return 1;
	return 0;
}
bool ex(string &s, const char *p){
	assert(s.size());
	if(s.size()>1)return 0;
	for(int i=0; p[i]; i++)
		if(s[0]==p[i])return 1;
	return 0;
}
int fdig(string &s, int i){
	for(; isdigit(s[i]) || s[i]=='.'; i++);
	return i;
}
void add(const string &op, string &n1, string &n2){
	if(n2[0]=='-')n1=n1+(op=="+"?"-":"+")+n2.substr(1,n2.size()-1);
	else n1=n1+op+n2;
}
void calc(string &op, string &n1, string &n1p, string &n2, string &n2p){
	if(ex(op, "*/")){
		n1p=n1p+"*"+n2;
		n2p=n1+"*"+n2p;
		add(string(op=="*"?"+":"-"), n1p, n2p);
		n1p="("+n1p+")";
		if(op=="/")n1p+="/"+n2+"^2";
	} else add(op, n1p, n2p);
	add(op, n1, n2);
}
int main(){
	ss['*']=ss['/']=2;
	ss['+']=ss['-']=1;
	string f;
	while(cin>>f){
		t1=t2=0;
		f="("+f+")";
		for(int i=0; i<f.size(); i++){
			if(ex(f[i],"(l")){
				if(f[i]=='l'){
					i+=2;
					op[t2++]="ln(";
				} else op[t2++]=f[i];
			} else {
				bool is_num=0;
				if(ex(f[i], "+-x") || isdigit(f[i])){
					if(ex(f[i],"+-")){
						if(f[i-1]=='('){
							int t=fdig(f,i+1);
							num[t1]=f.substr(i, t-i);
							n2[t1++]="0";
							i=t-1;
							is_num=1;
						}
					} else {
						if(f[i]=='x'){
							num[t1]=f[i];
							n2[t1++]="1";
						} else {
							int t=fdig(f,i);
							num[t1]=f.substr(i, t-i);
							n2[t1++]="0";
							i=t-1;
						}
						is_num=1;
					}
				}
				if(is_num)continue;
				if(ex(f[i], "+-*/")){
					if(ss[op[t2-1][0]]>=ss[f[i]])
						t1--, t2--, calc(op[t2], num[t1-1], n2[t1-1], num[t1], n2[t1]);
					op[t2++]=f[i];
				} else {
					assert(f[i]==')');
					while(!ex(op[--t2][0], "l("))
						t1--, calc(op[t2], num[t1-1], n2[t1-1], num[t1], n2[t1]);
					if(op[t2]=="ln("){
						n2[t1-1]="("+n2[t1-1]+")/("+num[t1-1]+")";
					} else n2[t1-1]="("+n2[t1-1]+")";
					num[t1-1]=op[t2]+num[t1-1]+")";
				}
			}
		}
		assert(t2==0 && t1==1);
		cout<<n2[0].substr(1,n2[0].size()-2)<<endl;
	}
}
