#include "point.h"
#define int long long

// Tra ve 2 lan dien tich da giac
int polygon_area(vector<Point>& p) {
    int n = p.size();
    int s = 0;
    for(int i = 0; i < n; i++) {
        s += p[i] * p[(i+1)%n];
    }
    return abs(s);
}
#undef int
