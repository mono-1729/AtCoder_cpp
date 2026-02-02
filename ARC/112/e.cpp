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

ll maxnum=200005;
vector<ll> fac(maxnum), inv(maxnum), finv(maxnum);
void init_fac(){
    fac[0] = fac[1] = 1;
    inv[1] = 1;
    finv[0] = finv[1] = 1;
    rep(i, 2, maxnum){
        fac[i] = fac[i-1]*i%MOD;
        inv[i] = MOD-MOD/i*inv[MOD%i]%MOD;
        finv[i] = finv[i-1]*inv[i]%MOD;
    }
}
ll nCr(ll n, ll r){
    if(n < 0 or n-r < 0 or r < 0) return 0;
    return fac[n]*(finv[n-r]*finv[r]%MOD)%MOD;
}
ll nHr(ll n, ll r){
    return nCr(n+r-1, r);
}

int main() {
    init_fac();
    ll n, m; cin >> n >> m;
    vector<ll> a(n);
    rep(i,0,n) cin >> a[i], a[i]--;
    vector<vector<ll>> ok(n+1,vector<ll>(n+1,0));
    rep(i,0,n+1) ok[i][i] = 1;
    rep(i,0,n) ok[i][i+1] = 1;
    rep(i,0,n)rep(j,i+2,n+1){
        if(ok[i][j-1] && a[j-2] < a[j-1]) ok[i][j] = 1;
    }
    mint ans = 0;
    vector<ll> cnt(n+1);
    rep(i,0,n)rep(j,i,n+1){
        if(ok[i][j]) cnt[j-i]++;
    }
    vector<vector<mint>> dp(n+1,vector<mint>(m+1,0));
    dp[0][0] = 1;
    rep(i,0,n+1)rep(j,0,m+1){
        if(i > 0) dp[i][j] += dp[i-1][j];
        if(j > 0) dp[i][j] += dp[i][j-1]*i*2;
    }
    rep(i,0,n+1)rep(j,i,n+1){
        if(m < n-(j-i)) continue;
        if(ok[i][j]) ans += dp[n-(j-i)][m-(n-(j-i))]*nCr(n-(j-i),i);
    }

    cout << ans.val() << endl;
    return 0;
}