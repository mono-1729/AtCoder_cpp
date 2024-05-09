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
    ll n,m;cin>>n>>m;
    vector<ll> ans(m, 0);
    vector<vector<tuple<ll,ll,ll>>> g(n);
    vector<ll> a(m), b(m);
    rep(i,0,m)cin>>a[i];
    rep(i,0,m)cin>>b[i];
    rep(i,0,m){
        g[a[i]-1].push_back({b[i]-1,i,0});
        g[b[i]-1].push_back({a[i]-1,i,1});
    }
    vector<ll> check(n, 0);
    auto dfs = [&](auto& dfs, ll v, ll p,ll e)->void{
        check[v] = 1;
        for(auto [nv, i, f]:g[v]){
            if(i==e) continue;
            if(check[nv] == 0){
                ans[i] = f;
                dfs(dfs, nv, v, i);
            }else ans[i] = 1-f;
        }
    };
    rep(i,0,n){
        if(check[i] == 0) dfs(dfs, i, -1, -1);
    }
    rep(i,0,m)cout<<ans[i];
    cout<<endl;
    return 0;
}