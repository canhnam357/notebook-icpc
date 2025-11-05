#define ll long long
const ll mod1 = 1035972859;
const ll mod2 = 1704760909;
const int base = 256;
struct hashing{
    ll mod;
    int n;
    vector<ll> h, power;
    ll binpow(int a, int n){
        if (n == 0)
            return 1LL;
        ll res = binpow(a, n/2);
        if (n % 2)
            return res * res % mod * a % mod;
        return res * res % mod;
    }
    hashing() {}
    hashing(string s, int mod): mod(mod){
        this->n = s.length();
        power = h = vector<ll> (n);
        power[0] = 1;
        h[0] = s[0];
        for (int i = 1; i < n; i++){
            power[i] = power[i - 1] * base % mod;
            h[i] = (h[i - 1] * base + s[i]) % mod;
        }
    }

    ll get(int l, int r){
        return (!l ? h[r] : (h[r] - h[l - 1] * power[r - l + 1] + mod * mod) % mod);
    }
};

struct bighash{
    bighash() {}
    hashing a, b;
    bighash(string s){
        a = hashing(s, mod1);
        b = hashing(s, mod2);
    }
    ll get(int l, int r){
        return a.get(l, r) * b.get(l, r);
    }
};
