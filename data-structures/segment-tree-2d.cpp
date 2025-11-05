// 1-indexed
template<typename T, typename F>
struct SegmentTree2D {
	vector<vector<T>> tree;
	size_t szx, szy;
	const T ID;
	F f{};
	SegmentTree2D(size_t n, size_t m, T ID) : SegmentTree2D(n, m, ID, F{}) {}
	explicit SegmentTree2D(size_t n, size_t m, T ID, const F& f) :
		szx(Log2(n)), szy(Log2(m)), ID(ID), f(f) {
		tree = vector<vector<T>>(szx << 1, vector<T>(szy << 1, ID));
	}
	static size_t Log2(size_t n) {
		n--;
		for (int i = 0; i < 5; i++) n |= n >> (1 << i);
		return n + 1;
	}
	T get_child(int id_par, int y1, int y2, int id, int l, int r) {
		if (r < y1 || l > y2) return ID;
		if (l >= y1 && r <= y2)
			return tree[id_par][id];
		int mid = (l + r) >> 1;
		return f(get_child(id_par, y1, y2, id << 1, l, mid), get_child(id_par, y1, y2, id << 1 | 1, mid + 1, r));
	}
	T get_child(int id_par, int y1, int y2) {
		return get_child(id_par, y1, y2, 1, 1, szy);
	}
	T get(int x1, int y1, int x2, int y2, int id, int l, int r) {
		if (r < x1 || l > x2) return ID;
		if (l >= x1 && r <= x2)
			return get_child(id, y1, y2);
		int mid = (l + r) >> 1;
		return f(get(x1, y1, x2, y2, id << 1, l, mid), get(x1, y1, x2, y2, id << 1 | 1, mid + 1, r));
	}
	T get(int x1, int y1, int x2, int y2) {
		return get(x1, y1, x2, y2, 1, 1, szx);
	}
	void update_y(int id_par, int l_par, int r_par, int y, T val, int id, int l, int r) {
		if (l == r) {
			if (l_par == r_par)
				tree[id_par][id] = val;
			else
				tree[id_par][id] = f(tree[id_par << 1][id], tree[id_par << 1 | 1][id]);
		}
		else {
			int mid = (l + r) >> 1;
			if (y <= mid)
				update_y(id_par, l_par, r_par, y, val, id << 1, l, mid);
			else
				update_y(id_par, l_par, r_par, y, val, id << 1 | 1, mid + 1, r);
			tree[id_par][id] = f(tree[id_par][id << 1], tree[id_par][id << 1 | 1]);
		}
	}
	void update_y(int id_par, int l_par, int r_par, int y, T val) {
		update_y(id_par, l_par, r_par, y, val, 1, 1, szy);
	}
	void update(int x, int y, T val, int id, int l, int r) {
		if (l != r) {
			int mid = (l + r) >> 1;
			if (x <= mid)
				update(x, y, val, id << 1, l, mid);
			else
				update(x, y, val, id << 1 | 1, mid + 1, r);
		}
		update_y(id, l, r, y, val);
	}
	void update(int x, int y, T val) {
		update(x, y, val, 1, 1, szx);
	}
};
auto f = [&](int a, int b) -> int { return a + b; };
SegmentTree2D<int, decltype(f)> tree(n, n, 0, f);
