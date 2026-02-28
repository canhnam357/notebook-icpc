const int mod = 998244353;
const int N = 100000;
int ft[N];
int ift[N];
int power(int a, int n) {
    int ans = 1;
    while(n) {
        if(n & 1) {
            ans = ans * a % mod;
        }
        n >>= 1;
        a = a * a % mod;
    }    
    return ans;
}
int inverse(int a) {
    return power(a, mod-2);
}
void precalc() {
    ft[0] = 1;
    for(int i = 1; i < N; i++) {
        ft[i] = ft[i-1] * i % mod;
    }
    ift[N-1] = inverse(ft[N-1]);
    for(int i = N-2; i >= 0; i--) {
        ift[i] = ift[i+1] * (i+1) % mod;
    }
}
int C(int n, int k) {
    return ft[n] * ift[k] % mod * ift[n-k] % mod;
}