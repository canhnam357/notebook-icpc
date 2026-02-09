#include<bits/stdc++.h>
using namespace std;

#define sqr(x) ((x) * (x))
using num_t = long long;
// using num_t = double;
using ll = long long;

const num_t EPS = 1e-8;
const double PI = acos(-1);

inline int comp(num_t x) {
    if (x > EPS) return 1;
    if (x < -EPS) return -1;
    return 0;
}

// Diem co toa do (x, y)
// Hoac vector co toa do (x, y)
struct Point {
    num_t x, y;
    void input() {
        cin >> x >> y;
    }
    Point() {}
    Point(num_t x, num_t y) {this->x = x; this->y = y;}
    void norm() {
        if(x < 0 || x == 0 && y < 0) {
            x = -x;
            y = -y;
        }
        int g = __gcd(llabs((ll)x), llabs((ll)y));
        if(g != 0) {
            x /= g;
            y /= g;
        }
    }
};

bool operator < (Point a, Point b) {
    int cx = comp(a.x - b.x);
    if (cx != 0) return cx < 0;
    return comp(a.y - b.y) < 0;
}
bool operator == (Point a, Point b) { return comp(a.x - b.x) == 0 && comp(a.y - b.y) == 0; }
bool operator <= (Point a, Point b) { return (a < b) || (a == b); }
bool operator  > (Point a, Point b) { return b < a; }
bool operator >= (Point a, Point b) { return (b < a) || (a == b); }
bool operator != (Point a, Point b) { return !(a == b); }

Point operator + (Point a, Point b) { return Point(a.x + b.x, a.y + b.y); }
Point operator - (Point a, Point b) { return Point(a.x - b.x, a.y - b.y); }
Point operator * (Point a, num_t x) { return Point(a.x * x, a.y * x); }
Point operator / (Point a, num_t x) { return Point(a.x / x, a.y / x); }

// Tra ve phep nhan co huong
// Tra ve phep nhan vo huong
num_t operator * (Point a, Point b) { return a.x * b.y - a.y * b.x; }
num_t dot(Point a, Point b) { return a.x * b.x + a.y * b.y; }

// Tra ve 1 neu a, b, c nguoc chieu kim dong ho (re trai)
//       -1 neu a, b, c cung chieu kim dong ho (re phai)
//        0 neu a, b, c thang hang
int ccw(Point a, Point b, Point c) {
    return comp((b - a) * (c - b));
}
