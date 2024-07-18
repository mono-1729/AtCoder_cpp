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
    vector<ll> a(n);
    rep(i,0,n) cin >> a[i];
    vector<vector<vector<vector<mint>>>> dp(n+1, vector<vector<vector<mint>>>(n+1, vector<vector<mint>>(n, vector<mint>(n,0))));
    rep(i,0,n)rep(j,i+1,n)dp[j][2][j][i] += 1;
    rep(i,2,n)rep(j,2,n+1)rep(l,0,n)rep(k,l+1,n){
        dp[i][j][k][l] += dp[i-1][j][k][l];
        if(a[i] - a[k] == a[k] - a[l]) dp[i][j][i][k] += dp[i-1][j-1][k][l];
    }
    cout << n << " ";
    rep(j,2,n+1){
        mint ans = 0;
        rep(i,0,n)rep(k,0,n)ans += dp[n-1][j][i][k];
        cout << ans.val() << " ";
    }
    cout << endl;
    return 0;
}