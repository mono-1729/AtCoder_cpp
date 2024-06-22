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

int border = 500;

int main() {
    int n, m, q; cin >> n >> m >> q;
    vector<vector<int>> g(n);
    rep(i,0,m){
        int u, v; cin >> u >> v;
        u--;v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<vector<int>> big(n);
    rep(i,0,n){
        if(g[i].size() >= border){
            for(auto x: g[i]) big[x].push_back(i);
        }
    }
    vector<pii> num(n,{-1,-1});
    vector<pii> bigquery(n,{-1,-1});
    rep(i,0,n) num[i] = {i+1, -1};
    rep(_,0,q){
        int x; cin >> x;
        x--;
        for(auto b: big[x]){
            if(bigquery[b].second > num[x].second) num[x] = bigquery[b];
        }
        if(g[x].size() >= border){
            bigquery[x] = {num[x].first, _};
        }else{
            for(auto v:g[x]) num[v] = {num[x].first, _};
        }
    }
    rep(i,0,n){
        for(auto b: big[i]){
            if(bigquery[b].second > num[i].second) num[i] = bigquery[b];
        }
    }
    rep(i,0,n) cout << num[i].first << " ";
    cout << endl;
    return 0;
}