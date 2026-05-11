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
    string s; cin >> s;
    ll n = s.size();
    vector<vector<ll>> dp(n,vector<ll>(n+1,0));
    rrep(l,n-3,0)rep(r,l+1,n+1){
        rep(mid,l+1,r){
            if(s[l] == 'i' && s[mid] == 'w' && s[r-1] == 'i' && (dp[l+1][mid]+dp[mid][r-1])*3 == r-l-3) chmax(dp[l][r], dp[l+1][mid]+dp[mid][r-1]+1);
            chmax(dp[l][r], dp[l][mid]+dp[mid][r]);
        }
    }
    cout << dp[0][n] << endl;
    return 0;
}