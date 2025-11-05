// 0-indexed
struct Bridge { // must be no multi-edge
	int n, dfs_cnt;
	vector<int> dfs_order;
	vector<pair<int, int>> bridge;
	vector<vector<int>> adj;
	Bridge(int n) :
		n(n), adj(n),
		dfs_order(n),
		dfs_cnt(0) {}
	void AddEdge(int a, int b) {
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	int DFS(int cur, int prv = -1) {
		int ret = dfs_order[cur] = ++dfs_cnt;
		for (const auto& nxt : adj[cur]) {
			if (nxt == prv) continue;
			if (!dfs_order[nxt]) {
				const int t = DFS(nxt, cur);
				if (t > dfs_order[cur]) bridge.push_back({ cur, nxt });
				ret = min(ret, t);
			}
			else ret = min(ret, dfs_order[nxt]);
		}
		return ret;
	}
	void GetBridge() {
		for (int i = 0; i < n; i++)
			if (!dfs_order[i]) DFS(i);
		for (auto& [a, b] : bridge) if (a > b) swap(a, b);
		sort(bridge.begin(), bridge.end());
	}
};
// Bridge b(n);
// b.AddEdge()
// b.GetBridge();
