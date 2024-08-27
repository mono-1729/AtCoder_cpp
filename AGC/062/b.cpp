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
ll dp[101][101][101];

int main() {
    ll n, k; cin >> n >> k;
    vector<ll> c(k), p(n), rev(n);
    rrep(i,k-1,0) cin >> c[i];
    rep(i,0,n) cin >> p[i], p[i]--;
    rep(i,0,n) rev[p[i]] = i;
    rep(i,0,n+1)rep(j,0,n+1)rep(l,0,k+1) dp[i][j][l] = INF;
    rep(i,0,n) dp[i][i+1][0] = 0;
    rep(i,0,n+1) dp[i][i][0] = 0;
    rep(i,0,n-1) if(rev[i] < rev[i+1]) dp[i][i+2][0] = 0;
    rep(len,3,n+1)rep(l,0,n+1){
        ll r = l + len;
        if(r > n) break;
        if(dp[l+1][r][0] == 0 && rev[l] < rev[l+1]) dp[l][r][0] = 0;
    }
    rep(op,0,k)rep(l,0,n)rep(r,l,n+1){
        chmin(dp[l][r][op+1], dp[l][r][op]);
        rep(mid,l,r){
            if(dp[l][mid][op] == INF || dp[mid][r][op] == INF) continue;
            chmin(dp[l][r][op+1], dp[l][mid][op]+dp[mid][r][op]+(r-mid)*c[op]);
        }
    }
    if(dp[0][n][k] == INF) dp[0][n][k] = -1;
    cout << dp[0][n][k] << endl;
    return 0;
}