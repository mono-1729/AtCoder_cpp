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

int main() {
    ll n; cin >> n;
    vector<ll> a(n);
    rep(i,0,n) cin >> a[i];
    vector<vector<ll>> g(n);
    rep(i,0,n-1){
        ll u, v; cin >> u >> v;
        u--;v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    mint ans = 0;
    auto solve = [&](auto solve, ll v, ll p) -> unordered_map<ll,pair<mint,mint>> {
        unordered_map<ll,pair<mint,mint>> mp;
        for(auto nv: g[v]){
            if(nv == p) continue;
            auto nmp = solve(solve, nv, v);
            for(auto [key1, val1] : nmp)for(auto[key2,val2] : mp){
                auto [num1, sum1] = val1;
                auto [num2, sum2] = val2;
                ans += (sum1*num2+sum2*num1)*gcd(key1,key2);
            }
            for(auto [key, val] : nmp){
                auto [num, sum] = val;
                ll nkey = gcd(key,a[v]);
                ans += nkey*(sum+num);
                mp[nkey].first += num;
                mp[nkey].second += sum+num;
            }
        }
        mp[a[v]].first++;
        mp[a[v]].second++;
        return mp;
    };
    solve(solve, 0, -1);
    cout << ans.val() << endl;
    return 0;
}