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
ll border = 0;
bool f(S x){
    return x < border;
}
S e() {return 0;}

int main() {
    ll n; cin >> n;
    vector<ll> a(n), sum(n+1, 0);
    rep(i,0,n) cin >> a[i], sum[i+1] = sum[i] + a[i];
    segtree<S, op, e> seg(a);
    vector<ll> ans(n);
    auto calc = [&](ll l, ll r){
        return sum[r] - sum[l];
    };
    rep(i,0,n){
        ll l = i, r = i+1;
        ll now = a[i];
        while(1){
            ll nl = l, nr = r;
            border = now;
            if(l > 0) chmin(nl, seg.min_left<f>(l));
            if(r < n) chmax(nr, seg.max_right<f>(r));
            if(nl == l && nr == r) break;
            l = nl, r = nr;
            now = calc(l, r);
        }
        ans[i] = now;
    }
    rep(i,0,n) cout << ans[i] << " ";
    return 0;
}