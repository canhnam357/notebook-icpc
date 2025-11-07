// suffix_link : nhay toi nut co do dai nho hon ma lon nhat va la suffix cua chuoi hien tai (vi la trie nen chuoi hien tai la 1 prefix cua mot chuoi da them vao)
// exit_link : la nut gan nhat sau khi nhay (> 0) lan va nut do la ket thuc cua 1 trong nhung chuoi da them vao
// trong ham get() tim nhung chuoi la suffix cua hien tai theo do dai giam dan
struct aho_corasick{
    struct node{
        int suffix_link = -1, exit_link = -1, nxt[26], tot = 0;
        bool has = false;
        node() {fill(nxt, nxt + 26, -1);}
    };
    vector<node> g = {node()};
    void insert_string(const string &s, int point){
        int p = 0;
        for (char c: s){
            if (g[p].nxt[c - 'A'] == -1){
                g[p].nxt[c - 'A'] = g.size();
                g.emplace_back();
            }
            p = g[p].nxt[c - 'A'];
        }
        g[p].has = true;
        g[p].tot += point;
    }
    void build_automaton(){
        for (deque<int> q = {0}; q.size(); q.pop_front()){
            int v = q.front(), suffix_link = g[v].suffix_link;
            if (v) g[v].exit_link = g[suffix_link].has ? suffix_link : g[suffix_link].exit_link;
            for (int i=0; i< 26; i++){
                int &nxt = g[v].nxt[i], nxt_sf = v ? g[suffix_link].nxt[i] : 0;
                if (nxt == -1) nxt = nxt_sf;
                else{
                    g[nxt].suffix_link = nxt_sf;
                    q.push_back(nxt);
                }
            }
        }
    }
    int get(int p) {
        int res = 0;
        for (int v = g[p].has ? p : g[p].exit_link; v != -1; v = g[v].exit_link) {
            res += g[v].tot;
        }
        return res;
    }
    int feed(int u, int c) {
        return g[u].nxt[c];
    }
};
