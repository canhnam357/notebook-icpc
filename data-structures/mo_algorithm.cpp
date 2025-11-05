/*
Let in[u] <= in[v], p = lca(u, v)
Case 1 : p = u -> [in[u], in[v]]
Case 2 : p != u -> [out[u], in[v]] [in[p], in[p]]
*/
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
bool cmp(pair<int, int> p, pair<int, int> q) {
    if (p.first / BLOCK_SIZE != q.first / BLOCK_SIZE)
        return p < q;
    return (p.first / BLOCK_SIZE & 1) ? (p.second < q.second) : (p.second > q.second);
}
