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
S e() {return 0;}

S op2(S x1, S x2) {
    return x1+x2;
} 
S e2() {return 0;}


int main() {
    ll n, q; cin >> n >> q;
    vector<ll> h(n);
    vector<pll> hi(n);
    rep(i,0,n) cin >> h[i], hi[i] = {h[i], i};
    segtree<S, op, e> seg(vector<S>(n, 0));
    segtree<S, op2, e2> segl(vector<S>(n+1, 0));
    vector<ll> l(q), r(q);
    vector<vector<ll>> rr(n);
    vector<ll> ans(q);
    rep(i,0,q) cin >> l[i] >> r[i], l[i]--, r[i]--, rr[r[i]].push_back(i);
    vector<ll> pre(n, 0);
    ll now = 0;

    sort(hi.begin(), hi.end(), greater<pll>());

    while(now < n){
        auto [h_, i_] = hi[now];
        ll p_now = now;
        while(now < n && hi[now].first == h_){
            auto [hh, i] = hi[now];
            if(seg.prod(0, i+1) != 0){
                pre[i] = seg.prod(0, i+1);
            }
            now++;
        }
        rep(i,p_now,now){
            seg.set(hi[i].second, hi[i].second);
        }
    }

    rrep(i,n-1,0){
        for(auto q_id : rr[i]){
            ans[q_id] = segl.prod(0, l[q_id]+1);
        }
        segl.set(pre[i], segl.get(pre[i])+1);
    }

    rep(i,0,q){
        cout << ans[i] << endl;
    }
    return 0;
}