#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

int s[1010];

int find(int i)
{
    if(s[i]==i)return i;
    else return s[i]=find(s[i]);
}

void combine(int u, int v)
{
    s[find(v)]=find(u);
}

int main()
{
	int n,m;
	while(scanf("%d%d",&n,&m)==2)
	{
        for(int i=0;i<n;i++)
                s[i]=i;
	    while(m--)
	    {
	        char c;
	        int u, v;
	        cin>>c>>u>>v;
            switch(c)
            {
                case'Q':
                    cout<<(int)(find(u-1)==find(v-1))<<endl;
                    //cout<<find(u-1)<<' '<<find(v-1)<<endl;
                    break;
                case'U':
                    combine(u-1,v-1);
                    break;
            }
	    }
	}
}
