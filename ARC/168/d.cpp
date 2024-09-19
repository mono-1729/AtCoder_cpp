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

int main() {
    ll n, m; cin >> n >> m;
    vector<vector<ll>> dp(n+1,vector<ll>(n+1, 0));
    vector<vector<vector<ll>>> can(n+1,vector<vector<ll>>(n+1,vector<ll>(n,0)));
    rep(i,0,m){
        ll l, r; cin >> l >> r;
        l--;
        rep(j,l,r) can[l][r][j] = 1;
    }
    rep(len,1,n+1)rep(l,0,n){
        ll r = len+l;
        if(r > n) continue;
        rep(i,l,r){
            can[l][r][i] |= can[l+1][r][i];
            can[l][r][i] |= can[l][r-1][i];
        }
    }
    rep(len,1,n+1)rep(l,0,n){
        ll r = len+l;
        if(r > n) continue;
        chmax(dp[l][r], dp[l+1][r]);
        chmax(dp[l][r], dp[l][r-1]);
        rep(i,l,r){
            if(can[l][r][i]) chmax(dp[l][r], dp[l][i] + 1 + dp[i+1][r]);
        }
    }
    cout << dp[0][n] << endl;
    return 0;
}