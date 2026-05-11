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
    vector<vector<ll>> f(n,vector<ll>(n));
    rep(i,0,n)rep(j,0,n) cin >> f[i][j];
    vector<ll> dp = {0};
    rep(i,1,n){
        vector<ll> ndp(i+1,-INF);
        vector<ll> fsum(i+1,0);
        rrep(j,i-1,0) fsum[j] = fsum[j+1]+f[j][i]*2;
        rep(j,1,i) chmax(dp[j], dp[j-1]);
        rep(j,0,i) ndp[j] = dp[j]+fsum[j];
        ndp[i] = dp.back();
        swap(dp,ndp);
    }
    ll ans = 0;
    for(auto x: dp) chmax(ans,x);
    cout << ans << endl;
    return 0;
}