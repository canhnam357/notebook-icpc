#include "check_intersect.h"
#include "line.h"

// center (x, y), radius r
struct Circle {
    num_t x;
    num_t y;
    num_t r;
    Circle() {}
    Circle(num_t x, num_t y, num_t r) {this->x = x; this->y = y; this->r = r;}
};

double det(double a, double b, double c, double d) {
    return a*d - b*c;
}

// Giao diem 2 duong thang
// Tra ve false neu 2 duong thang song song hoac trung nhay
// Nguoc lai tra ve true va giao diem
bool intersect_line_line(Line m, Line n, Point& res) {
    double zn = det(m.a, m.b, n.a, n.b);
    if (abs(zn) < EPS)
        return false;
    res.x = -det(m.c, m.b, n.c, n.b) / zn;
    res.y = -det(m.a, m.c, n.a, n.c) / zn;
    return true;
}

// Tra ve diem giao nhau cua 2 doan thang AB va CD
// Trong truong hop co doan chung, tra ve doan thang giao nhau chung theo thu tu tang dan
vector<Point> intersect_segment_segment(Point a, Point b, Point c, Point d) {
    int cnt = count_intersect(a, b, c, d);
    if(cnt == 0) {
        return {};
    }
    else if(cnt == -1) { // co diem chung o giua
        Point ans;
        intersect_line_line(to_line(a, b), to_line(c, d), ans);
        return {ans};
    }
    else {
        vector<Point> ans;
        if(on_segment(a, b, c)) {ans.push_back(c);}
        if(on_segment(a, b, d)) {ans.push_back(d);}
        if(on_segment(c, d, a)) {ans.push_back(a);}
        if(on_segment(c, d, b)) {ans.push_back(b);}
        sort(ans.begin(), ans.end());
        ans.erase(unique(ans.begin(), ans.end()), ans.end());
        return ans;
    }
}

// Giao diem duong thang va duong tron
vector<Point> intersect_line_circle(Line l, Circle c1) {
    double dx = c1.x;
    double dy = c1.y;
    vector<Point> ans;

    double a = l.a;
    double b = l.b;
    double c = l.c + l.a * dx + l.b * dy;
    double r = c1.r;
    double x0 = -a*c / (sqr(a) + sqr(b));
    double y0 = -b*c / (sqr(a) + sqr(b));
    if (sqr(c) > sqr(r) * (sqr(a) + sqr(b)) + EPS) {
        return ans;
    }
    else if (abs (sqr(c) - sqr(r) * (sqr(a) + sqr(b))) < EPS) {
        ans.push_back({x0 + dx, y0 + dy});
        return ans;
    }
    else {
        double d = sqr(r) - sqr(c) / (sqr(a) + sqr(b));
        double mult = sqrt (d / (sqr(a) + sqr(b)));
        double ax, ay, bx, by;
        ax = x0 + b * mult + dx;
        bx = x0 - b * mult + dx;
        ay = y0 - a * mult + dy;
        by = y0 + a * mult + dy;
        
        ans.push_back({ax, ay});
        ans.push_back({bx, by});
    }
    return ans;
}

// Giao diem 2 duong tron
vector<Point> intersect_circle_circle(Circle c1, Circle c2) {
    double dx = c1.x;
    double dy = c1.y;
    c2.x -= c1.x;
    c2.y -= c1.y;
    c1.x = 0;
    c1.y = 0;

    Line l;
    l.a = -2 * c2.x;
    l.b = -2 * c2.y;
    l.c = sqr(c2.x) + sqr(c2.y) + sqr(c1.r) - sqr(c2.r);
    vector<Point> ans = intersect_line_circle(l, c1);
    for(Point& p : ans) {
        p.x += dx;
        p.y += dy;
    }
    return ans;
}
