#include <bits/stdc++.h>
#define int long long
using namespace std;
#define MASK(i) (1LL << (i))
#define MASK_ALL(i) ((1LL << (i+1)) - 1)
#define sqr(x) ((x) * (x))
const int inf = 1.1e18;
const int mod = 998244353;
const double eps = 1e-6;

mt19937_64 mt(0);
int randint(int l, int r) {
    return mt() % (r - l + 1) + l;
}

int n;
// creating variables here
void gentest() {
    // generate test case (if using generator)
}

int ask() {
    return -1;
}

void answer() {
    // assert the answer
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef LOCAL
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
#endif
    int t;
    cin >> t;
    while(t--) {
        gentest();
    }
}