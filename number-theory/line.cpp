#include "point.h"
#define int long long
// Duong thang co phuong trinh ax + by = c
struct Line {
    int a;
    int b;
    int c;
    void norm() {
        if(a < 0 || a == 0 && b < 0 || a == 0 && b == 0 && c < 0) {
            a = -a;
            b = -b;
            c = -c;
        } 
        int g = __gcd(abs(a), __gcd(abs(b), abs(c)));
        if(g != 0) {
            a /= g;
            b /= g;
            c /= g;
        }
    }
};

// Tra ve duong thang AB
Line to_line(Point a, Point b) {
    if(a == b) {
        return {0, 0, 0};
    }
    Line res;
    res.a = a.y - b.y;
    res.b = b.x - a.x;
    res.c = res.a * a.x + res.b * a.y;
    return res;
}

// Tra ve khoang cach giua diem va duong thang
double point_distance_to_line(Point p, Line l) {
    return abs(l.a * p.x + l.b * p.y + l.c) / sqrt(sqr(l.a) + sqr(l.b));
}

#undef int