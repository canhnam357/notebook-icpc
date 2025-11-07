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
    long long val = 0;
};
void combine(Node* t) {
    t->val = max(t->l->val, t->r->val);
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
long long query(Node* t, int xl, int xr, int yl, int yr) {
    if (!t->val) return 0;
    if (t->xr < xl || t->xl > xr || t->yr < yl || t->yl > yr || !t->val) return 0;
    if (t->xl >= xl && t->xr <= xr && t->yl >= yl && t->yr <= yr) return t->val;
    return max(query(t->l, xl, xr, yl, yr), query(t->r, xl, xr, yl, yr));
}
void update(Node* t, int x, int y, long long val) {
    if (t->xl > x || t->xr < x || t->yl > y || t->yr < y) return;
    if (x == t->xl && x == t->xr && y == t->yl && y == t->yr) {
        t->val = max(t->val, val);
        return;
    }
    update(t->l, x, y, val);
    update(t->r, x, y, val);
    combine(t);
}
const int N = 2e5;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, dx, dy;
    cin >> n >> dx >> dy;
    vector<tuple<int, int, int, int>> a(n);
    for (auto &[h, x, y, p] : a) cin >> x >> y >> h >> p;
    sort(a.begin(), a.end());
    for (auto [h, x, y, p] : a) b.emplace_back(x, y);
    sort(b.begin(), b.end());
    auto root = build(0, b.size() - 1);
    for (auto [h, x, y, p] : a) {
        int xl = max(1, x - dx);
        int yl = max(1, y - dy);
        long long k = query(root, xl, min(N, x + dx), yl, min(N, y + dy));
        if (k + p > 0) update(root, x, y, k + p);
    }
    cout << query(root, 1, N, 1, N);
    return 0;
}
