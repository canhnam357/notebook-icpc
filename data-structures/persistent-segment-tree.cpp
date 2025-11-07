#define N  1000000 // N must double of update or add
#define LG 20 // log
int L[N * LG], R[N * LG], val[N * LG], root[N];
long long sum[N * LG];
int M = 0, p = 2, n = 200001;
void update(int id, int l, int r, int x) {
    val[id]++; sum[id] += x;
    if (l != r) {
        int mid = (l + r) >> 1;
        int u = L[id], v = R[id];
        if (x <= mid) {
            L[id] = p++;
            tie(L[L[id]], R[L[id]], val[L[id]], sum[L[id]]) = {L[u], R[u], val[u], sum[u]};
            update(L[id], l, mid, x);
        }
        else {
            R[id] = p++;
            tie(L[R[id]], R[R[id]], val[R[id]], sum[R[id]]) = {L[v], R[v], val[v], sum[v]};
            update(R[id], mid + 1, r, x);
        }
    }
}
void create_node(int x) {
    root[++M] = p++;
    tie(L[root[M]], R[root[M]], val[root[M]], sum[root[M]]) = {L[root[M - 1]], R[root[M - 1]], val[root[M - 1]], sum[root[M - 1]]};
    update(root[M], 1, n, x);
}
long long get_occ(int v, int u, int x, int y, int l, int r) {
    if (r < x || l > y) return 0;
    if (l >= x && r <= y) return val[u] - val[v];
    int mid = (l + r) >> 1;
    return get_occ(L[v], L[u], x, y, l, mid) + get_occ(R[v], R[u], x, y, mid + 1, r);
}
long long get_occ(int l, int r, int x, int y) {
    return get_occ(root[l - 1], root[r], x, y, 1, n);
}
long long get_sum(int v, int u, int x, int y, int l, int r) {
    if (r < x || l > y) return 0;
    if (l >= x && r <= y) return sum[u] - sum[v];
    int mid = (l + r) >> 1;
    return get_sum(L[v], L[u], x, y, l, mid) + get_sum(R[v], R[u], x, y, mid + 1, r);
}
long long get_sum(int l, int r, int x, int y) {
    return get_sum(root[l - 1], root[r], x, y, 1, n);
}
long long get_kth(int v, int u, int x, int l, int r) {
    if (l == r) return r;
    int k = val[L[u]] - val[L[v]];
    int mid = (l + r) >> 1;
    if (k >= x) return get_kth(L[v], L[u], x, l, mid);
    return get_kth(R[v], R[u], x - k, mid + 1, r);
}
long long get_kth(int l, int r, int x) {
    return get_kth(root[l - 1], root[r], x, 1, n);
}
void build(int id, int l, int r) {
    val[id] = sum[id] = 0;
    if (l == r) return;
    int mid = (l + r) >> 1;
    L[id] = p++; R[id] = p++;
    build(L[id], l, mid);
    build(R[id], mid + 1, r);
}

// root[0] = 1
// build(1, 1, n);
// node in order of call create_node 
