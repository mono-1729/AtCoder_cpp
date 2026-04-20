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

using mint = modint;

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
    mint::set_mod(m);
    vector<vector<mint>> dp(3*n+1,vector<mint>(n+1));
    dp[0][0] = 1;
    rep(i,1,n*3+1){
        rep(j,0,n+1){
            dp[i][j] += dp[i-1][j];
            if(i >= 2 && j) dp[i][j] += dp[i-2][j-1]*(i-1);
            if(i >= 3 && j) dp[i][j] += dp[i-3][j-1]*(i-1)*(i-2);
        }
    }
    mint ans = 0;
    for(auto x: dp[3*n]) ans += x;
    cout << ans.val() << endl;
    return 0;
}