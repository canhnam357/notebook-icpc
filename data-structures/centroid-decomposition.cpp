// path(u, v) = path'(u, w) + path'(w, v) with w is lca of (u, v) in centroid tree
const int N = 1e5 + 5;
vector<pair<int, int>> adj[N];
int del[N], sz[N];
int dfs_sz(int u, int p) {
    sz[u] = 1;
    for (auto [v, w] : adj[u]) {
        if (v != p && !del[v]) sz[u] += dfs_sz(v, u);
    }
    return sz[u];
}
int centroid(int u, int p, int n) {
    for (auto [v, w] : adj[u]) {
        if (v != p && !del[v] && sz[v] > n / 2) return centroid(v, u, n);
    }
    return u;
}
void solve(int u, int p) {
    int n = dfs_sz(u, p);
    int c = centroid(u, p, n);
    del[c] = 1;
    for (auto [v, w] : adj[c]) {
        if (del[v]) continue;
        // solve subtree of centroid here
    }
    for (auto [v, w] : adj[c]) {
        if (!del[v]) solve(v, c);
    }
}
