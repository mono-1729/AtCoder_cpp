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
    ll n; cin >> n;
    vector<vector<ll>> g(n);
    rep(i,0,n-1){
        ll a, b; cin >> a >> b;
        a--;b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    
    ll ans = 0;

    auto dfs = [&](auto dfs, ll v, ll p) -> ll {
        priority_queue<ll,vector<ll>,greater<ll>> pq;
        for(auto nv: g[v]){
            if(nv == p) continue;
            ll x = dfs(dfs, nv, v);
            if(x > 0){
                if(pq.size() < 4 || pq.top() < x) pq.push(x);
                if(pq.size() > 4) pq.pop();
            }
        }
        if(g[v].size() >= 4){
            ll num = 1;
            ll nans = 1;
            while(pq.size()){
                ll x = pq.top();pq.pop();
                if(pq.size() < 3) num += x;
                nans += x;
            }
            if(pq.size()) num += pq.top();
            chmax(ans, nans);
            return num;
        }else{
            return 0;
        }
    };

    dfs(dfs, 0, -1);
    
    if(ans == 0) cout << -1 << endl;
    else cout << ans*3+2 << endl;
    return 0;
}