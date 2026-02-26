int k = p.size();
ranges::sort(p, [&](int u, int v) {return in[u] < in[v];});
for (int i = 1; i < k; i++) p.push_back(lca(p[i - 1], p[i]));
ranges::sort(p, [&](int u, int v) {return in[u] < in[v];});
p.erase(ranges::unique(p).begin(), p.end());
for (int i : p) vadj[i].clear();
for (int i = 1; i < p.size(); i++) vadj[lca(p[i - 1], p[i])].push_back(p[i]);