// MOD thay the:
// 1004535809 = 479 * 2^21 + 1
// root = 702606812, root_pw = 1 << 21
// 1012924417 = 483 * 2^21 + 1
// root = 673144645, root_pw = 1 << 21
// 998244353  = 119 * 2^23 + 1
// root = 15311432, root_pw = 1 << 23
int mod = 998244353; // // 1 + 7*17*2^23
int inv_2 = (mod+1) / 2;
int root = 15311432;
int root_pw = 1 << 23;
int inv_root = inverse(root, mod);
using ll = long long;
void fft(vector<ll> &a, int n, bool invert) {
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
        ll wlen = invert ? inv_root : root;
        for (int i = len; i < root_pw; i <<= 1) wlen = wlen * wlen % mod;
        for (int i = 0; i < n; i += len) {
            ll w = 1;
            for (int j = 0; j < len / 2; j++) {
                int u = a[i+j];
                int v = a[i+j+len/2] * w % mod;
                a[i+j] = u + v < mod ? u + v : u + v - mod;
                a[i+j+len/2] = u - v >= 0 ? u - v : u - v + mod;
                w = w * wlen % mod;
            }
        }
    }
    if (invert) {
        int inv_n = inverse(n, mod);
        for(int i = 0; i < n; i++) a[i] = a[i] * inv_n % mod;
    }
}

vector<int> multiply(vector<int> a, vector<int> b) {
    vector<ll> fa(a.begin(), a.end());
    vector<ll> fb(b.begin(), b.end());
    int n = 1;
    int sz = a.size() + b.size() - 1;
    while(n < sz) n <<= 1;
    fa.resize(n), fb.resize(n);
    fft(fa, n, false);
    fft(fb, n, false);
    for(int i = 0; i < n; i++) fa[i] = fa[i] * fb[i] % mod;
    fft(fa, n, true);
    vector<int> res(sz);
    for(int i = 0; i < sz; i++) res[i] = fa[i];
    return res;
}