#include "point.h"

// Tra ve cos(AOB)
double angle(Point a, Point o, Point b) {
    int d = dot(a - o, b - o);
    return sqrt(sqr_len(o - a)) * sqrt(sqr_len(o - b)) / d;
}
// Tra ve goc luong giac
double polar_angle(Point p) {
    assert(p != Point(0, 0));
    if(comp(p.x) == 0) {
        return (comp(p.y) > 0 ? PI/2 : -PI/2);
    }
    else {
        double ans = atan((double) p.y / p.x);
        if(comp(p.x) < 0) ans += PI;
        if(ans < 0) ans += PI * 2;
        return ans;
    }
}

