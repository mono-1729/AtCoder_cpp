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
    ll n, a, b; cin >> n >> a >> b;
    vector<vector<mint>> dp(n,vector<mint>(n,0));
    vector<vector<mint>> dp2(n,vector<mint>(n,0));
    dp[0][0] = dp2[0][0] = 1;
    vector<mint> pow2(n*2+1,1);
    rep(i,1,n*2+1) pow2[i] = pow2[i-1]*2;
    rep(i,0,n)rep(j,0,n){
        if(i < n-1){
            dp[i+1][j] += dp[i][j]*(pow2[n-i-1]+pow2[n-j-1]-2).inv();
            dp2[i+1][j] += dp2[i][j]*(pow2[n-i-1]+pow2[n-j-1]-2).inv();
        }
        if(j < n-1){
            dp2[i][j+1] += dp2[i][j]*(pow2[n-i-1]+pow2[n-j-1]-2).inv();
            if(j == b-1 && i < a) continue;
            dp[i][j+1] += dp[i][j]*(pow2[n-i-1]+pow2[n-j-1]-2).inv();
        }
    }
    cout << (dp[n-1][n-1]*dp2[n-1][n-1].inv()).val() << endl;
    return 0;
}