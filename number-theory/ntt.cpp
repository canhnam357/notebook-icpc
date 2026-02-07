int power(long long a, int n, int mod) {
    long long ans = 1;
    while(n) {
        if(n & 1) ans = ans * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return ans;
}
int inverse(int a, int mod) {
    return power(a, mod - 2, mod);
}

// 1012924417 = 3*7*23 * 2^21 + 1
// root = 673144645, inv_root = 915669194, root_pw = 1 << 21
// 998244353  = 7*17 * 2^23 + 1
// root = 15311432, inv_root = 469870224, root_pw = 1 << 23
int mod = 998244353; // // 1 + 7*17*2^23
int inv_2 = (mod+1) / 2;
int root = 15311432;
int inv_root = 469870224;
int root_pw = 1 << 23;

void fft(vector<int> & a, bool invert) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        while(j & bit) {
            j ^= bit;
            bit >>= 1;
        }
        j ^= bit;

        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        int wlen = invert ? inv_root : root;
        for (int i = len; i < root_pw; i <<= 1) wlen = 1LL * wlen * wlen % mod;
        for (int i = 0; i < n; i += len) {
            int w = 1;
            for (int j = 0; j < len / 2; j++) {
                int u = a[i+j];
                int v = 1LL * a[i+j+len/2] * w % mod;
                a[i+j] = u + v < mod ? u + v : u + v - mod;
                a[i+j+len/2] = u - v >= 0 ? u - v : u - v + mod;
                w = 1LL * w * wlen % mod;
            }
        }
    }
    if (invert) {
        int n_1 = inverse(n, mod);
        for (int & x : a) x = 1LL * x * n_1 % mod;
    }
}

vector<int> multiply(const vector<int>& a, const vector<int>& b) {
    vector<int> fa(a.begin(), a.end());
    vector<int> fb(b.begin(), b.end());
    int n = 1;
    int sz = a.size() + b.size() - 1;
    while(n < a.size() + b.size()) n <<= 1;
    fa.resize(n);
    fb.resize(n);
    fft(fa, false);
    fft(fb, false);
    for(int i = 0; i < n; i++) fa[i] = 1LL * fa[i] * fb[i] % mod;
    fft(fa, true);
    fa.resize(sz);
    return fa;
}
