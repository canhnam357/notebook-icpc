// Tra ve 2 lan dien tich da giac
num_t polygon_area(vector<Point>& p) {
    int n = p.size();
    num_t s = 0;
    for(int i = 0; i < n; i++) {
        s += p[i] * p[(i+1)%n];
    }
    return abs(s);
}
