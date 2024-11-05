#include <bits/stdc++.h>
using namespace std;
#define all(x) x.begin(), x.end()


// https://www.acmicpc.net/problem/13547
class Query {
public:
	int id, l, r;
	Query(int id, int l, int r) :
		id(id), l(l), r(r), prior(ConvHilbert(l, r)) {}
	bool operator< (const Query& i) const { return prior < i.prior; }

private:
	long long prior;
	static long long ConvHilbert(int x, int y) {
		long long ret = 0;
		for (int i = 17, cx, cy; ~i; i--) {
			cx = x >> i & 1, cy = y >> i & 1;
			ret = ret << 2 | cx << 1 | cx ^ cy;
			cy || (swap(x, y), cx) && (x = ~x, y = ~y);
		}
		return ret;
	}
};

const int A = 1e6 + 1;
int cnt[A] = {}, diff = 0;
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;
	vector<int> a(n);
	for (int &i : a) cin >> i;
	int nq;
	cin >> nq;
	vector<Query> q;
	for (int i = 0; i < nq; i++)
	{
		int l, r;
		cin >> l >> r;
		l--, r--;
		q.emplace_back(i, l, r);
	}
	sort(all(q));
	vector<int> ans(nq);
	int l = 0, r = -1;
	auto add = [&](int x)
	{
		diff += (cnt[x]++ == 0);
	};
	auto rmv = [&](int x)
	{
		diff -= (cnt[x]-- == 1);
	};
	for (auto query : q)
	{
		while (l > query.l) add(a[--l]);
		while (r < query.r) add(a[++r]);
		while (l < query.l) rmv(a[l++]);
		while (r > query.r) rmv(a[r--]);
		ans[query.id] = diff;
	}
	for (int i : ans) cout << i << '\n';
	return 0;
}