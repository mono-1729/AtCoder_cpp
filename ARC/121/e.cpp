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
    ll n; cin >> n;
    vector<vector<ll>> g(n);
    rep(i,1,n){
        ll p; cin >> p;
        p--;
        g[p].push_back(i);
    }    
    vector<vector<mint>> dp(n);
    auto solve = [&](auto solve, ll v) -> void {
        dp[v] = {1};
        for(auto nv: g[v]){
            solve(solve,nv);
            vector<mint> ndp(dp[v].size()+dp[nv].size()-1,0);
            rep(i,0,dp[v].size())rep(j,0,dp[nv].size()){
                ndp[i+j] += dp[v][i]*dp[nv][j];
            }
            swap(dp[v],ndp);
        }
        ll sz = dp[v].size();
        {
            dp[v].push_back(0);
            rrep(i,sz,1){
                dp[v][i] += dp[v][i-1]*(sz-i);
            }
        }
    };
    solve(solve,0);
    mint ans = 0;
    rep(i,0,n+1){
        if(i%2) ans -= dp[0][i]*fac[n-i];
        else ans += dp[0][i]*fac[n-i];
    }
    cout << ans.val() << endl;
    return 0;
}