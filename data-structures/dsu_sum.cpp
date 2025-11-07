struct dsu {
    vector<int> par, d;
    int cc;
    dsu() {}
    dsu(int n) {
        par.resize(n + 5);
        iota(par.begin(), par.end(), 0);
        d.resize(n + 5);
    }
    pair<int, int> find(int u) {
        if (u == par[u]) return make_pair(u, d[u]);
        auto p = find(par[u]);
        par[u] = p.first;
        d[u] += p.second;
        return make_pair(par[u], d[u]);
    }
    void join(int a, int b) {
        int z = b;
        a = find(a).first, b = find(b).first;
        if (a != b) par[a] = b, d[a] = d[z] + 1; 
    }
    bool same(int a, int b) {
        return find(a).first == find(b).first;
    }
};
