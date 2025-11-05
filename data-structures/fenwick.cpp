// for multi-dimension D, vector<pair<int, int>> = {x1 - 1, x2} {y1 - 1, y2} ...
// if sum (0-1) % 2 = D % 2 -> + else - , note : sum (0-1) is choose p1 - 1 or p2 
struct fenwick {
	int n;
	vector<int> bit;
	fenwick() {}
	fenwick(int n) {
		this->n = n + 5;
		bit.resize(n + 5);
	}
	// add x : pos -> n : x += x & -x
	// get x : pos -> 0 : x -= x & -x
	int find(int k) {
		int sum = 0, pos = 0;
		for (int i = __lg(n); i >= 0; i--) {
			if (pos + (1 << i) < n && sum + bit[pos + (1 << i)] < k) {
				sum += bit[pos + (1 << i)];
				pos += (1 << i);
			}
		}
		return pos + 1;
	}
};
