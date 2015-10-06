#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#include <cstdlib>
using namespace std;
#define MAXN 1000000
#define out(x) cout<<(#x)<<'='<<x<<endl
struct AC{
    int tot;
    struct node{
        int cnt, f, ch[26];
        node(bool flag){
            memset(ch,-1,26*sizeof(int));
            cnt=0; f=-1;
        }
        node(){}
    } a[MAXN];
    void clear(){
        tot=1;
        a[0]=1;
    }
    void insert(const string &s){
        int now=0;
        for(int i=0; i<s.size(); i++){
            char t=s[i]-'a';
            node &v=a[now];
            if(~v.ch[t])now=v.ch[t];
            else {
                v.ch[t]=tot;
                a[tot]=1;
                now=tot++;
            }
        }
        a[now].cnt++;
    }
    void gao(){
		queue<int> q;
		q.push(0);
		while(!q.empty()){
			int i=q.front();
			q.pop();
            node &v=a[i];
            for(int j=0; j<26; j++)if(~v.ch[j]){
				q.push(v.ch[j]);
                node &u=a[v.ch[j]];
                int k=v.f;
                for(; ~k; k=a[k].f){
                    if(~a[k].ch[j]){
                        u.f=a[k].ch[j];
                        break;
                    }
                }
                if(k==-1)u.f=0;
                //u.cnt+=a[u.f].cnt;
            }
        }
    }
    int find(const string &s){
        int now=0, res=0;
        for(int i=0; i<s.size(); i++){
            char t=s[i]-'a';
            while(~now && !~a[now].ch[t])
                now=a[now].f;
            now=(~now)?a[now].ch[t]:0;
            for(int tt=now; ~tt && ~a[tt].cnt; tt=a[tt].f){
                res+=a[tt].cnt;
                a[tt].cnt=-1;
            }
        }
        return res;
    }
} aacc;
char buf[1000010];
int main(){
    int T;
    scanf("%d",&T);
    for(int tt=0; tt<T; tt++){
        aacc.clear();
        int n;
        scanf("%d ",&n);
        while(n--){
            gets(buf);
            aacc.insert(buf);
        }
        aacc.gao();
        gets(buf);
        printf("%d\n",aacc.find(buf));
    }
}

