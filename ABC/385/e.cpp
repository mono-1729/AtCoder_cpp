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
    ll n; cin >> n;
    vector<vector<ll>> g(n);
    vector<ll> d(n);
    rep(i,0,n-1){
        ll u, v; cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
        d[u]++;
        d[v]++;
    }

    ll ans = 0;

    auto solve = [&](auto solve, ll v, ll p) -> void {
        vector<ll> degs;
        if(p != -1) degs.push_back(d[p]-1);
        for(auto u : g[v]){
            if(u == p) continue;
            solve(solve, u, v);
            degs.push_back(d[u] - 1);
        }
        sort(degs.begin(), degs.end());
        ll m = degs.size();
        rep(i,0,m){
            chmax(ans, 1 + (m-i) + degs[i]*(m-i));
        }
    };

    solve(solve, 0, -1);

    cout << n - ans << endl;

    return 0;
}