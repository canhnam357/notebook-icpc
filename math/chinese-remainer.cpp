#include "extended_euclid.h"
#define int long long
int chinese(int a, int m, int b, int n) {
    int32_t x, y;
    euclid(m, n, x, y);
    int ret = a * (y + m) % m * n + b * (x + n) % n * m;
    if (ret >= m * n) ret -= m * n;
    return ret;
}
int chinese_common(int a, int m, int b, int n) {
    int d = __gcd(m, n);
    b = ((b - a) % n + n) % n;
    if (b % d != 0) return -1;
    return d * chinese(0, m/d, b/d, n/d) + a;
}