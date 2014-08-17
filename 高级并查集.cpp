#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

const int maxn=200010;

int r=0;
int s[maxn*3],pos[maxn],sz[maxn*3];
bool dir[maxn*3];

int find(int i)
{
    if(s[i]==i)return i;
    int t=find(s[i]);
    if(t!=s[i])dir[i]^=dir[s[i]],s[i]=t;
    return t;
}

int find_size(int u)
{
    int t;
    if((t=find(u))==u)return sz[u];
    else return sz[u]=sz[t];
}

void link(int u, int v)
{
    u=pos[u], v=pos[v];
    int i=find(u), j=find(v);
    if(i==j)return;//!assert
    if(sz[i]>sz[j]){swap(u,v);swap(i,j);}
    sz[i]+=sz[j];
    dir[j]=!(dir[u]^dir[v]);
    s[j]=i;
}

void disconnect(int u)
{
    sz[find(pos[u])]--;
    pos[u]=++r;
    s[r]=r;
    sz[r]=1;
}

int query_dir(int u, int v) //0 same, 1 different, -1 unknown
{
    u=pos[u], v=pos[v];
    if(find(u)==find(v))
    {
        if(u==find(u))return dir[v];
        else if(v==find(v))return dir[u];
        else return dir[u]!=dir[v];
    } else return -1;
}

int main()
{
	int n,m;
	while(scanf("%d%d",&n,&m)==2)
	{
        for(int i=0;i<n;i++)
            s[i]=i,pos[i]=i,sz[i]=1,dir[i]=0;
        r=n-1;
	    while(m--)
	    {
	        char c;
	        int u, v;
	        getchar();
	        c=getchar();
            switch(c)
            {
                case'Q':
                    scanf("%d%d",&u,&v);
                    switch(query_dir(u-1,v-1))
                    {
                        case 0:printf("Same\n");break;
                        case 1:printf("Different\n");break;
                        case -1:printf("Unknown\n");break;
                    }
                    //cout<<find(u-1)<<' '<<find(v-1)<<endl;
                    break;
                case'L':
                    scanf("%d%d",&u,&v);
                    link(u-1,v-1);
                    break;
                case'D':
                    scanf("%d",&u);
                    disconnect(u-1);
                    break;
                case'S':
                    scanf("%d",&u);
                    printf("%d\n",find_size(pos[u-1]));
                    break;
            }
	    }
	}
}
