/**
 * Description: Eulerian path starting at \texttt{src} if it exists,
	 * visits all edges exactly once. Works for both directed and
	 * undirected. Returns vector of \{vertex,label of edge to vertex\}.
	 * Second element of first pair is always $-1$.
 * Time: O(N+M)
 * Source: USACO Training, MIT ICPC Notebook
 * Verification:
	* directed -> https://open.kattis.com/problems/eulerianpath
	* undirected -> USACO Training 3.3, Riding the Fences
 */
struct Euler {
	int n; 
	vector<vector<pair<int, int>>> adj; 
	vector<vector<pair<int, int>>::iterator> its; 
	vector<bool> used;
	void init(int _n) 
	{ 
		n = _n; 
		adj.resize(n); 
	}
	void add_edge(int a, int b, bool directed = false) 
	{
		int m = used.size(); 
		used.push_back(0);
		adj[a].emplace_back(b, m); 
		if (!directed) adj[b].emplace_back(a, m);
	}
	vector<pair<int, int>> solve(int src = 0) 
	{
		its.resize(n); 
		for (int i = 0; i < n; i++) its[i] = adj[i].begin();
		vector<pair<int, int>> ans, s = { {src, -1} }; // {{vert,prev vert},edge label}
		int lst = -1; // ans generated in reverse order
		while (s.size()) {
			int x = s.back().first; 
			auto& it = its[x], en = adj[x].end();
			while (it != en && used[it->second]) ++it;
			if (it == en) { // no more edges out of vertex
				if (lst != -1 && lst != x) return {};
				// not a path, no tour exists
				ans.push_back(s.back()); s.pop_back(); if (s.size()) lst = s.back().first;
			}
			else s.push_back(*it), used[it->second] = 1;
		} // must use all edges
		if (ans.size() != used.size() + 1) return {};
		reverse(all(ans)); return ans;
	}
};
int32_t main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	Euler e;
	int n;
	cin >> n;
	e.init(n);
	vector<int> deg(n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int x;
			cin >> x;
			if (i < j && x) 
			{
				while (x--)
				e.add_edge(i, j), deg[i] ^= 1, deg[j] ^= 1;
			}
		}
	}
	if (*max_element(all(deg)))
	{
		cout << -1;
		return 0;
	}
	auto g = e.solve();
	if (g.empty())
	{
		cout << -1;
		return 0;
	}
	for (auto x : g)
	{
		cout << x.first + 1 << ' ';
	}
	return 0;
}