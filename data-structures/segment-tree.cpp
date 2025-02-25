#include <bits/stdc++.h>
using namespace std;
#define all(x) x.begin(), x.end()
 
// https://cses.fi/problemset/task/1649/
// 1-indexed
template<typename T, typename F>
struct segtree {
    const size_t sz; const T ID; F f{};
    vector<T> tree;
    segtree(size_t n, T ID) : segtree(n, ID, F{}) {}
    explicit segtree(size_t n, T ID, const F& f) :
        sz(Log2(n)), ID(ID), f(f),
        tree(sz << 1, ID) {}
    static size_t Log2(size_t n) {
        n--;
        for (int i = 0; i < 5; i++) n |= n >> (1 << i);
        return n + 1;
    }
    void update(int i, T val) {
        --i |= sz; tree[i] = val;
        while (i >>= 1) tree[i] = f(tree[i << 1], tree[i << 1 | 1]);
    }
    T query(int l, int r) const {
        T L = ID, R = ID; --l |= sz, --r |= sz;
        while (l <= r) {
            if (l & 1) L = f(L, tree[l++]);
            if (~r & 1) R = f(tree[r--], R);
            l >>= 1, r >>= 1;
        }
        return f(L, R);
    }
};
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	auto f = [&](int a, int b) -> int { return a < b ? a : b; };
	int n, q;
	cin >> n >> q;
	segtree<int, decltype(f)> tree(n, numeric_limits<int>::max(), f);
	for (int i = 1; i <= n; i++)
	{
		int x;
		cin >> x;
		tree.update(i, x);
	}
	while (q--)
	{
		int t, l, r;
		cin >> t >> l >> r;
		if (t == 1) tree.update(l, r);
		else cout << tree.query(l, r) << '\n';
	}
	return 0;
}
