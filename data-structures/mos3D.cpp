const int maxN = 1e5 + 5;
struct query{
    int l, r, k, t, id;
};
// Luu lai thong tin cap nhat: Sau khi thuc hien truy van nay, a[index] = old se tro thanh a[index] = next. Luu lai nhu vay nham muc dich thuan tien khi dao nguoc truy van.
struct update{
    int index, old, next;
};
vector<update> update_queries;
vector<query> queries;
int n, q, a[maxN], b[maxN], has[maxN] = {}, S, l = 1, r = 0, t = -1;
int occ[maxN] = {}, ans[maxN], ord[maxN] = {}, f[maxN] = {};
pair<int, int> range[maxN] = {};
bool cmp(const query &a, const query &b){
    if(a.l / S != b.l / S)
        return a.l < b.l;
    else if(a.r / S != b.r / S){
        if((a.l / S) % 2 == 1)
            return a.r < b.r;
        else
            return a.r > b.r;
    }
    return a.t < b.t;
}
void add(int x) {
}
void rmv(int x) {
}
void run_update(int i, int x){
    // Neu i nam trong [l, r], viec cap nhat se anh huong den dap an
    if(l <= i && i <= r){
        rmv(a[i]);
        add(x);
    }
    a[i] = x;
}
signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    memset(ans, -1, sizeof ans);
    S = pow(2LL * n * n, 1. / 3.) + 1;
    for(int i = 1; i <= q; i++){   	
       	int t;
       	cin >> t;
       	int u, v;
        cin >> u >> v;
        if(t == 2){
            update_queries.push_back({u, b[u], v});
            b[u] = v;
        }else{
        	int k;
        	cin >> k;
            queries.push_back({u, v, k, (int)update_queries.size() - 1, i});
            has[i] = 1;
        }
    }
    sort(queries.begin(), queries.end(), cmp);
    for(query &q : queries){
        // Truy van cap nhat
        while(t < q.t) t++, run_update(update_queries[t].index, update_queries[t].next);
        // Dao nguoc truy van cap nhat
        while(t > q.t) run_update(update_queries[t].index, update_queries[t].old), t--;
        while (l > q.l) add(a[--l]);
        while (r < q.r) add(a[++r]);
        while (l < q.l) rmv(a[l++]);
        while (r > q.r) rmv(a[r--]);
        // answer query here
    }
}
