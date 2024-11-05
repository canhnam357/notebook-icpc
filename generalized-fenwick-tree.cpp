#include <bits/stdc++.h>
using namespace std;
#define all(x) x.begin(), x.end()

/*
 * reference : https://ioinformatics.org/journal/v9_2015_39_44.pdf
 */

/* =============================================================================================== */

/*
                                                                                                   *
                                                   *                       *           *     *  *   
                           *           *     *  *              *     *  *        *  *     *         
               *     *  *        *  *     *              *  *     *           *                     
         *  *     *           *                       *                                             
      *                                                                                             
----------------------------------------------------------------------------------------------------
   0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32
*/

/*
                                                                                                   *
                                                   *                                                
                           *                          *  *     *           *                        
               *              *  *     *                    *     *  *        *  *     *            
         *        *  *              *     *  *                          *           *     *  *      
      *     *           *                       *                                               *   
----------------------------------------------------------------------------------------------------
   0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32
*/

/* =============================================================================================== */
// https://cses.fi/problemset/task/1647/
// 1-indexed
template<typename T, typename F>
struct Fenwick {
    const int n; const T ID; F f;
    vector<T> v, FT1, FT2;
    Fenwick(int n, T ID) : Fenwick(n, ID, F{}) {}
    explicit Fenwick(int n, T ID, const F& f) :
        n(n), ID(ID), f(f),
        v(n + 1, ID), FT1(n + 1, ID), FT2(n + 1, ID) {}
    void Update(int i, T val) {
        T t = v[i] = val;
        for (int j = i, l = i - 1, r = i + 1; j <= n; j += j & -j) {
            while (l > j - (j & -j)) t = f(FT1[l], t), l -= l & -l;
            while (r < j) t = f(t, FT2[r]), r += r & -r;
            FT1[j] = i ^ j ? f(t, v[j]) : t;
        }
        t = val;
        for (int j = i, l = i - 1, r = i + 1; j; j -= j & -j) {
            while (l > j) t = f(FT1[l], t), l -= l & -l;
            while (r <= n && r < j + (j & -j)) t = f(t, FT2[r]), r += r & -r;
            FT2[j] = i ^ j ? f(v[j], t) : t;
        }
    }
    T Query(int l, int r) {
        T L = ID, R = ID; int i;
        for (i = l; i + (i & -i) <= r; i += i & -i) L = f(L, FT2[i]);
        for (i = r; i - (i & -i) >= l; i -= i & -i) R = f(FT1[i], R);
        return f(f(L, v[i]), R);
    }
};
int f(int a, int b)
{
	return a < b ? a : b;
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int n, q;
	cin >> n >> q;
	Fenwick<int, function<int(int, int)>> tree(n, INT_MAX, f);
	for (int i = 1; i <= n; i++)
	{
		int x;
		cin >> x;
		tree.Update(i, x);
	}
	while (q--)
	{
		int l, r;
		cin >> l >> r;
		cout << tree.Query(l, r) << '\n';
	}
	return 0;
}