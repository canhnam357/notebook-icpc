struct DSU {
    vector<int> par, sz;
    int cc;
    DSU(int n) : cc(n) {
        par.resize(n + 1);
        iota(par.begin(), par.end(), 0);
        sz.resize(n + 1, 1);
    }
    int find(int u) {
        return u == par[u] ? u : par[u] = find(par[u]);
    }
    bool join(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return false;
        par[u] = v;
        sz[v] += sz[u];
        cc--;
        return true;
    }
    bool same(int u, int v) {
        return find(u) == find(v);
    }
};
