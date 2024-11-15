	// every two vertex same bcc, have two disjoint path between them
	int n, m;
	cin >> n >> m;
	vector<vector<int>> g(n), adj(n), radj(n), e(n);
	vector<int> edge_used(m);
	vector<tuple<int, int, int>> ed;
	for (int i = 0; i < m; i++)
	{
		int u, v, w; 
		cin >> u >> v >> w;
		u--, v--;
		g[u].push_back(v);
		e[u].push_back(i);
		g[v].push_back(u);
		e[v].push_back(i);
		ed.emplace_back(u, v, w);
	}
	vector<int> vis(n);
	function<void(int, int)> dfs1 = [&](int u, int p)
	{
		vis[u] = 1;
		for (int i = 0; i < g[u].size(); i++)
		{
			int v = g[u][i];
			if (v == p) continue;
			if (!edge_used[e[u][i]])
			{
				adj[u].push_back(v);
				radj[v].push_back(u);
				edge_used[e[u][i]] = 1;
			}
			if (!vis[v]) dfs1(v, u);
		}
	};
	dfs1(0, -1);
	fill(all(vis), 0);
	vector<int> topo;
	function<void(int)> dfs2 = [&](int u)
	{
		vis[u] = 1;
		for (int v : adj[u])
		{
			if (!vis[v]) dfs2(v);
		}
		topo.push_back(u);
	};
	for (int i = 0; i < n; i++) if (!vis[i]) dfs2(i);
	reverse(all(topo));
	vector<int> cc(n);
	int c = 0;
	fill(all(vis), 0);
	function<void(int)> dfs3 = [&](int u)
	{
		vis[u] = 1;
		cc[u] = c;
		//cout << u + 1 << ' ';
		for (int v : radj[u])
		{
			if (!vis[v]) dfs3(v);
		}
	};
	for (int i : topo)
	{
		if (!vis[i])
		{
			dfs3(i);
			//cout << '\n';
			c++;
		}
	}