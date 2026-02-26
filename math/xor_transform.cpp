const int mod = 998244353;

void fwht(int* a, int len, bool invert) {
    // assert(len > 0 && (len & (len-1)) == 0);
    for (int h = 1; h < len; h <<= 1) {
        for (int i = 0; i < len; i += (h << 1)) {
            for (int j = i; j < i + h; j++) {
                int x = a[j];
                int y = a[j + h];
                a[j] = x + y;
                a[j + h] = x - y;
                if(a[j] >= mod) a[j] -= mod;
                if(a[j+h] < 0) a[j+h] += mod;
            }
        }
    }
    if(invert) {
        int inv_len = inverse(len);
        for(int i = 0; i < len; i++) {
            a[i] = 1LL * a[i] * inv_len % mod;
        }
    }
}
