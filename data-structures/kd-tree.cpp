#include <bits/stdc++.h>
using namespace std;
const int inf = 1e9;
// KD-Tree
struct Node {
    Node* l = nullptr;
    Node* r = nullptr;
    int xl = inf;
    int xr = -inf;
    int yl = inf;
    int yr = -inf;
    int minz = inf; // order by time shoot
};
map<pair<int, int>, queue<int>> shoots;
void combine(Node* t) {
    t->minz = min(t->l->minz, t->r->minz);
}
// d (dimension) : 0 -> x, 1 -> y
vector<pair<int, int>> b;
Node* build(int l, int r, int d = 0) {
    Node* t = new Node();
    for (int i = l; i <= r; i++) {
        auto [x, y] = b[i];
        t->xl = min(t->xl, x);
        t->xr = max(t->xr, x);
        t->yl = min(t->yl, y);
        t->yr = max(t->yr, y);
    }
    if (l == r) {
        t->minz = shoots[b[l]].front();
        return t;
    }
    int n = r - l + 1;
    nth_element(b.begin() + l, b.begin() + l + n / 2, b.begin() + r + 1, [&](auto i, auto j) {
        return d ? i.second < j.second : i.first < j.first;
    });
    t->l = build(l, l + n / 2 - 1, d ^ 1);
    t->r = build(l + n / 2, r, d ^ 1);
    combine(t);
    return t;
}
int query(Node* t, int xl, int xr, int yl, int yr) {
    if (t->xr < xl || t->xl > xr || t->yr < yl || t->yl > yr) return inf;
    if (t->xl >= xl && t->xr <= xr && t->yl >= yl && t->yr <= yr) return t->minz;
    return min(query(t->l, xl, xr, yl, yr), query(t->r, xl, xr, yl, yr));
}
void del(Node* t, int x, int y) {
    if (t->xl > x || t->xr < x || t->yl > y || t->yr < y) return;
    if (x == t->xl && x == t->xr && y == t->yl && y == t->yr) {
        shoots[{x, y}].pop();
        t->minz = shoots[{x, y}].empty() ? inf : shoots[{x, y}].front();
        return;
    }
    del(t->l, x, y);
    del(t->r, x, y);
    combine(t);
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> xl(n), xr(n), yl(n), yr(n), z(n);
    for (int i = 0; i < n; i++) {
        cin >> xl[i] >> xr[i] >> yl[i] >> yr[i] >> z[i];
    }
    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int a, int b) {
        return z[a] < z[b];
    });
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        b.emplace_back(x, y);
        shoots[b.back()].push(i);
    }
    auto c = b;
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    auto root = build(0, b.size() - 1);
    vector<int> ans(m);
    for (int i = 0; i < n; i++) {
        int j = ord[i];
        int k = query(root, xl[j], xr[j], yl[j], yr[j]);
        if (k != inf) {
            ans[k] = j + 1;
            del(root, c[k].first, c[k].second);
        }
    }
    for (int i : ans) cout << i << '\n';
    return 0;
}
