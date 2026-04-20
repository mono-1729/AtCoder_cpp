#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <stdlib.h>
#include <atcoder/all>
using namespace atcoder;
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
#define inr(l, x, r) (l <= x && x < r)
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define all(x) (x).begin(), (x).end()
//constexpr ll MOD = 1000000007;
constexpr ll MOD = 998244353;
constexpr int IINF = 1001001001;
constexpr ll INF = 1LL<<60;
template<class t,class u> void chmax(t&a,u b){if(a<b)a=b;}
template<class t,class u> void chmin(t&a,u b){if(b<a)a=b;}

using mint = modint998244353;

ll gcd(ll a, ll b){
    if(b == 0) return a;
    if(a%b == 0){
      return b;
    }else{
      return gcd(b, a%b);
    }
}

ll lcm(ll a, ll b){
    return a*b / gcd(a, b);
}

ll powMod(ll x, ll n, ll mod) {
    if (n == 0) return 1 % mod;
    ll val = powMod(x, n / 2, mod);
    val *= val;
    val %= mod;
    if (n % 2 == 1) val *= x;
    return val % mod;
}

int main() {
    ll n; cin >> n;
    vector<tuple<ll,ll,ll>> wsv(n);
    rep(i,0,n){
        ll w, s, v; cin >> w >> s >> v;
        wsv[i] = {w,s,v};
    }
    sort(all(wsv), [](const auto& a, const auto& b){
        auto [a1,a2,a3] = a;
        auto [b1,b2,b3] = b;
        return a1+a2 < b1+b2;
    });
    vector<ll> dp(10002,0);
    rep(i,0,n){
        auto [w,s,v] = wsv[i];
        vector<ll> ndp = dp;
        rep(j,0,s+1){
            chmax(ndp[min(10001LL,w+j)],dp[j]+v);
        }
        swap(dp,ndp);
    }
    ll ans = 0;
    rep(i,0,10002) chmax(ans,dp[i]);
    cout << ans << endl;
    return 0;
}