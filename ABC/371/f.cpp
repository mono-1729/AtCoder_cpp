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

//区間変更・区間和取得
struct S{
    long long value;
    ll size;
    ll maxi;
    ll mini;
};
using F = long long;
const F ID = 8e18;

S op(S a, S b){ return {a.value+b.value, a.size+b.size, max(a.maxi, b.maxi), min(a.mini,b.mini)}; }
S e(){ return {0, 0, -INF,INF}; }
S mapping(F f, S x){
    if(f != ID){
        x.value = f*x.size;
        x.maxi = f;
        x.mini = f;
    }
    return x;
}
F composition(F f, F g){ return (f == ID ? g : f); }
F id(){ return ID; }
// ll n;
// vector<S> v(n, {0, 1});
// LazySegmentTree<S, op, e, F, mapping, composition, id> seg(v);
ll border;

bool f1(S x){
    return (x.maxi <= border || x.mini == INF);
}

bool f2(S x){
    return (x.mini >= border || x.maxi == -INF);
}

int main() {
    ll n; cin >> n;
    vector<ll> x(n);
    rep(i,0,n) cin >> x[i], x[i] -= i;
    ll ans = 0;
    vector<S> vec(n);
    rep(i,0,n) vec[i] = {x[i],1,x[i],x[i]};
    lazy_segtree<S,op,e,F,mapping,composition,id> seg(vec);
    ll q; cin >> q;
    while(q--){
        ll t, g; cin >> t >> g;
        t--; g -= t;
        ll now = seg.get(t).maxi;
        border = g;
        if(g < now){
            t++;
            ll l = seg.min_left<f2>(t);
            auto res = seg.prod(l,t);
            ans += res.value - g * res.size;
            seg.apply(l,t,g);
        }else if(now < g){
            ll r = seg.max_right<f1>(t);
            auto res = seg.prod(t,r);
            ans += g * res.size - res.value;
            seg.apply(t,r,g);
        }
    }
    cout << ans << endl;
    return 0;
}