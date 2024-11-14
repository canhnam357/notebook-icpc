#include <bits/stdc++.h>
#define int long long
using namespace std;
const int inf = 1e18;

// y = a * x + b
struct Line {
    int a;
    int b;
};
bool operator < (Line a, Line b) {
    return true;
}
int lower_divide(int a, int b) {
    return a / b;
}
int upper_divide(int a, int b) {
    return (a+b-1) / b;
}
// Duoc dat trong comment la dao chieu hull
struct Hull {
    vector<int> pos;
    vector<Line> lines;
    Hull(Line first) {
        pos.emplace_back(-inf);
//        pos.emplace_back(inf);
        lines.emplace_back(first);
    }
    // Them duong thang voi a tang dan
    // Trong comment: them duong thang voi a giam dan
    void update(Line l) {
        int A = l.a;
        int B = l.b;
        while(true) {
            int A1 = lines.back().a;
            int B1 = lines.back().b;
            int X1 = pos.back();
            // A * X + B == A1 * X + B1
            int intersect = lower_divide(B - B1, A1 - A);
//            int intersect = upper_divide(B - B1, A1 - A);
            if(intersect <= X1) {
//            if(intersect >= X1) {
                pos.pop_back();
                lines.pop_back();
            }
            else {
                pos.push_back(intersect);
                lines.push_back({A, B});
                break;
            }
        }
    }
    int query(int X) {
        int p = lower_bound(pos.begin(), pos.end(), X) - pos.begin() - 1;
//        int p = lower_bound(pos.begin(), pos.end(), X, greater<int>()) - pos.begin() - 1;
        Line l = lines[p];
        return l.a * X + l.b;
    }
};

