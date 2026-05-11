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
    ll n, m; cin >> n >> m;
    vector<ll> a(n), b(m);
    rep(i,0,n) cin >> a[i];
    rep(i,0,m) cin >> b[i];
    vector<vector<ll>> dp(n+1,vector<ll>(m+1,-INF));
    auto dfs = [&](auto& dfs, ll i, ll j) -> ll {
        if(dp[i][j] != -INF) return dp[i][j];
        if(i == n && j == m) return dp[i][j] = 0;
        if((i+j)%2 == 0){
            ll ma = 0;
            if(i < n) chmax(ma,dfs(dfs,i+1,j)+a[i]);
            if(j < m) chmax(ma,dfs(dfs,i,j+1)+b[j]);
            return dp[i][j] = ma;
        }else{
            ll mi = INF;
            if(i < n) chmin(mi,dfs(dfs,i+1,j));
            if(j < m) chmin(mi,dfs(dfs,i,j+1));
            return dp[i][j] = mi;
        }
    };
    cout << dfs(dfs,0,0) << endl;
    return 0;
}