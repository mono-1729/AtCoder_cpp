#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, n) for(int i = a; i < n; i++)
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
const int MOD = 1000000007;
const int mod = 998244353;

// sを始点とする各頂点への距離の最小値を格納した配列を返す
vector<ll> dijk(ll s,vector<vector<pll>> &g){
    priority_queue<pll, vector<pll>, greater<pll>> que;
    vector<ll> dist(100005, (1LL<<60));
    que.push(make_pair(0, s));
    dist[s] = 0;
    while(!que.empty()){
        pll q = que.top(); que.pop();
        ll d = q.first, u = q.second;
        if(dist[u] < d) continue;
        for(auto nq: g[u]){
            ll v = nq.first, cost = nq.second;
            if(dist[v] > d+cost){
                dist[v] = d+cost;
                que.push({dist[v], v});
            }
        }
    }
    return dist;
}

int main(){
    int n, m; cin >> n >> m;
    vector<vector<pll>> g(n+1);
    rep(i, 0, m){
        int u, v, c; cin >> u >> v >> c;
        g[u].push_back({v, c});
        g[v].push_back({u, c});
    }

    vector<ll> d = dijk(1, g);
    rep(i, 1, n+1){
        cout << d[i] << endl;
    }
    
    return 0;
}