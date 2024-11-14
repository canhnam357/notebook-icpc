#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod = 1e9+7;

bool prime(int n) {
    for(int i = 2; i * i <= n; i++) {
        if(n % i == 0)
            return false;
    }
    return n >= 2;
}
__int128_t power(int a, int n, int mod) {
    if(n == 0)
        return 1;
    __int128_t ans = power(a, n/2, mod);
    ans = ans * ans % mod;
    if(n & 1)
        return ans * a % mod;
    else
        return ans;
}

// Kiem tra miler rabin
// p-1 = m * 2^k
// f[i] = m * 2^i (i = 0..k)
// Neu f[0] != 1 (mod p) va f[i] != -1 (mod p) -> p chac chan khong nguyen to
// Nguoc lai p co the la so nguyen to
// Xac suat sai 1 lan chay = 25%
bool miler_rabin(int p) {
    if(p <= 1)
        return false;
    int m = p-1;
    int k = 0;
    while(!(m & 1)) {
        k++;
        m >>= 1;
    }
    for(int i = 1; i <= 30; i++) {
        int a = rand() % (p-1) + 1;
        __int128_t b = power(a, m, p);
        
        if(b == 1)
            continue;
        bool ok = false;
        for(int j = 0; j < k; j++) {
            if(b == p-1) {
                ok = true;
                break;
            }
            b = b * b % p;
        }
        if(!ok)
            return false;
    }
    return true;
}


void test_miler_rabin() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int l = 1e12;
    int r = l + 1e4;
    int ans1 = 0;
    int ans2 = 0;
    for(int i = l; i <= r; i++) {
        int res2 = miler_rabin(i);
        int res1 = prime(i);
        ans1 += res1;
        ans2 += res2;
    }
    cout << "Expected: " << ans1 << "\nFound: " << ans2 << "\n";
    
}