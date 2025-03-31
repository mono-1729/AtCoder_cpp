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
#define all(x) (x).begin(), (x).end()
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
    ll n, k; cin >> n >> k;
    vector<vector<ll>> g(n*k);
    rep(i,0,n*k-1){
        ll u, v; cin >> u >> v;
        u--;v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    if(k == 1){
        cout << "Yes" << endl;
        return 0;
    }
    auto no = [&]() -> void {
        cout << "No" << endl;
        exit(0);
    };
    auto dfs = [&](auto dfs, ll v, ll p) -> ll {
        vector<ll> vec;
        for(auto nv: g[v]){
            if(nv == p) continue;
            ll len = dfs(dfs,nv,v);
            if(len)vec.push_back(len);
        }
        if(vec.size() >= 3) no();
        else if(vec.size() == 0) return 1;
        else if(vec.size() == 1){
            if(vec[0] == k-1) return 0;
            else return vec[0]+1;
        }else{
            if(vec[0]+vec[1]+1 == k) return 0;
            else no();
        }
        return -1;
    };
    dfs(dfs, 0, -1);
    cout << "Yes" << endl;
    return 0;
}