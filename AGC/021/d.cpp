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
    string s; cin >> s;
    ll n = s.size();
    ll k; cin >> k;
    vector<vector<vector<ll>>> dp(n,vector<vector<ll>>(n+1,vector<ll>(k+1,0)));
    rep(i,0,n) dp[i][i+1][0] = 1;
    rep(i,2,n+1)rep(j,0,n)rep(num,0,k+1){
        int l = j, r = i+j;
        if(r > n) continue;
        chmax(dp[l][r][num], dp[l+1][r][num]);
        chmax(dp[l][r][num], dp[l][r-1][num]);
        if(s[l] == s[r-1]) chmax(dp[l][r][num], dp[l+1][r-1][num]+2);
        else chmax(dp[l][r][num], dp[l+1][r-1][num]);
        if(num > 0) chmax(dp[l][r][num], dp[l+1][r-1][num-1]+2);
    }
    ll ans = 0;
    rep(i,0,k+1)chmax(ans,dp[0][n][i]);
    cout << ans << endl;
    return 0;
}