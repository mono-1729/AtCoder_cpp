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
    vector<vector<pll>> g(n);
    rep(i,0,m){
        ll a,b,c;cin>>a>>b>>c;
        a--;b--;
        g[a].push_back({b,-c});
        g[b].push_back({a,c});
    }

    vector<bool> used(n);
    vector<ll> idx(n);
    vector<vector<ll>> vs;
    vector<ll> xs;
    rep(i,0,n){
        if(used[i]) continue;
        auto dfs = [&](auto dfs, ll v)->void{
            vs.back().push_back(v);
            used[v] = true;
            for(auto [nv, w] : g[v]){
                if(used[nv]) continue;
                idx[nv] = idx[v] + w;
                dfs(dfs, nv);
            }
        };
        vs.push_back({});
        dfs(dfs, i);
        ll mn = 0;
        for(auto v: vs.back()) chmin(mn, idx[v]);
        for(auto v: vs.back()) idx[v] -= mn;
        ll x = 0;
        for(auto v: vs.back()) x |= 1LL<<idx[v];
        xs.push_back(x);
    }

    ll n2 = 1LL<<n;
    m=xs.size();
    vector<ll> ans(n,-1);
    rep(k,0,m){
        vector<bool> dp(n2);
        dp[0] = true;
        ll num = 0;
        rep(i,0,m)if(i!=k){
            rep(s,0,n2){
                if(__popcount(s) != num || !dp[s]) continue;
                ll x = xs[i];
                while(x<n2){
                    if((s&x) == 0) dp[s|x] = true;
                    x<<=1; 
                }
            }
            num+=vs[i].size();
        }
        ll x = xs[k],cnt = 0;
        ll offset = 0,i=0;
        while(x<n2){
            if(dp[(n2-1)^x]){
                offset = i;
                cnt++;
            }
            x<<=1;i++;
        }
        if(cnt == 1){
            for(auto v: vs[k]) ans[v] = idx[v] + offset+1;
        }
    }
    rep(i,0,n) cout<<ans[i]<<" ";
    cout<<endl;
    return 0;
}