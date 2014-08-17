/*
Tarjan 强连通分量，点编号从 1 到 n
第 i 个点的 scc 编号保存在 col[i] 中，总 scc 个数为 col_cnt
const int N = 10000;
vector<int> G[N];
*/
struct Tarjan{
	int num[N], low[N], col[N], clk, col_cnt;
	int stk[N], top;
	void dfs(int x){
		num[x] = low[x] = ++clk;
		stk[++top] = x;
		for(int i = 0; i < G[x].size(); i++){
			int y = G[x][i];
			if(num[y] == 0){
				dfs(y); low[x] = min(low[x], low[y]);
			}
			else if(col[y] == 0){
				low[x] = min(low[x], num[y]);
			}
		}
		if(low[x] == num[x]){
			col_cnt++;
			do col[stk[top]] = col_cnt; 
			while(stk[top--] != x);
		}
	}
	void gao(int n){
		clk = col_cnt = top = 0;
		memset(col, 0, sizeof(col));
		memset(num, 0, sizeof(num));
		for(int i = 1; i <= n; i++) 
			if(num[i] == 0) dfs(i);
	}
}scc;

