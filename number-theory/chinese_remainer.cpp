#include "extended_euclid.h"
#define int long long
using namespace std;

struct Congruence {
    int a, m;
};
int chinese_remainder(vector<Congruence> c) {
    int M = 1;
    for (Congruence x : c) {
        M *= x.m;
    }
    int ans = 0;
    for (Congruence x : c) {
        int a_i = x.a;
        int M_i = M / x.m;
        // inverse(a, mod) : nghich dao modulo cua a
        int N_i = inverse_extended_euclid(M_i, x.m);
        ans = (ans + a_i * M_i % M * N_i) % M;
    }
    return ans;
}

// input (2, 3), (3, 4), (4, 5) (mod 3 = 2, mod 4 = 3, mod 5 = 4)
// output 59
// input (0, 1001), (2, 1003), (5, 1005)
// output 378508130
void test_chinese_remainder() {
    vector<Congruence> a = { {0, 1001}, {2, 1003} , {5, 1005} };
    cout << chinese_remainder(a) << "\n";
}
