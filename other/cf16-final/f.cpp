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
constexpr ll MOD = 1000000007;
// constexpr ll MOD = 998244353;
constexpr int IINF = 1001001001;
constexpr ll INF = 1LL<<60;
template<class t,class u> void chmax(t&a,u b){if(a<b)a=b;}
template<class t,class u> void chmin(t&a,u b){if(b<a)a=b;}

using mint = modint1000000007;

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

mint dp[303][303][303];

int main() {
    ll n, m; cin >> n >> m;
    dp[0][1][0] = 1;
    rep(i,0,m)rep(j,1,n+1)rep(k,0,n+1){
        if(dp[i][j][k] == 0) continue;
        ll l = n-j-k;
        dp[i+1][j+k][0] += dp[i][j][k]*j;
        dp[i+1][j][k] += dp[i][j][k]*k;
        dp[i+1][j][k+1] += dp[i][j][k]*l;
    }
    cout << dp[m][n][0].val() << endl;
    return 0;
}