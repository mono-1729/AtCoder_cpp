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
    ll n; cin >> n;
    vector<vector<ll>> g(n);
    rep(i,0,n-1){
        ll u, v; cin >> u >> v;
        u--;v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<ll> dist(n), pre(n);
    auto bfs = [&](ll s) -> void {
        fill(all(pre),-1);
        fill(all(dist),-1);
        queue<ll> q;
        dist[s] = 0;
        q.push(s);
        while(!q.empty()){
            ll v = q.front(); q.pop();
            for(auto nv: g[v]){
                if(dist[nv] == -1){
                    dist[nv] = dist[v]+1;
                    q.push(nv);
                    pre[nv] = v;
                }
            }
        }
    };
    ll s = 0, t = 0;
    rep(_,0,2){
        swap(s, t);
        bfs(s);
        t = s;
        rep(i,0,n) if(dist[t] < dist[i]) t = i;
    }
    vector<ll> path;
    ll sum = 0;
    while(t != -1){
        path.push_back(g[t].size());
        sum += pre[t] == -1 ? g[t].size(): g[t].size()-1;
        t = pre[t];
    }
    // for(auto x: path) cout << x << " ";
    // cout << endl;
    if(sum != n-1){
        cout << -1 << endl;
        return 0;
    }
    vector<ll> ans1, ans2;
    {
        ans1.push_back(0);
        ll now = 1;
        rep(i,1,path.size()-1){
            ll x = now;
            rep(j,0,path[i]-2){
                ans1.push_back(now+1);
                now++;
            }
            ans1.push_back(x);
            now++;
        }
        ans1.push_back(n-1);
        reverse(all(path));
    }
    {
        ans2.push_back(0);
        ll now = 1;
        rep(i,1,path.size()-1){
            ll x = now;
            rep(j,0,path[i]-2){
                ans2.push_back(now+1);
                now++;
            }
            ans2.push_back(x);
            now++;
        }
        ans2.push_back(n-1);
    }
    if(ans1 > ans2) swap(ans1, ans2);
    for(auto x: ans1) cout << x+1 << " ";
    cout << endl;
    return 0;
}