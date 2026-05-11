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
    rep(i,0,n-1){
        ll a, b; cin >> a >> b;
        a--;b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    unordered_map<ll,mint> dp;
    unordered_map<ll,ll> sz;
    auto dfs = [&](auto& dfs, ll v, ll p) -> pair<mint,ll> {
        if(dp.count(v*n+p)) return {dp[v*n+p],sz[v*n+p]};
        ll c = 1;
        mint num = 1;
        for(auto nv: g[v]){
            if(nv == p) continue;
            auto [numm,cc] = dfs(dfs,nv,v);
            num = num*numm*nCr(c+cc-1,cc);
            c += cc;
        }
        dp[v*n+p] = num;
        sz[v*n+p] = c;
        return {num,c};
    };
    mint ans = 0;
    rep(i,0,n){
        for(auto j: g[i]){
            if(i > j) continue;
            auto [num1,sz1] = dfs(dfs,i,j);
            auto [num2,sz2] = dfs(dfs,j,i);
            ans += num1*num2*nCr(sz1+sz2-2,sz1-1);
        }
    }
    cout << ans.val() << endl;
    return 0;
}