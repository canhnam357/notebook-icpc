struct DSUrb {
    vector<int> par, sz; stack<vector<int>> s;
    int cc;
    void init(int n) {
        cc = n; par.resize(n);
        sz.resize(n, 1);
        iota(par.begin(), par.end(), 0);
    }
    int get(int x) {
        if (x == par[x]) return x;
        return get(par[x]);
    }
    bool join(int u, int v) {
        u = get(u); v = get(v);
        if (u == v) return false;
        if (sz[u] < sz[v]) swap(u, v);
        s.push({ u, v, sz[v] });
        par[v] = u; sz[u] += sz[v];
        return true;
    }
    void rollback(int cnt) {
        while (cnt--) {
            auto a = s.top(); s.pop();
            par[a[1]] = a[1];
            sz[a[0]] -= a[2];
            sz[a[1]] = a[2];
        }
    }
    int same(int a, int b){
        return get(a) == get(b);
    }
};
