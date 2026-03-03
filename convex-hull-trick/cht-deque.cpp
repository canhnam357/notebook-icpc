using ll = long long;
const ll inf = 1.1e18;
// y = a * x + b
struct Line {
    ll a, b;
    ll calc(ll x) { return a * x + b; }
};
ll upper_divide(ll a, ll b) {
    return a / b + ((a ^ b) > 0 && a % b);
}

// Complexity: O(N+Q)
// To know usage of this code, see [line container]
// Require increasing add/query (and manual deque)
// "add_dec" and "query_dec" using for decreasing add/query
struct CHT_Deque {
    deque<pair<ll, Line>> lines;
    void add(ll a, ll b) {
        Line l = {a, b};
        if(lines.empty()) {
            lines.emplace_back(-inf, l);
        }
        else {
            Line l_back = lines.back().second;
            assert(l.a >= l_back.a);

            if(l.a == l_back.a) {
                if(l.b <= l_back.b) return;
                lines.pop_back();
            }
            while(!lines.empty()) {
                l_back = lines.back().second;
                ll x = lines.back().first;
                ll new_x = upper_divide(l_back.b - l.b, l.a - l_back.a);
                if(new_x <= x) lines.pop_back();
                else break;
            }
            if(lines.empty()) {
                lines.emplace_back(-inf, l);
            }
            else {
                ll new_x = upper_divide(l_back.b - l.b, l.a - l_back.a);
                lines.emplace_back(new_x, l);
            }
        }
    }
    ll query(ll x) {
        while(lines.size() > 1 && next(lines.begin())->first <= x) {
            lines.pop_front();
            lines.front().first = -inf;
        }
        return lines.front().second.calc(x);
    }
    void add_dec(ll a, ll b) {
        add(-a, b);
    }
    ll query_dec(ll x) {
        return query(-x);
    }
};
