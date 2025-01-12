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

int main() {
    ll n; cin >> n;
    vector<ll> a(n);
    rep(i,0,n) cin >> a[i];
    ll q; cin >> q;
    vector<ll> tmp(n);
    rep(i,0,n){
        tmp[i] = lower_bound(a.begin(), a.end(), a[i]*2) - a.begin();
        if(tmp[i] == n) tmp[i] = INF;
        tmp[i] -= i;
    }
    segtree<S, op, e> seg(tmp);
    rep(i,0,q){
        ll l, r; cin >> l >> r;
        l--;
        ll ok = 0, ng = (r-l)/2 + 1;
        while(ng - ok > 1){
            ll mid = (ok + ng) / 2;
            if(seg.prod(l, l+mid) <= r-l-mid){
                ok = mid;
            }else{
                ng = mid;
            }
        }
        cout << ok << endl;
    }
    return 0;
}