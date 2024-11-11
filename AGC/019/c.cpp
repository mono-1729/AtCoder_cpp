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

using S = long long;
S op(S x1, S x2) {
    return max(x1, x2);
} 
bool f(S x){
    return 1;
}
S e() {return 0;}

ll MAX_XY = 1e8;

int main() {
    cout << fixed << setprecision(15);
    ll sx, sy, gx, gy; cin >> sx >> sy >> gx >> gy;
    ll n; cin >> n;
    vector<ll> x(n), y(n);
    rep(i,0,n) cin >> x[i] >> y[i];
    if(sx > gx){
        sx = MAX_XY - sx;
        gx = MAX_XY - gx;
        rep(i,0,n) x[i] = MAX_XY - x[i];
    }
    if(sy > gy){
        sy = MAX_XY - sy;
        gy = MAX_XY - gy;
        rep(i,0,n) y[i] = MAX_XY - y[i];
    }
    set<ll> yst;
    unordered_map<ll,ll> mp;
    vector<pll> f_pos;
    rep(i,0,n){
        if(x[i] < sx || gx < x[i] || y[i] < sy || gy < y[i]) continue;
        yst.insert(y[i]);
        f_pos.push_back({x[i], y[i]});
    }
    ll idx = 0;
    for(auto a: yst) mp[a] = idx++;
    segtree<S,op,e> seg(idx);
    sort(f_pos.begin(), f_pos.end());
    for(auto [a, b]: f_pos){
        seg.set(mp[b], seg.prod(0,mp[b]+1)+1);
    }
    double ans = ((gx-sx) + (gy-sy))*100;
    ans -= (20-5*M_PI) * seg.prod(0, idx);
    if(seg.prod(0, idx) == min(gx-sx+1, gy-sy+1)){
        ans += (20-M_PI*5)+(M_PI*10-20);
    }
    cout << ans << endl;
    return 0;
}