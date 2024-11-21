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
    unordered_map<ll,vector<pll>> mp;
    vector<vector<ll>> g(n);
    rep(i,0,m){
        ll p, q, r; cin >> p >> q >> r;
        p--;q--;r--;
        mp[r].push_back({p, q});
    }
    ll next = n;
    vector<ll> par(n);
    rep(i,0,n) par[i] = -1;
    for(auto [key, vec]: mp){
        unordered_map<ll,vector<ll>> groups;
        for(auto [p, q]: vec){
            if(par[p] == -1){
                par[p] = p;
                groups[p] = {p};
            }
            if(par[q] == -1){
                par[q] = q;
                groups[q] = {q};
            }
            if(par[p] != par[q]){
                if(groups[par[p]].size() < groups[par[q]].size()) swap(p, q);
                ll pp = par[p], pq = par[q];
                for(auto x: groups[par[q]]){
                    groups[pp].push_back(x);
                    par[x] = pp;
                }
                groups[pq].clear();
            }
        }
        for(auto [key, group] : groups){
            if(group.size() == 0) continue;
            g.push_back({});
            for(auto x: group){
                g[x].push_back(next);
                g[next].push_back(x);
            }
            next++;
        }
        for(auto [p, q]: vec){
            par[p] = -1;
            par[q] = -1;
        }
    }
    deque<ll> que;
    que.push_back(0);
    vector<ll> dist(next,INF);
    dist[0] = 0;
    while(!que.empty()){
        ll v = que.front();que.pop_front();
        for(auto nv: g[v]){
            ll nd = dist[v] + (v >= n);
            if(nd < dist[nv]){
                dist[nv] = nd;
                if(v < n) que.push_front(nv);
                else que.push_back(nv);
            }
        }
    }
    cout << (dist[n-1] == INF ? -1: dist[n-1]) << endl;
    return 0;
}