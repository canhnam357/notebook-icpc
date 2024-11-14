// source problem : 
#include <bits/stdc++.h>
using namespace std;
#define all(x) x.begin(), x.end()
#define int long long
#define lb lower_bound
#define ub upper_bound
#define MASK(i) (1LL << (i))
const int inf = 1e18;
void ckmax(int& f, int s)
{
    f = (f > s ? f : s);
}
void ckmin(int& f, int s)
{
    f = (f < s ? f : s);
}
istream &operator>>(istream &is, __int128 &v) {
    string s;
    is>>s;
    v=0;
    for(auto &it:s) if(isdigit(it)) v=v*10+it-'0';
    if(s[0]=='-') v*=-1;
    return is;
}

ostream &operator<<(ostream &os,const __int128 &v) {
    if(v==0) return (os<<"0");
    __int128 num=v;
    if(v<0) os<<'-',num=-num;
    string s;
    for(;num>0;num/=10) s.push_back((char)(num%10)+'0');
    reverse(all(s));
    return (os<<s);
}
int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    __int128 x = 999999999;
    __int128 z = 999999999;
    x = x * x;
    x = x * x;
    x = x / z;
    x = x / z;
    x = x / z;
    cout << x;
    return 0;
}