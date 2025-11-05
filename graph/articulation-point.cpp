// 0-indexed
struct ArticulationPoint {
	int n, dfs_cnt;
	vector<int> dfs_order, check;
	vector<vector<int>> adj;
	ArticulationPoint(int n) :
		n(n), adj(n),
		dfs_order(n), check(n),
		dfs_cnt(0) {}
	void AddEdge(int a, int b) {
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	int DFS(int cur, bool IsRoot = 0) {
		int ret = dfs_order[cur] = ++dfs_cnt, cnt = 0;
		for (const auto& nxt : adj[cur]) {
			if (!dfs_order[nxt]) {
				const int t = DFS(nxt);
				if (t >= dfs_order[cur]) check[cur] = 1;
				ret = min(ret, t), cnt++;
			}
			else ret = min(ret, dfs_order[nxt]);
		}
		if (IsRoot) check[cur] = cnt > 1;
		return ret;
	}
	void GetCheck() {
		for (int i = 0; i < n; i++)
			if (!dfs_order[i]) DFS(i, 1);
	}
};
// ArticulationPoint ap(n);
// ap.AddEdge()
// ap.GetCheck();
