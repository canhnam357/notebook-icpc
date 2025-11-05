// updated
#include <bits/stdc++.h>
#define int long long
#define MASK(i) (1LL << (i))
using namespace std;
const int N = 1e5 + 5;
int __lg(int n) { return log2(n) + 0.0001; }
vector<pair<int, int>> G[N];
int sz[N], h[N] = {}, d[N][17], par[N][17], par_centroid[N], dpar[N][17], del[N] = {}, amount[N] = {}, sum[N] = {}, sum_child[N] = {}, colored[N] = {};
int dfs(int u, int p)
{
    sz[u] = 1;
    for (auto v : G[u]) if (v.first != p && !del[v.first]) sz[u] += dfs(v.first, u);
    return sz[u];
}
int centroid(int u, int p, int n)
{
    for (auto v : G[u]) if (v.first != p && !del[v.first]) if (sz[v.first] > n / 2) return centroid(v.first, u, n);
    return u;
}
void first_dfs(int u, int p)
{
    for (auto v : G[u])
    {
        if (v.first == p) continue;
        h[v.first] = h[u] + 1;
        par[v.first][0] = u;
        d[v.first][0] = v.second;
        first_dfs(v.first, u);
    }
}
void build(int u, int p)
{
    int n = dfs(u, p);
    int c = centroid(u, p, n);
    par_centroid[c] = p;
    del[c] = 1;
    for (auto v : G[c])
    {
        if (del[v.first]) continue;
        build(v.first, c);
    }
}
int get_dis(int u, int v)
{
    int dis = 0;
    if (h[u] > h[v]) swap(u, v);
    int k = h[v] - h[u];
    for (int i = 0; i < 17; i++) if (k & MASK(i))
    {
        dis += d[v][i];
        v = par[v][i];
    }
    if (v == u) return dis;
    for (int i = 16; i >= 0; i--)
    {
        if (par[v][i] != par[u][i])
        {
            dis += d[v][i] + d[u][i];
            v = par[v][i];
            u = par[u][i];
        }
    }
    return dis + d[v][0] + d[u][0];
}
void modify(int u)
{
    for (int v = u, level = 0; v; v = par_centroid[v], level++)
    {
        amount[v]++;
        sum[v] += dpar[u][level];
    }
    int pre = u;
    for (int v = par_centroid[u], level = 1; v; v = par_centroid[v], level++)
    {
        sum_child[pre] += dpar[u][level];
        pre = v;
    }
}
int query(int u)
{
    int ans = sum[u];
    int pre = u;
    for (int v = par_centroid[u], level = 1; v; v = par_centroid[v], level++)
    {
        int cur_amount = amount[v] - amount[pre];
        ans += cur_amount * dpar[u][level] + sum[v] - sum_child[pre];
        pre = v;
    }
    return ans;
}
int32_t main()
{
    // tô 1 đỉnh màu đen
    // tìm tổng khoảng cách từ các đỉnh màu đen tới x
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n - 1; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        u++, v++;
        G[u].emplace_back(v, w);
        G[v].emplace_back(u, w);
    }
    first_dfs(1, 0);
    for (int i = 1; i < 17; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            par[j][i] = par[par[j][i - 1]][i - 1];
            d[j][i] = d[j][i - 1] + d[par[j][i - 1]][i - 1];
        }
    }
    build(1, 0);
    for (int i = 1; i <= n; i++)
    {
        for (int v = i, level = 0; v; v = par_centroid[v], level++)
        {
            dpar[i][level] = get_dis(i, v);
        }
    }
    while (q--)
    {
        int t, u;
        cin >> t >> u;
        u++;
        if (t == 1)
        {
            if (!colored[u])
            modify(u);
            colored[u] = 1;
        }
        else
        {
            cout << query(u) << '\n';
        }
    }
    return 0;
}
