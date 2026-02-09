// (Real number coordinate sometime not trustable)
#include "point.h"

// Kiem tra b co nam giua a va c khong (neu a, b, c da thang hang)
bool between(Point a, Point b, Point c) {
    return a <= b && b <= c || c <= b && b <= a;
}

// Kiem tra b co nam giua a va c khong (a, b, c chua chac da thang hang)
bool on_segment(Point a, Point b, Point p) {
    return ccw(a, b, p) == 0 && between(a, p, b);
}

// Kiem tra AB va CD co diem chung nam hoan toan ben trong khong
bool is_inner_intersect(Point a, Point b, Point c, Point d) {
    int c1 = ccw(a, b, c);
    int c2 = ccw(a, b, d);
    int c3 = ccw(c, d, a);
    int c4 = ccw(c, d, b);
    return c1 * c2 < 0 && c3 * c4 < 0;
}

// Kiem tra giao diem cua 2 duong thang, tra ve
// 0 neu khong co diem chung
// 1 neu co diem cat nhau o bien
// 2 neu co doan chung
// -1 neu cat nhau hoan toan ben trong
int count_intersect(Point a, Point b, Point c, Point d) {
    if (a == b) {
        return on_segment(c, d, a);
    }

    if (c == d) {
        return on_segment(a, b, c);
    }

    int c1 = ccw(a, b, c);
    int c2 = ccw(a, b, d);
    int c3 = ccw(c, d, a);
    int c4 = ccw(c, d, b);

    if (c1 * c2 < 0 && c3 * c4 < 0) return -1;
    if (c1 * c2 != 0 && c3 * c4 != 0) return 0;

    int cnt = 0;
    if (c1 == 0 && between(a, c, b)) cnt++;
    if (c2 == 0 && between(a, d, b)) cnt++;
    if (c3 == 0 && between(c, a, d)) cnt++;
    if (c4 == 0 && between(c, b, d)) cnt++;

    if(a == c || a == d) cnt--;
    if(b == c || b == d) cnt--;

    return cnt;
}
