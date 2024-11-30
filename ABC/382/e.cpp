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
    cout << fixed << setprecision(15);
    ll n, x; cin >> n >> x;
    vector<ll> p(n);
    rep(i,0,n) cin >> p[i];
    vector<vector<double>> dp(n+1, vector<double>(x+1, 0));
    dp[0][0] = 1;
    rep(i,0,n){
        rep(j,0,x){
            dp[i+1][j] += dp[i][j] * (1 - p[i]/100.0);
            dp[i+1][j+1] += dp[i][j] * (p[i]/100.0);
        }
        dp[i+1][x] += dp[i][x];
    }
    vector<double> dp2(x+1, 0);
    rrep(i,x-1,0){
        dp2[i] += 1/(1-dp[n][0]);
        rep(j,1,x+1){
            dp2[i] += dp[n][j]*(1/(1-dp[n][0])) * dp2[min(i+j, x)];
        }
    }
    cout << dp2[0] << endl;
    return 0;
}