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
constexpr ll MOD = 1000000007;
// constexpr ll MOD = 998244353;
constexpr int IINF = 1001001001;
constexpr ll INF = 1LL<<60;
template<class t,class u> void chmax(t&a,u b){if(a<b)a=b;}
template<class t,class u> void chmin(t&a,u b){if(b<a)a=b;}

using mint = modint1000000007;

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
    ll n, k; cin >> n >> k;
    vector<vector<ll>> g(n);
    rep(i,0,n-1){
        ll a, b; cin >> a >> b;
        a--;b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    vector<vector<vector<mint>>> dp(n,vector<vector<mint>>(k+1,{0,0}));
    auto dfs = [&](auto&dfs, ll v, ll p) -> void {
        vector<vector<mint>> tdp(k+2,{0,0,0});
        tdp[0][0] = 1;
        for(auto nv: g[v]){
            if(nv == p) continue;
            dfs(dfs,nv,v);
            vector<vector<mint>> ndp(k+2,{0,0,0});
            rep(i,0,k+2)rep(j,0,k+1){
                if(i+j >= k+2) break;
                ndp[i+j][0] += tdp[i][0]*dp[nv][j][0];
                ndp[i+j][1] += tdp[i][0]*dp[nv][j][1] + tdp[i][1]*dp[nv][j][0];
                ndp[i+j][2] += tdp[i][1]*dp[nv][j][1] + tdp[i][2]*dp[nv][j][0];
            }
            swap(tdp,ndp);
        }
        rep(i,0,k+2){
            if(i <= k) dp[v][i][0] += tdp[i][0];
            if(i+1 <= k) dp[v][i+1][1] += tdp[i][0];
            if(i <= k) dp[v][i][0] += tdp[i][1];
            if(i <= k) dp[v][i][1] += tdp[i][1];
            if(i > 0) dp[v][i-1][0] += tdp[i][2];
        }
    };
    dfs(dfs,0,-1);
    cout << (dp[0][k][0]).val() << endl;
    return 0;
}