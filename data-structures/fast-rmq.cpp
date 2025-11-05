// RMQ with sparse table O<N, 1>
template<typename T>
struct RMQ {
    static const int b = 30;
    vector<T> dat;
    vector<int> mask, a;
    function<bool(T, T)> g;
    int n;
    RMQ() : n(0) {}
    int f(int a, int b) {
        return g(dat[a], dat[b]) ? a : b;
    }
    RMQ(vector<T>& dat, function<bool(T, T)> g) {
        this->g = g;
        this->dat = dat;
        n = dat.size();
        mask = vector<int>(n);
        a = vector<int>(n);
        int cur_mask = 0;
        for (int i = 0; i < n; i++) {
            cur_mask = (cur_mask << 1) & ((1 << b) - 1);
            while (cur_mask > 0 && f(i, i - msb_index(lsb(cur_mask))) == i) {
                cur_mask ^= lsb(cur_mask);
            }
            cur_mask |= 1;
            mask[i] = cur_mask;
        }
        for (int i = 0; i < n / b; i++) {
            a[i] = small(b * i + b - 1);
        }
        for (int j = 1; (1 << j) <= n / b; j++) for (int i = 0; i + (1 << j) <= n / b; i++) {
            a[n / b * j + i] = f(a[n / b * (j - 1) + i], a[n / b * (j - 1) + i + (1 << (j - 1))]);
        }
    }
    int lsb(int x) {
        return x & -x;
    }
    int msb_index(int x) {
        return __builtin_clz(1) - __builtin_clz(x);
    }
    int small(int r, int size = b) {
        int dist_from_r = msb_index(mask[r] & ((1 << size) - 1));
        return r - dist_from_r;
    }
    T query(int l, int r) {
        assert(l <= r);
        if (r - l + 1 <= b) return dat[small(r, r - l + 1)];
        int ans = f(small(l + b - 1), small(r));
        int x = l / b + 1, y = r / b - 1;     
        if (x <= y) {
            int j = msb_index(y - x + 1);
            ans = f(ans, f(a[n / b * j + x], a[n / b * j + y - (1 << j) + 1]));
        }
        return dat[ans];
    }
};
