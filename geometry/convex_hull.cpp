#include "point.h"

// Bao loi khong tinh diem thang hang, nguoc chieu kim dong ho
// Stress test https://judge.yosupo.jp/problem/static_convex_hull
void convex_hull(vector<Point>& a) {
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());

    if(a.size() <= 2) return;

    vector<Point> up;
    vector<Point> down;

    Point p1 = a[0], p2 = a.back();
    up.push_back(p1);
    down.push_back(p1);
    
    for(int i = 1; i < a.size(); i++) {
        if(i == a.size() - 1 || ccw(p1, a[i], p2) > 0) {
            while (up.size() >= 2 && ccw(up[up.size()-2], up[up.size()-1], a[i]) <= 0)
                up.pop_back();
            up.push_back(a[i]);
        }


        if(i == a.size() - 1 || ccw(p1, a[i], p2) < 0) {
            while (down.size() >= 2 && ccw(down[down.size() - 2], down[down.size()-1], a[i]) >= 0)
                down.pop_back();
            down.push_back(a[i]);
        }
    }

    if(up.size() == a.size()) return;

    a = up;
    for(int i = down.size() - 2; i > 0; i--) {
        a.push_back(down[i]);
    }
}
