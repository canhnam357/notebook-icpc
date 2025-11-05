#include<bits/stdc++.h>
#define int long long
using namespace std;
#define sqr(x) ((x) * (x))
const double pi = acos(-1);

int comp(int x) {
    if(x > 0)
        return 1;
    else if(x < 0)
        return -1;
    else
        return 0;
}

// Diem co toa do (x, y)
// Hoac vector co toa do (x, y)
struct Point {
    int x, y;
    void input() {
        cin >> x >> y;
    }
    void norm() {
        if(x < 0 || x == 0 && y < 0) {
            x = -x;
            y = -y;
        }
        int g = __gcd(abs(x), abs(y));
        if(g != 0) {
            x /= g;
            y /= g;
        }
    }
};
bool operator < (Point a, Point b) {
    return a.x < b.x || a.x == b.x && a.y < b.y;
}
bool operator <= (Point a, Point b) {
    return a.x < b.x || a.x == b.x && a.y <= b.y;
}
bool operator > (Point a, Point b) {
    return a.x > b.x || a.x == b.x && a.y > b.y;
}
bool operator >= (Point a, Point b) {
    return a.x > b.x || a.x == b.x && a.y >= b.y;
}
bool operator == (Point a, Point b) {
    return a.x == b.x && a.y == b.y;
}


// Tra ve phep tru vector
Point operator - (Point a, Point b) {
    return {a.x - b.x, a.y - b.y};
}

// Tra ve phep nhan co huong
int operator * (Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

// Tra ve phep nhan vo huong
int dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

// Tra ve 1 neu a, b, c nguoc chieu kim dong ho (re trai)
//       -1 neu a, b, c cung chieu kim dong ho (re phai)
//        0 neu a, b, c thang hang
int ccw(Point a, Point b, Point c) {
    int val = (b - a) * (c - b);
    return comp(val);
}

// Tra ve d^2
int sqr_len(Point a) {
    return sqr(a.x) + sqr(a.y);
}
#undef int
