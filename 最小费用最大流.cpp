/*
用spfa增广的费用流，这里费用的类型为double，流量的类型为int
图是用数组模拟链表搞的, cnt初始值为0
*/
const int MAXN=105;
const int MAXM=50005;
const int inf=1000000000;
const double eps=1e-8;

struct node
{
    int u,v,f;
    double c;
    int next;
};

double dis[MAXN];
int pre[MAXN];
int head[MAXN];
bool vis[MAXN];
node e[MAXM];
int n,m,cnt;
int S,T;


void addedge(int u,int v,int f,double c)
{
    e[cnt].u=u; e[cnt].v=v; e[cnt].c=c; e[cnt].f=f; e[cnt].next=head[u]; head[u]=cnt++;
    e[cnt].u=v; e[cnt].v=u; e[cnt].c=-c; e[cnt].f=0; e[cnt].next=head[v]; head[v]=cnt++;
}

bool spfa()
{
    std::queue<int>q;
    while (!q.empty()) q.pop();
    for (int i=0; i<=T; i++)
    {
	dis[i]=inf; vis[i]=0; pre[i]=-1;
    }
    q.push(S); vis[S]=1; dis[S]=0;
    while (!q.empty())
    {
	int u=q.front(); q.pop();
	for (int now=head[u]; now!=-1; now=e[now].next)
	{
	    int v=e[now].v;
	    if (e[now].f>0&&dis[v]>dis[u]+e[now].c+eps)
	    {
		dis[v]=dis[u]+e[now].c;
		pre[v]=now;
		if (!vis[v])
		{
		    q.push(v);
		    vis[v]=1;
		}
	    }
	}
	vis[u]=false;
    }
    return (dis[T]<inf);
}

double MCMF()
{
    double mincost=0;
    int maxflow=0;
    while (spfa())
    {
	int nec=inf;
	for (int now=pre[T]; now!=-1; now=pre[e[now].u])
	    nec=std::min(nec,e[now].f);
	mincost+=nec*dis[T];
	maxflow+=nec;
	for (int now=pre[T]; now!=-1; now=pre[e[now].u])
	{
	    e[now].f-=nec;
	    e[now^1].f+=nec;
	}
    }
    return mincost;
}
//优化spfa版本，如果上面的超时就用下面这个
const int MAXN=1010;
const int MAXM=25000;
const int inf=100000000;
struct node
{
	int v, next;
	int flow;
	int cost;
}E[MAXM*2];

bool vis[MAXN];
int head[MAXN], que[MAXN+1], dis[MAXN];
int N, M, S, T, cnt, ans;

void addedge(int u, int v, int a, int b, int c)
{
	E[cnt].v=v; E[cnt].flow=a; E[cnt].cost=c; E[cnt].next=head[u]; head[u]=cnt++;
	E[cnt].v=u; E[cnt].flow=b; E[cnt].cost=-c; E[cnt].next=head[v]; head[v]=cnt++;
}

int dfs(int u, int low)
{
	int ret=0, tmp;
	if (u==T) return low;
	vis[u]=true;
	for (int now=head[u]; now!=-1&&ret<low; now=E[now].next)
	{
		int v=E[now].v; if (vis[v]) continue;
		if (E[now].flow&&dis[v]==dis[u]+E[now].cost)
		{
			tmp=dfs(v, min(E[now].flow, low-ret));
			ans+=tmp*E[now].cost; ret+=tmp;
			E[now].flow-=tmp; E[now^1].flow+=tmp;
		}
	}
	return ret;
}

bool extend()
{
	for (int i=0; i<=N+1; i++) dis[i]=inf, vis[i]=false;
	dis[S]=0; vis[S]=true; que[0]=S;
	for (int front=0, rear=1; front!=rear; front=(front==MAXN)?0:front+1)
	{
		int u=que[front]; vis[u]=false;
		for (int now=head[u]; now!=-1; now=E[now].next)
		{
			int v=E[now].v, f=E[now].flow, c=E[now].cost;
			if (f>0&&dis[v]>dis[u]+c)
			{
				dis[v]=dis[u]+c;
				if (!vis[v])
				{
					vis[v]=true;
					que[rear]=v; rear=(rear==MAXN)?0:rear+1;
				}
			}
		}
	}
	if (dis[T]>=inf) return false;
	do
	{
		for (int i=0; i<=N+1; i++) vis[i]=false;
	}while (dfs(S, inf));
	return true;
}
/*
最小费用最大流模板
执行 solve(s, t) 后，最大流保存在 flow 中，最小费用保存在 cost 中
*/
const int MAXN = 2005;
const int INF = 2100000000;

struct Edge{
	int from, to, cap, flow, cost;
	Edge(int fr, int t, int c, int fl, int co){
		from = fr; to = t; cap = c; flow = fl; cost = co;
	}
};

struct MinCostMaxFlow{
	vector<Edge> E;
	vector<int> G[MAXN];
	int s, t;
	int flow, cost;
	void clear_graph(){
		E.clear();
		for(int i = 0; i < MAXN; i++) G[i].clear();
	}
	void clear_flow(){
		for(int i = 0; i < E.size(); i++)
			E[i].flow = 0;
	}
	void add_edge(int from, int to, int cap, int cost){
		int m = E.size();
		E.push_back(Edge(from, to, cap, 0, cost));
		E.push_back(Edge(to, from, 0, 0, -cost));
		G[from].push_back(m);
		G[to].push_back(m + 1);
	}
	void solve(int S, int T){
		s = S; t = T;
		queue<int> Q;
		bool inq[MAXN];
		int d[MAXN], pre[MAXN];
		flow = cost = 0;
		while(true){
			memset(inq, 0, sizeof(inq));
			for(int i = 0; i < MAXN; i++) d[i] = INF;
			d[s] = 0;
			Q.push(s);
			while(!Q.empty()){
				int x = Q.front(); Q.pop(); inq[x] = 0;
				for(int i = 0; i < G[x].size(); i++){
					Edge& e = E[G[x][i]]; 
					int y = e.to;
					if(e.cap > e.flow && d[x] + e.cost < d[y]){
						d[y] = d[x] + e.cost;
						pre[y] = G[x][i];
						if(!inq[y]){
							inq[y] = true;
							Q.push(y);
						}
					}
				}
			}
			if(d[t] == INF) break;
			int mi = INF;
			for(int x = t; x != s; x = E[pre[x]].from)
				mi = min(mi, E[pre[x]].cap - E[pre[x]].flow);
			for(int x = t; x != s; x = E[pre[x]].from){
				E[pre[x]].flow += mi;
				E[pre[x] ^ 1].flow -= mi;
			}
			flow += mi;
			cost += mi * d[t];
		}
	}
};
