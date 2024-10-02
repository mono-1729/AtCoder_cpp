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
    vector<ll> c(n);
    rep(i,0,n) cin >> c[i], c[i]--;
    vector<vector<ll>> g(n);
    rep(i,0,n-1){
        ll a, b; cin >> a >> b;
        a--;b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    vector<ll> ans(n,0);
    vector<ll> size(n,n);
    auto solve = [&](auto solve, ll v, ll p) -> unordered_map<ll,ll> {
        unordered_map<ll,ll> res;
        res[n+1]++;
        for(auto nv: g[v]){
            if(nv == p) continue;
            unordered_map<ll,ll> mp = solve(solve, nv, v);
            ans[c[v]] -= (mp[n+1]-mp[c[v]]) * (mp[n+1]-mp[c[v]]-1) / 2;
            if(res.size() < mp.size()) swap(res, mp);
            for(auto [key, val]: mp) res[key] += val;
        }
        ans[c[v]] += (res[n+1]-res[c[v]]) * (size[c[v]]-res[n+1]+res[c[v]]+1);
        ans[c[v]] += (res[n+1]-res[c[v]]-1) * (res[n+1]-res[c[v]]-2)/2;
        size[c[v]] -= (res[n+1]-res[c[v]]);
        res[c[v]] = res[n+1];
        return res;
    };
    solve(solve, 0, -1);
    for(auto x: ans) cout << x << endl;
    return 0;
}