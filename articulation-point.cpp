#include <bits/stdc++.h>
using namespace std;

// https://www.acmicpc.net/problem/11266
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

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int n, m;
	cin >> n >> m;
	ArticulationPoint ap(n);
	for (int i = 0; i < m; i++)
	{
		int u, v;
		cin >> u >> v;
		ap.AddEdge(--u, --v);
	}
	ap.GetCheck();
	cout << accumulate(ap.check.begin(), ap.check.end(), 0) << '\n';
	for (int i = 0; i < n; i++)
	{
		if (ap.check[i]) cout << i + 1 << ' ';
	}
	return 0;
}