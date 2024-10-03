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
    vector<vector<tuple<ll,ll,ll>>> g(n+1);
    vector<vector<ll>> w(2,vector<ll>(n, -1));
    rep(i,0,n-1){
        ll u, v, w1, w2; cin >> u >> v >> w1 >> w2;
        u--;v--;
        g[u].push_back({v,w1,w2});
        g[v].push_back({u,w1,w2});
    }
    auto dfs = [&](auto dfs, ll v, ll p) -> void {
        if(w[0][v] == -1) w[0][v] = 0, w[1][v] = 0;
        for(auto [nv, w0, w1]: g[v]){
            if(nv == p) continue;
            w[0][nv] = w[0][v]^w0;
            w[1][nv] = w[1][v]^w1;
            dfs(dfs, nv, v);
        }
    };
    dfs(dfs, 0, -1);
    ll num0 = 0, num1 = 0;
    rep(i,0,n) num0 ^= w[0][i], num1 ^= w[1][i];
    rep(i,0,n) w[0][i] ^= num0, w[1][i] ^= num1;
    sort(w[0].begin(), w[0].end());
    sort(w[1].begin(), w[1].end());
    rep(i,0,n){
        if(w[0][i] != w[1][i]){
            cout << "NO" << endl;
            return 0;
        }
    }
    cout << num0 << " " << num1 << endl;
    cout << "YES" << endl;
    return 0;
}