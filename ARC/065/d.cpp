#include <bits/stdc++.h>
#include <stdlib.h>
#include <atcoder/all>
using namespace atcoder;
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
#define inr(l, x, r) (l <= x && x < r)
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define all(x) (x).begin(), (x).end()
//constexpr ll MOD = 1000000007;
constexpr ll MOD = 998244353;
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
    vector<ll> l(n), r(n);
    rep(i,0,n) l[i] = i, r[i] = i+1;
    string s; cin >> s;
    rep(i,0,m){
        ll x, y; cin >> x >> y;
        x--;
        rep(j,x,y) chmax(r[j],y);
        rep(j,x,y) chmin(l[j],l[x]);
    }
    vector<ll> sum(n+1,0);
    rep(i,0,n) sum[i+1] = sum[i]+(s[i]-'0');
    // cout << s[n-1] << endl;
    vector<vector<mint>> dp(n+1,vector<mint>(sum[n]+1,0));
    dp[0][0] = 1;
    rep(i,0,n)rep(j,0,sum[n]+1){
        if(dp[i][j] == 0) continue;
        if(sum[r[i]] > j) dp[i+1][j+1] += dp[i][j];
        if(r[i]-sum[r[i]] > i-j) dp[i+1][j] += dp[i][j];
    }

    cout << dp[n][sum[n]].val() << endl;
    return 0;
}