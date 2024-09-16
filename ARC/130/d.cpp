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

ll maxnum=3005;
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
    auto solve = [&](auto solve, ll v, ll p, ll flg) -> vector<mint> {
        vector<mint> dp = {1};
        for(auto nv: g[v]){
            if(nv == p) continue;
            vector<mint> cdp = solve(solve, nv, v, 1-flg);
            ll m1 = dp.size(), m2 = cdp.size();
            rrep(i,m2-1,1) cdp[i-1] += cdp[i];
            cdp.push_back(0);
            vector<mint> ndp(m1+m2,0);
            rep(i,0,m1)rep(j,0,m2+1){
                if(flg) ndp[i+j] += dp[i] * cdp[j] * nCr(i+j,i) * nCr(m1+m2-i-j-1,m1-i-1);
                else ndp[i+j] += dp[i] * (cdp[0] - cdp[j]) * nCr(i+j,i) * nCr(m1+m2-i-j-1,m1-i-1);
            }
            swap(dp,ndp);
        }
        return dp;
    };
    mint ans = 0;
    for(auto x :solve(solve, 0, -1, 0)) ans += x;
    for(auto x :solve(solve, 0, -1, 1)) ans += x;
    cout << ans.val() << endl;
    return 0;
}