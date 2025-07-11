#include <bits/stdc++.h>
#include <stdlib.h>
#include <atcoder/all>
using namespace atcoder;
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
#define inr(l, x, r) (l <= x && x < r)
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

ll powMod(ll x, ll n, ll mod) {
    if (n == 0) return 1 % mod;
    ll val = powMod(x, n / 2, mod);
    val *= val;
    val %= mod;
    if (n % 2 == 1) val *= x;
    return val % mod;
}

int main() {
    ll n, m, s, t; cin >> n >> m >> s >> t;
    s--;t--;
    vector<vector<ll>> g(n);
    rep(i,0,m){
        ll u, v; cin >> u >> v;
        u--;v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    ll ans = INF;
    vector<ll> dist1(n,INF), dist2(n,INF), pre(n,-1);
    {
        queue<ll> q;
        dist1[s] = 0;
        q.push(s);
        while(!q.empty()){
            ll v = q.front();q.pop();
            for(auto nv: g[v]){
                if(dist1[nv] == INF){
                    pre[nv] = v;
                    dist1[nv] = dist1[v]+1;
                    q.push(nv);
                }
            }
        }
    }
    {
        queue<ll> q;
        dist2[t] = 0;
        q.push(t);
        while(!q.empty()){
            ll v = q.front();q.pop();
            for(auto nv: g[v]){
                if(dist2[nv] == INF){
                    dist2[nv] = dist2[v]+1;
                    q.push(nv);
                }
            }
        }
    }
    {
        ll cnt = 0;
        rep(i,0,n){
            if(g[i].size() >= 3) chmin(ans,dist1[t]*2+min(dist1[i], dist2[i])*4+4);
            if(i == s || i == t) continue;
            if(dist1[i]+dist2[i] == dist1[t]){
                cnt++;
                if(g[i].size() >= 3) chmin(ans, dist1[t]*2+2);
            }
            for(auto x: g[i]){
                if(dist1[i]+dist2[x] == dist1[t] || dist1[x]+dist2[i] == dist1[t]) chmin(ans, dist1[t]*2+1);
            }
        }
        if(cnt > dist1[t]-1) ans = dist1[t]*2;
    }
    {
        fill(all(dist2),INF);
        queue<ll> q;
        dist2[t] = 0;
        q.push(t);
        while(!q.empty()){
            ll v = q.front();q.pop();
            for(auto nv: g[v]){
                if((dist2[v]+dist1[nv]+1 == dist1[t])&&(pre[v] == nv || pre[nv] == v)) continue;
                if(dist2[nv] == INF){
                    dist2[nv] = dist2[v]+1;
                    q.push(nv);
                }
            }
        }
        // cout << dist1[t] << " " << dist2[t] << endl;
        chmin(ans,dist1[t]+dist2[s]);
    }
    cout << (ans == INF ? -1: ans) << endl;
    return 0;
}