pair<int, int> q[MAXN];
int cnt = 1, nq;
map<pair<int, int>, int> mp;
vector<vector<int>> e;
vector<vector<pair<int, int>>> st(1 << 19);
void update(int u, int v, int f, int s, int id = 1, int l = 1, int r = 1 << 18) {
    if (r < u || l > v) return;
    if (l >= u && r <= v) {
        st[id].emplace_back(f, s);
        return;
    }
    int mid = (l + r) >> 1;
    update(u, v, f, s, id << 1, l, mid);
    update(u, v, f, s, id << 1 | 1, mid + 1, r);
}
DSUrb s;
void divide(int id = 1, int l = 1, int r = 1 << 18) {
    int z = 0;
    for (auto x : st[id]) {
        z += (int)s.join(x.first, x.second);
    }
    if (l == r) {
        if (l < cnt) {
            cout << (s.same(q[l].first, q[l].second) ? "YES" : "NO") << '\n';
        }
        s.rollback(z);
        return;
    }
    int mid = (l + r) >> 1;
    divide(id << 1, l, mid); divide(id << 1 | 1, mid + 1, r);
    s.rollback(z);
}
void solve() {
    vector<int> state(m);
    for (int& i : state) cin >> i;
    for (int i = 0; i < m; i++) {
        if (edge[i].first > edge[i].second) swap(edge[i].first, edge[i].second);
        if (state[i]) {
            mp[edge[i]] = cnt;
        }
    }
    cin >> nq;
    s.init(n);
    for (int i = 0; i < nq; i++) {
        int t, a, b;
        cin >> t >> a;
        a--;
        if (t == 1) {
            if (state[a]) {
                if (mp[edge[a]] != cnt) {
                    e.push_back({ edge[a].first, edge[a].second, mp[edge[a]], cnt - 1 });
                }
                mp.erase(edge[a]);
            }
            else {
                mp[edge[a]] = cnt;
            }
            state[a] ^= 1;
        }
        else {
            cin >> b;
            b--;
            if (a > b) swap(a, b);
            q[cnt++] = { a,b };
        }
    }
    for (auto x : mp) {
        if (x.second != cnt) {
            e.push_back({ x.first.first, x.first.second, x.second, cnt - 1 });
        }
    }
    for (int i = 0; i < e.size(); i++) update(e[i][2], e[i][3], e[i][0], e[i][1]);
    divide();
}
