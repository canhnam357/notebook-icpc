#include "extended-euclid.h"
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
//vector<Congruence> a = { {0, 1001}, {2, 1003} , {5, 1005} };
//cout << chinese_remainder(a) << "\n";
