/*
����ͼ�����/��/˫��ͨ����
�ж��ٸ�low[y] >= num[x]����ôȥ�� x ������֮����ͨ������Ӷ��٣����Ǹ���ʱ��Ӧ�� -1
�˴�˫��ͨ����ָ����˫��ͨ������������������������������㲻�ظ���·�����������������������˫��ͨ������
����˫��ͨ����������������������������߲��ظ���·�����󷨣�ɾ�����е��ţ�ʣ���ÿ����ͨ�������ǡ���˫��ͨ������
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
		S.push(x);  // ������BCC�ǵý�ջȥ��
		for(int i = 0; i < G[x].size(); i++){
			int y = G[x][i];
			if(num[y] == 0){
				fa[y] = x; dfs(y);
				// ��
				if(low[y] > num[x]) cout << x << " to " << y << " is a bridge" << endl;
				if(low[y] >= num[x]){
					add[x]++;
					// ˫��ͨ����
					vector<int> bcc; bcc.push_back(x);
					do{
						bcc.push_back(S.top()); S.pop();
					}while(bcc.back() != y);
					// ��ʱ bcc ��Ϊһ��˫��ͨ����
				}
				low[x] = min(low[x], low[y]);
			}
			else if(y != fa[x])
				low[x] = min(low[x], num[y]);
		}
		if(fa[x] < 0) add[x]--;
		// add[x] ��ʾ�� x ɾ������ͨ�������Ӷ���
		if(add[x] > 0) iscut[x] = true;
	}
	int solve(int n){
		memset(num, 0, sizeof(num));
		memset(iscut, 0, sizeof(iscut));
		int ret = clk = 0;
		for(int i = 1; i <= n; i++) if(num[i] == 0){
			fa[i] = -1; dfs(i); ret++;
		}
		return ret;  // ������ͨ��������
	}
};
