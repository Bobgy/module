/*
无向图：割点/桥/双连通分量
有多少个low[y] >= num[x]，那么去掉 x 这个割点之后连通块就增加多少，根是割点的时候应该 -1
此处双连通分量指『点双连通分量』，即任意两点间有至少两条点不重复的路径，割点属于至少两个『点双连通分量』
『边双连通分量』即任意两点间有至少两条边不重复的路径，求法：删掉所有的桥，剩余的每个连通分量就是『边双连通分量』
*/
const int N = 1005;
vector<int> G[N];

struct Tarjan{
	int num[N], low[N], fa[N], add[N], clk;
	bool iscut[N];
	stack<int> S;
	void dfs(int x){
		num[x] = low[x] = ++clk;
		add[x] = 0;
		S.push(x);  // 不需求BCC记得将栈去掉
		for(int i = 0; i < G[x].size(); i++){
			int y = G[x][i];
			if(num[y] == 0){
				fa[y] = x; dfs(y);
				// 桥
				if(low[y] > num[x]) cout << x << " to " << y << " is a bridge" << endl;
				if(low[y] >= num[x]){
					add[x]++;
					// 双连通分量
					vector<int> bcc; bcc.push_back(x);
					do{
						bcc.push_back(S.top()); S.pop();
					}while(bcc.back() != y);
					// 此时 bcc 中为一个双连通分量
				}
				low[x] = min(low[x], low[y]);
			}
			else if(y != fa[x])
				low[x] = min(low[x], num[y]);
		}
		if(fa[x] < 0) add[x]--;
		// add[x] 表示将 x 删掉后连通分量增加多少
		if(add[x] > 0) iscut[x] = true;
	}
	int solve(int n){
		memset(num, 0, sizeof(num));
		memset(iscut, 0, sizeof(iscut));
		int ret = clk = 0;
		for(int i = 1; i <= n; i++) if(num[i] == 0){
			fa[i] = -1; dfs(i); ret++;
		}
		return ret;  // 返回连通分量个数
	}
};
