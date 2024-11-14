#include <bits/stdc++.h>
using namespace std;
#define all(x) x.begin(), x.end()
struct aho_corasick{
    struct node{
        int suffix_link = -1, exit_link = -1, nxt[26];
        vector<int> leaf;
        node() {fill(nxt, nxt + 26, -1);}
    };
    vector<node> g = {node()};
    void insert_string(const string &s, int sidx){
        int p = 0;
        for (char c: s){
            if (g[p].nxt[c - 'a'] == -1){
                g[p].nxt[c - 'a'] = g.size();
                g.emplace_back();
            }
            p = g[p].nxt[c - 'a'];
        }
        g[p].leaf.push_back(sidx);
    }
    void cc()
    {
        for (int i = 0; i < g.size(); i++)
        {
            if (g[i].leaf.size())
            {
                sort(all(g[i].leaf));
                g[i].leaf.erase(unique(all(g[i].leaf)), g[i].leaf.end());
            }
        }
    }
    void build_automaton(){
        for (deque<int> q = {0}; q.size(); q.pop_front()){
            int v = q.front(), suffix_link = g[v].suffix_link;
            if (v) g[v].exit_link = g[suffix_link].leaf.size() ? suffix_link : g[suffix_link].exit_link;
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
    vector<int> get_sindex(int p){
        vector<int> a;
        for (int v = g[p].leaf.size() ? p : g[p].exit_link; v != -1; v = g[v].exit_link)
            for (int j: g[v].leaf)
                a.push_back(j);
        sort(all(a));
        a.erase(unique(all(a)), a.end());
        return a;
    }
};

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    aho_corasick ac;
    int n;
    string z;
    cin >> n >> z;
    int m;
    cin >> m;
    vector<int> len;
    for (int i = 0; i < m; i++)
    {
        string s;
        cin >> s;
        ac.insert_string(s, s.size());
    }
    ac.build_automaton();
    ac.cc();
    vector<int> dp(n, 123123123);
    for (int r = 0, p = 0; r < n; r++)
    {
        p = ac.g[p].nxt[z[r] - 'a'];
        for (int j: ac.get_sindex(p))
        {
            int l = r - j + 1;
            if (l == 0) dp[r] = min(dp[r], 1);
            else dp[r] = min(dp[r], dp[l - 1] + 1);
        }
    }
    cout << dp[n - 1];
    return 0;
}