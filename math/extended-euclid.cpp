// Dung extended euclid de tim nghiem cua phuong trinh
// a*x + b*y = gcd(a, b)
int euclid(int a, int b, int& x, int& y) {
    x = 1, y = 0;
    int x1 = 0, y1 = 1, a1 = a, b1 = b;
    while (b1 != 0) {
        int q = a1 / b1;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    if (a1 < 0) {
        a1 = -a1;
        x = -x;
        y = -y;
    }
    return a1;
}

// Tinh nghich dao su dung extended euclid
// Tra ve -1 neu khong ton tai nghich dao
int inverse_euclid(int a, int mod) {
    int x, y;
    int g = euclid(a, mod, x, y);
    if(g == 1) {
        x = (x % mod + mod) % mod;
        return x;
    }
    else {
        // No solution
        return -1;
    }
}

// Giai phuong trinh (ax + by = c)
// Neu ton tai tao ra mot ho nghiem, do la (x + dx * k) va (y + dy * k)
bool solve_extended_euclid(int a, int b, int c, int &x, int& dx, int &y, int &dy) {
    assert(a != 0 || b != 0);
    int g = euclid(a, b, x, y);
    if (c % g != 0) return false;
    x *= c / g;
    y *= c / g;
    dx = b / g;
    dy = -a / g;
    return true;
}
