#include <bits/stdc++.h>
using namespace std;
#define all(x) x.begin(), x.end()
#define int long long

// 1-indexed
// https://www.acmicpc.net/problem/10538
template<int mod> // define int long long?
struct hashing2D 
{
	vector<vector<int>> h;
	vector<int> px, py;
	int n, m;
	static const int basex = 256,  basey = 652;
	// basex, basey is base, must difference
	hashing2D() {}
	hashing2D(vector<string>& s) 
	{
		n = (int)s.size(), m = (int)s[0].size();
		h.assign(n + 1, vector<int>(m + 1, 0));
		px.assign(n + 1, 1);
		py.assign(m + 1, 1);
		for (int i = 0; i < n; i++) px[i + 1] = 1LL * px[i] * basex % mod;
		for (int i = 0; i < m; i++) py[i + 1] = 1LL * py[i] * basey % mod;
		for (int i = 0; i < n; i++) 
		{
			for (int j = 0; j < m; j++) 
			{
				h[i + 1][j + 1] = s[i][j];
			}
		}
		for (int i = 0; i <= n; i++) 
		{
			for (int j = 0; j < m; j++) 
			{
				h[i][j + 1] = (h[i][j + 1] + 1LL * h[i][j] * basey % mod) % mod;
			}
		}
		for (int i = 0; i < n; i++) 
		{
			for (int j = 0; j <= m; j++) 
			{
				h[i + 1][j] = (h[i + 1][j] + 1LL * h[i][j] * basex % mod) % mod;
			}
		}
	}
	int get_hash(int x1, int y1, int x2, int y2) 
	{ // 1-indexed
		assert(1 <= x1 && x1 <= x2 && x2 <= n);
		assert(1 <= y1 && y1 <= y2 && y2 <= m);
		x1--;
		y1--;
		int dx = x2 - x1, dy = y2 - y1;
		return (1LL * (h[x2][y2] - 1LL * h[x2][y1] * py[dy] % mod + mod) % mod -
		1LL * (h[x1][y2] - 1LL * h[x1][y1] * py[dy] % mod + mod) % mod * px[dx] % mod + mod) % mod;
	}
	int get_hash() // whole vector2D
	{
		return get_hash(1, 1, n, m);
	}
};
const int mod1 = 1035972859;
const int mod2 = 1704760909;