int get_neg(int n) {
    int k = abs(n) * 2;
    return n < 0 ? k + 1 : k;
}
int get_pos(int n) {
    int k = abs(n) * 2;
    return n < 0 ? k : k + 1;
}
const int mxn = 2e5 + 5;
vector<int> adj[mxn], adj_rev[mxn];
int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> m >> n;
    for (int i = 0; i < m; i++) {
        char c, d;
        int u, v;
        cin >> c >> u >> d >> v;
        if (c == '-') u = -u;
        if (d == '-') v = -v;
        adj[get_neg(u)].push_back(get_pos(v));
        adj_rev[get_pos(v)].push_back(get_neg(u));
        adj[get_neg(v)].push_back(get_pos(u));
        adj_rev[get_pos(u)].push_back(get_neg(v));
    }
    vector<int> vis(n * 2 + 5), topo;
    function<void(int)> dfs = [&](int u) {
        vis[u] = 1;
        for (int v : adj[u]) if (!vis[v]) dfs(v);
        topo.push_back(u);
    };
    for (int i = 2; i <= n * 2 + 1; i++) {
        if (!vis[i]) dfs(i);
    }
    reverse(all(topo));
    int cnt = 1;
    fill(all(vis), 0LL);
    vector<int> val(n * 2 + 5);
    function<void(int)> dfs2 = [&](int u) {
        vis[u] = 1;
        val[u] = cnt;
        for (int v : adj_rev[u]) if (!vis[v]) dfs2(v);
    };
    for (int i : topo) {
        if (!vis[i]) {
            dfs2(i);
            cnt++;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (val[i * 2] == val[i * 2 + 1]) {
            cout << "IMPOSSIBLE";
            return 0;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (val[i << 1 | 1] > val[i << 1]) cout << '+' << ' ';
        else cout << '-' << ' ';
    }
    return 0;
}
