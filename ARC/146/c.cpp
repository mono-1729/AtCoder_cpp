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
    ll n; cin >> n;
    vector<mint> pow2(n+2,1), div(n+2,1);
    rep(i,1,n+2) pow2[i] = pow2[i-1] * 2;
    rep(i,2,n+2) div[i] = div[i-1]/i; 
    vector<vector<mint>> dp(n+2,vector<mint>(2,0));
    dp[0][0] = 1;
    mint ans = 0;
    rep(i,0,n+1){
        dp[i+1][0] += dp[i][0] * (pow2[n]-pow2[i]);
        dp[i+1][1] += dp[i][0] * (i == 0 ? 1 : pow2[i-1]) + dp[i][1] * (pow2[n] - (i == 0 ? 1 : pow2[i-1]));
    }
    rep(i,1,n+2){
        ans += dp[i][0] * div[i];
        ans += dp[i][1] * div[i];
    }
    cout << (ans+1).val() << endl;
    return 0;
}