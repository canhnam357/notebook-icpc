function<int(int, bool)> dfs_solve = [&](int u, bool keep) {
        int mx = -1, big_child = -1, cur = 0;
        for (auto [v, c] : adj[u]) {
            if (sz[v] > mx) {
                mx = sz[v];
                big_child = v;
            }
        }
        for (auto [v, c] : adj[u]) {
            if (v != big_child) dfs_solve(v, false);
        }
        if (big_child != -1) {
            cur = max(cur, dfs_solve(big_child, true));
            if (f[g[u]] != -1) {
                cur = max(cur, f[g[u]] - h[u]);
            }
            for (int j = 0; j < 22; j++) {
                if (f[g[u] ^ (1 << j)] != -1) {
                    cur = max(cur, f[g[u] ^ (1 << j)] - h[u]);
                }
            }
        }
        for (auto [v, c] : adj[u]) {
            if (v == big_child) continue;
            for (int i = in[v]; i < out[v]; i++) {
                int k = g[et[i]] ^ g[u];
                if ((k & (k - 1)) == 0) {
                    cur = max(cur, h[et[i]] - h[u]);
                }
                k ^= g[u];
                if (f[k] != -1) {
                    cur = max(cur, h[et[i]] + f[k] - 2 * h[u]);
                }
                for (int j = 0; j < 22; j++) {
                    int l = k ^ (1 << j);
                    if (f[l] != -1) {
                        cur = max(cur, h[et[i]] + f[l] - 2 * h[u]);
                    }
                }
            }
            for (int i = in[v]; i < out[v]; i++) {
                int k = g[et[i]];
                if (f[k] < h[et[i]]) f[k] = h[et[i]];
            }
        }
        ans[u] = cur;
        if (f[g[u]] < h[u]) {
            f[g[u]] = h[u];
        }
        if (!keep) {
            for (int i = in[u]; i < out[u]; i++) {
                f[g[et[i]]] = -1;
            }
            return 0;
        }
        return cur;
    };
