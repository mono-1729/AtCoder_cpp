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
    return x1+x2;
} 
ll border;
bool f(S x) {
    return x < border;
}
S e() {return 0;}


int main() {
    ll n; cin >> n;
    vector<ll> p(n);
    rep(i,0,n) cin >> p[i];
    vector<S> a(n);
    rep(i,0,n) a[i] = 1;
    segtree<S, op, e> seg(a);
    vector<ll> ans(n);
    rrep(i,n-1,0){
        border = p[i];
        ll id = seg.max_right<f>(0);
        ans[id] = i;
        seg.set(id, 0);
    }
    rep(i,0,n) cout << ans[i]+1 << " ";
    cout << endl;
    return 0;
}