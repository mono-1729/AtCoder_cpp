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

mint dp[51][51][5001];

int main() {
    ll n, k; cin >> n >> k;
    dp[0][0][2500] = 1;
    rep(i,0,n)rep(j,0,n)rep(l,0,5000){
        if(dp[i][j][l] == 0) continue;
        dp[i+1][j][l] += dp[i][j][l];
        if(n-i-1 >= j+1) dp[i+1][j+1][l-i*2] += dp[i][j][l];
        if(j > 0) dp[i+1][j-1][l+i*2] += dp[i][j][l]*j*j;
        if(n-i-1 >= j) dp[i+1][j][l] += dp[i][j][l]*j*2;
    }
    cout << dp[n][0][2500+k].val() << endl;
    return 0;
}