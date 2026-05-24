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
    ll n, l, r; cin >> n >> l >> r;
    map<ll,ll> cnt;
    rep(i,0,n){
        ll a; cin >> a;
        cnt[-a]++;
    }
    ll f = 1;
    vector<vector<mint>> dp;
    ll sum = 0;
    for(auto [num, c]: cnt){
        if(f){
            f = 0;
            dp = {{0,0},{0,1}};
            sum += c;
            continue;
        }
        ll m = dp.size();
        vector<vector<mint>> ndp(m+1,vector<mint>(m+1));
        rep(i,0,m)rep(j,0,m){
            ndp[i][j] += dp[i][j]*nCr(sum-2+c,c);
            ndp[i+1][j] += dp[i][j]*nCr(sum-2+c,c-1);
            ndp[i][j+1] += dp[i][j]*nCr(sum-2+c,c-1);
            ndp[i+1][j+1] += dp[i][j]*nCr(sum-2+c,c-2);
        }
        sum += c;
        swap(dp,ndp);
    }
    if(dp.size() > l && dp[l].size() > r) cout << dp[l][r].val() << endl;
    else cout << 0 << endl;
    return 0;
}