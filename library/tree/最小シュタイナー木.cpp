#include <bits/stdc++.h>
#include <unordered_map>
#include <stdlib.h>
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

template<typename T> class SteinerTree {
private:
    struct edge {
        ll to;
        T cost;
    };
    ll V;
    vector<vector<edge> > G;
    vector<vector<T> > dp;
    const T inf = numeric_limits<T>::max() / 10;
    using pti = pair<T, ll>;
 
public:
    SteinerTree(ll node_size) : V(node_size), G(V){}
    void add_edge(ll u, ll v, T cost){
        G[u].push_back((edge){v, cost}), G[v].push_back((edge){u, cost});
    }
    T solve(vector<ll>& terminal){
        ll t = (ll)terminal.size();
        if(t == 0) return (T)0;
        dp.resize((1 << t), vector<T>(V, inf));
        for(ll i = 0; i < t; i++){
            dp[(1 << i)][terminal[i]] = 0;
        }
        for(ll i = 1; i < (1 << t); i++){
            for(ll j = 0; j < V; j++){
                for(ll k = i; k > 0; k = (k - 1) & i){
                    dp[i][j] = min(dp[i][j], dp[k][j] + dp[i ^ k][j]);
                }
            }
            if(i == (1 << t) - 1) break;
            priority_queue<pti, vector<pti>, greater<pti> > que;
            for(ll j = 0; j < V; j++){
                que.push(make_pair(dp[i][j], j));
            }
            while(!que.empty()){
                pti p = que.top();
                que.pop();
                ll v = p.second;
                if(dp[i][v] < p.first) continue;
                for(auto& e : G[v]){
                    if(dp[i][e.to] > dp[i][v] + e.cost){
                        dp[i][e.to] = dp[i][v] + e.cost;
                        que.push(make_pair(dp[i][e.to], e.to));
                    }
                }
            }
        }
        return dp[(1 << t) - 1][terminal[0]];
    }
};

int main() {
    return 0;
}