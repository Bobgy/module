/*
Dinic 最大流
FL 为流量类型，可以修改，MAXN 为最大点数
创建
Dinic D;
清除全图
D.clear_graph();
清除图中流量
D.clear_flow();
从 from 到 to 添加一条容量为 cap 的边
D.add_edge(from, to, cap);
从 s 到 t 计算最大流
D.max_flow(s, t);
*/

typedef long long FL;
const int MAXN = 20005;
const FL INF = 2100000000;

struct Edge{
	int from, to;
	FL cap, flow;
	Edge(int fr, int t, FL c, FL fl){
		from = fr; to = t; cap = c; flow = fl;
	}
};
struct Dinic{
	vector<int> G[MAXN];
	vector<Edge> E;
	int s, t;
	int cur[MAXN], d[MAXN];
	void clear_graph(){
		E.clear();
		for(int i = 0; i < MAXN; i++)
			G[i].clear();
	}
	void clear_flow(){
		for(int i = 0; i < E.size(); i++)
			E[i].flow = 0;
	}
	void add_edge(int from, int to, FL cap){
		int m = E.size();
		E.push_back(Edge(from, to, cap, 0));
		E.push_back(Edge(to, from, 0, 0));
		G[from].push_back(m);
		G[to].push_back(m + 1);
	}
	bool bfs(){
	    bool vis[MAXN];
		memset(vis, 0, sizeof(vis));
		queue<int> Q;
		Q.push(s); d[s] = 0; vis[s] = 1;
		while(!Q.empty()){
			int x = Q.front(); Q.pop();
			for(int i = 0; i < G[x].size(); i++){
				Edge &e = E[G[x][i]];
				if(vis[e.to] == 0 && e.cap > e.flow){
					vis[e.to] = 1;
					d[e.to] = d[x] + 1;
					Q.push(e.to);
				}
			}
		}
		return vis[t];
	}
	FL dfs(int x, FL mi){
		if(x == t || mi == 0) return mi;
		FL sum = 0;
		for(int &i = cur[x]; i < G[x].size(); i++){
			Edge &e = E[G[x][i]];
			if(d[x] + 1 == d[e.to]){
				FL f = dfs(e.to, min(mi, e.cap - e.flow));
				if(f > 0){
					e.flow += f;
					E[G[x][i] ^ 1].flow -= f;
					sum += f;
					mi -= f;
					if(mi == 0) break;
				}
			}
		}
		return sum;
	}
	FL max_flow(int s, int t){
		this->s = s; this->t = t;
		FL flow = 0;
		while(bfs()){
			memset(cur, 0, sizeof(cur));
			flow += dfs(s, INF);
		}
		return flow;
	}
};

