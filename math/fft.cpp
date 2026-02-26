#define sqr(x) ((x) * (x))

struct Cmplx {
    double x, y;
    Cmplx(double x = 0, double y = 0) {this->x = x; this->y = y;}
    double real() {return x;}
    double imag() {return y;}
};
Cmplx operator + (Cmplx a, Cmplx b) {return Cmplx(a.x + b.x, a.y + b.y); }
Cmplx operator - (Cmplx a, Cmplx b) { return Cmplx(a.x - b.x, a.y - b.y); }
Cmplx operator * (Cmplx a, Cmplx b) { return Cmplx(a.x*b.x - a.y*b.y, a.x*b.y + a.y*b.x); }
Cmplx operator * (Cmplx a, double b) { return Cmplx(a.x*b, a.y*b); }
Cmplx operator / (Cmplx a, double b) { return Cmplx(a.x/b, a.y/b); }
Cmplx operator / (Cmplx a, Cmplx b) {
    return Cmplx(a.x*b.x + a.y*b.y, a.y*b.x - a.x*b.y) / (sqr(b.x) + sqr(b.y));
}
Cmplx conj(Cmplx a) {return Cmplx(a.x, -a.y);}

using cd = Cmplx;
//using cd = complex<double>;
const double PI = acos(-1);

void fft(vector<cd>& a, int n, bool invert) {
    for(int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        while(j & bit) {
            j ^= bit;
            bit >>= 1;
        }
        j ^= bit;
        if(i < j) swap(a[i], a[j]);
    }

    for(int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len;
        if(invert) ang = -ang;
        cd wlen(cos(ang), sin(ang));
        for(int i = 0; i < n; i += len) {
            cd w(1);
            for(int j = 0; j < len/2; j++) {
                cd u = a[i + j];
                cd v = a[i + j + len/2] * w;
                a[i + j] = u + v;
                a[i + j + len/2] = u - v;
                w = w * wlen;
            }
        }
    }
    if(invert) {
        for(cd & x : a) x = x / (double)n;
    }
}

vector<cd> f1;
vector<cd> f2;
vector<int64_t> multiply(const vector<int>& a, const vector<int>& b) {
    int need = a.size() + b.size() - 1;
    int sz = 1;
    while (sz < need) sz <<= 1;
    if(sz > f1.size()) {
        f1.resize(sz);
        f2.resize(sz);
    }
    for(int i = 0; i < sz; i++) {
        double x = (i < a.size() ? a[i] : 0);
        double y = (i < b.size() ? b[i] : 0);
        f1[i] = cd(x, y);
    }
    fft(f1, sz, false);
    for(int i = 0; i < sz; i++) {
        int j = (sz - i) & (sz - 1);
        cd x = (f1[i] + conj(f1[j])) / cd(2,0);
        cd y = (f1[i] - conj(f1[j])) / cd(0,2);
        f2[i] = x*y;
    }
    fft(f2, sz, true);
    vector<int64_t> res(need);
    for (int i = 0; i < need; i++) res[i] = llround(f2[i].real());
    return res;
}
