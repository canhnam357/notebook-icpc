// Dung extended euclid de tim nghiem cua phuong trinh
// a*x + b*y = gcd(a, b)
// return gcd va 2 tham chieu x, y
// Phuong trinh tong quat co nghiem khi d chia het cho gcd(a, b)
int extended_euclid(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1; y = 0;
        return a;
    }
    int x1, y1;
    int d = extended_euclid(b, a % b, x1, y1);
    x = y1; y = x1 - y1 * (a / b);
    return d;
}
// Tinh nghich dao su dung extended euclid
int inverse_extended_euclid(int a, int mod) {
    int x, y;
    int g = extended_euclid(a, mod, x, y);
    if(g == 1) {
        x = (x % mod + mod) % mod;
        return x;
    }
    else {
        // No solution
        return -1;
    }
}
