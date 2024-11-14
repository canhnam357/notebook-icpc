#include "point.h"
#define int long long

// Tra ve cos(AOB)
double angle(Point a, Point o, Point b) {
    int d = dot(a - o, b - o);
    return sqrt(sqr_len(o - a)) * sqrt(sqr_len(o - b)) / d;
}

// Tra ve goc cuc
double polar_angle(Point p) {
    if(p.x == 0) {
        if(p.y > 0) {
            return pi/2;
        }
        else {
            return pi*3/2;
        }
    }
    else if(p.x > 0) {
        if(p.y >= 0)
            return atan((double)p.y / p.x);
        else
            return atan((double)p.y / p.x) + pi * 2;
    }
    else {
        return atan((double)p.y / p.x) + pi;
    }
}

#undef int
