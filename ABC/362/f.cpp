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
    int n; cin >> n;
    vector<vector<ll>> g(n);
    rep(i,0,n-1){
        ll u, v; cin >> u >> v;
        u--;v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    ll idx = -1;
    auto dfs1 = [&](auto dfs1, ll v, ll p) -> ll {
        ll res = 1;
        for(auto nv : g[v]){
            if(nv == p) continue;
            res += dfs1(dfs1, nv, v);
        }
        if(idx == -1 && res > n/2) idx = v;
        return res;
    };
    vector<ll> ans;

    auto dfs2 = [&](auto dfs2, ll v, ll p) -> void {
        for(auto nv : g[v]){
            if(nv == p) continue;
            dfs2(dfs2, nv, v);
        }
        ans.push_back(v+1);
    };
    dfs1(dfs1, 0, -1);
    dfs2(dfs2, idx, -1);
    if(n%2 == 1) ans.pop_back();
    rep(i,0,n/2) cout << ans[i] << " " << ans[n/2+i] << endl;
    return 0;
}