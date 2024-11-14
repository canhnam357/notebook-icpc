#include "point.h"
#define int long long
// Tra ve A <= B <= C
bool between(Point a, Point b, Point c) {
    return a <= b && b <= c || c <= b && b <= a;
}

// Kiem tra 2 doan thang AB va CD co diem chung khong
bool is_intersect(Point a, Point b, Point c, Point d) {
    int c1 = ccw(a, b, c);
    int c2 = ccw(a, b, d);
    int c3 = ccw(c, d, a);
    int c4 = ccw(c, d, b);
    
    if(c1 == 0 && between(a, c, b))
        return true;
    if(c2 == 0 && between(a, d, b))
        return true;
    if(c3 == 0 && between(c, a, d))
        return true;
    if(c4 == 0 && between(c, b, d))
        return true;
    return c1*c2 < 0 && c3*c4 < 0;
}

// in ra so luong giao diem 2 doan thang
// tra ve 2 neu co 1 doan chung
int number_intersect(Point a, Point b, Point c, Point d) {
    if(a > b)
        swap(a, b);
    if(c > d)
        swap(c, d);
    int c1 = ccw(a, b, c);
    int c2 = ccw(a, b, d);
    int c3 = ccw(c, d, a);
    int c4 = ccw(c, d, b);
    int cnt = 0;
    if(!c1 && between(a, c, b))
        cnt++;
    if(!c2 && between(a, d, b))
        cnt++;
    if(!c3 && between(c, a, d))
        cnt++;
    if(!c4 && between(c, b, d))
        cnt++;
    
    if(cnt > 0) {
        if(a == c || b == d || a == d || b == c) {
            return min(cnt-1, 2LL);
        }
        else
            return min(cnt, 2LL);
    }
    else {
        return c1*c2 < 0 && c3*c4 < 0;
    }
}
#undef int