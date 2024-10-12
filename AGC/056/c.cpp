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
    ll n, m; cin >> n >> m;
    vector<ll> l(m), r(m);
    vector<vector<pll>> g(n+1);
    rep(i,0,n){
        g[i].push_back({i+1, 1});
        g[i+1].push_back({i, 1});
    }
    rep(i, 0, m){
        cin >> l[i] >> r[i];
        l[i]--; r[i]--;
        g[l[i]].push_back({r[i]+1,0});
        g[r[i]+1].push_back({l[i],0});
    }
    vector<ll> dist(n+1, INF);
    dist[0] = 0;
    deque<ll> que;
    que.push_back(0);
    while(!que.empty()){
        ll v = que.front(); que.pop_front();
        for(auto [nv, c]: g[v]){
            if(dist[nv] > dist[v]+c){
                dist[nv] = dist[v] + c;
                if(c) que.push_back(nv);
                else que.push_front(nv);
            }
        }
    }
    rep(i,0,n){
        cout << (dist[i] < dist[i+1] ? '0' : '1');
    }
    cout << endl;
}