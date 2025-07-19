#include <bits/stdc++.h>
using namespace std;
#define all(x) x.begin(), x.end()
// suffix_link : nhảy tới nút có độ dài nhỏ hơn mà lớn nhất và là suffix của chuỗi hiện tại (vì là trie nên chuỗi hiện tại là 1 prefix của một chuỗi đã thêm vào)
// exit_link : là nút gần nhất sau khi nhảy (> 0) lần và nút đó là kết thúc của 1 trong những chuỗi đã thêm vào
struct aho_corasick{
    struct node{
        int suffix_link = -1, exit_link = -1, nxt[26];
        bool has = false;
        node() {fill(nxt, nxt + 26, -1);}
    };
    vector<node> g = {node()};
    void insert_string(const string &s){
        int p = 0;
        for (char c: s){
            if (g[p].nxt[c - 'a'] == -1){
                g[p].nxt[c - 'a'] = g.size();
                g.emplace_back();
            }
            p = g[p].nxt[c - 'a'];
        }
        g[p].has = true;
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
    int feed(int p, int c) {
        return g[p].nxt[c];
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
