#include <bits/stdc++.h>
#include <unordered_map>
#include <stdlib.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <atcoder/all>
using namespace atcoder;
using namespace boost::multiprecision;
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
//constexpr ll MOD = 1000000007;
constexpr ll MOD = 998244353;
constexpr int IINF = 1001001001;
constexpr ll INF = 1LL<<60;
template<class t,class u> void chmax(t&a,u b){if(a<b)a=b;}
template<class t,class u> void chmin(t&a,u b){if(b<a)a=b;}

using mint = modint998244353;

ll gcd(ll a, ll b){
    if(a%b == 0){
      return b;
    }else{
      return gcd(b, a%b);
    }
}

ll lcm(ll a, ll b){
    return a*b / gcd(a, b);
}

ll powMod(ll x, ll n) {
    if (n == 0) return 1 % MOD;
    ll val = powMod(x, n / 2);
    val *= val;
    val %= MOD;
    if (n % 2 == 1) val *= x;
    return val % MOD;
}

using S = struct{
    int val;
    pii pre;
};
S op(S x1, S x2) {
    if(x1.val > x2.val) return x1;
    else return x2;
} 
bool f(S x){
    return 1;
}
S e() {return {-1, {-1,-1}};}

int main() {
    int h, w, n; cin >> h >> w >> n;
    vector<pii> rc(n+2, {0,0});
    map<pii, int> mp;
    rep(i,1,n+1){
        int r, c; cin >> r >> c;
        rc[i] = {r-1, c-1};
    }
    rc[n+1] = {h-1, w-1};
    rep(i,0,n+2) mp[rc[i]] = i;
    sort(rc.begin(), rc.end());
    segtree<S, op, e> seg(w);
    seg.set(0, {0, {0,0}});
    vector<pii> pre(n+2, {-1,-1});
    rep(i,1,n+1){
        auto [r, c] = rc[i];
        auto res = seg.prod(0, c+1);
        seg.set(c, {res.val+1, {r, c}});
        pre[mp[{r,c}]] = res.pre;
    }
    pre[n+1] = seg.all_prod().pre;
    cout << seg.all_prod().val << endl;
    string ans;
    ans.reserve(h+w);
    pii now = {h-1, w-1};
    while(now != make_pair(0,0)){
        auto [r, c] = now;
        int idx = mp[now];
        auto [pr, pc] = pre[idx];
        rep(i,pr,r) ans.push_back('D');
        rep(i,pc,c) ans.push_back('R');
        now = {pr, pc};
    }
    reverse(ans.begin(), ans.end());
    cout << ans << endl;
    return 0;
}