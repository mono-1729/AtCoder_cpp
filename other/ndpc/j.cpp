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
    ll n, s, t; cin >> n >> s >> t;
    vector<ll> a(n);
    ll suma = 0;
    rep(i,0,n) cin >> a[i], suma += a[i];
    vector<vector<mint>> cnt(n+1,vector<mint>(suma+1,0));
    {
        auto dfs = [&](auto& dfs, ll c, ll s, ll i) -> void {
            if(i == n){
                cnt[c][s]++;
                return;
            }
            dfs(dfs,c,s,i+1);
            dfs(dfs,c+1,s+a[i],i+1);
        };
        dfs(dfs,0,0,0);
    }
    vector<vector<mint>> dp;
    dp = {{1}};
    rep(keta,0,60){
        vector<vector<mint>> ndp(((ll)dp.size()+n+1)/2,vector<mint>(((ll)dp[0].size()+suma+1)/2));
        rep(i,0,(ll)dp.size())rep(j,0,dp[0].size()){
            if(dp[i][j] == 0) continue;
            ll sx = (s>>keta&1), tx = (t>>keta&1);
            for(ll pi = i%2 != sx; pi <= n; pi += 2)for(ll pj = j%2 != tx; pj <= suma; pj += 2){
                ndp[(i+pi)/2][(j+pj)/2] += dp[i][j]*cnt[pi][pj];
            }
        }
        swap(dp,ndp);
    }
    cout << dp[0][0].val() << endl;
    return 0;
}