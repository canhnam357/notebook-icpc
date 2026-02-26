struct matrix {
    vector<vector<int>> a;
    int n, m;
    matrix(int n, int m) {
        this->n = n; this->m = m;
        a = vector<vector<int>>(n, vector<int>(m));
    }
};
int _gcd(int a, int b) {
    return b == 0 ? a : _gcd(b, a%b);
}
// rut gon cac so trong a
void norm_array(vector<int>& a) {
    int g = 0;
    for(int i : a)
        g = _gcd(g, abs(i));
    for(int i : a)
        if(i != 0) {
            if(i < 0)
                g *= -1;
            break;
        }
    for(int &i : a) i /= g;
}
void gauss_elimination(matrix& mat) {
    int n = mat.n, m = mat.m;
    for(int i = 0; i < n-1; i++) {
        // tim hang co a[i][i] != 0
        for(int j = i; j < n; j++) {
            if(mat.a[j][i] != 0) {
                swap(mat.a[j], mat.a[i]);
                break;
            }
        }
        // rut gon cac hang duoi
        for(int j = i+1; j < n; j++) {
            for(int k = m-1; k >= i; k--) {
                mat.a[j][k] = mat.a[j][k] * mat.a[i][i] - mat.a[i][k] * mat.a[j][i]; 
            }
            norm_array(mat.a[j]);
        }
    }
    for(int i = 1; i < n; i++) {
        // rut gon cac hang tren
        for(int j = i-1; j >= 0; j--) {
            for(int k = m-1; k >= i; k--) {
                mat.a[j][k] = mat.a[j][k] * mat.a[i][i] - mat.a[i][k] * mat.a[j][i];
            }
            for(int k = i-1; k >= 0; k--)
                mat.a[j][k] *= mat.a[i][i];
        }
    }
}
