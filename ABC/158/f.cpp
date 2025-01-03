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

using S = struct {
    ll num;
    ll idx;
};
S op(S x1, S x2) {
    if(x1.num >= x2.num) return x1;
    else return x2;
} 
S e() {return {-INF,-1};}

int main() {
    ll n; cin >> n;
    vector<pll> xd(n);
    rep(i,0,n){
        ll x, d; cin >> x >> d;
        xd[i] = {x,d};
    }
    sort(xd.begin(), xd.end());
    vector<ll> x(n), d(n);
    rep(i,0,n) x[i] = xd[i].first, d[i] = xd[i].second;
    vector<S> vec(n);
    rep(i,0,n) vec[i] = {x[i]+d[i], i};
    segtree<S,op,e> seg(vec);
    vector<ll> r(n);
    r[n-1] = n;
    rrep(i,n-2,0){
        r[i] = upper_bound(x.begin(), x.end(), x[i]+d[i]-1) - x.begin();
        // cout << r[i] << " " <<  seg.prod(i,r[i]).idx << endl;
        chmax(r[i], r[seg.prod(i,r[i]).idx]);
    }
    vector<mint> dp(n+1,0), sum(n+1);
    dp[n] = 1;
    sum[n] = 1;
    rrep(i,n-1,0){
        // cout << i << " " << r[i] << endl;
        dp[i] += sum[r[i]];
        sum[i] = dp[i] + sum[i+1];
    }
    cout << sum[0].val() << endl;
    return 0;
}