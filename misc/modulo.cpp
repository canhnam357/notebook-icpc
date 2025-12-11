#include <bits/stdc++.h>
#define int long long
using namespace std;
#define MASK(i) (1LL << (i))
#define MASK_ALL(i) ((1LL << (i+1)) - 1)
#define sqr(x) ((x) * (x))
const int inf = 1e18;
const int mod = 998244353;
const double eps = 1e-6;

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

const int N = 100000;
int ft[N];
int ift[N];
void precalc() {
    ft[0] = 1;
    for(int i = 1; i < N; i++) {
        ft[i] = ft[i-1] * i % mod;
    }
    ift[N-1] = inverse(ft[N-1]);
    for(int i = N-2; i >= 0; i--) {
        ift[i] = ift[i+1] * (i+1) % mod;
    }
    // testing
    // cerr << ift[1] << "\n";
}

int C(int n, int k) {
    return ft[n] * ift[k] % mod * ift[n-k] % mod;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    #ifdef LOCAL
       freopen("input.txt", "r", stdin);
       freopen("output.txt", "w", stdout);
    #endif
    precalc();
    cerr << C(6, 3) << "\n";
}
