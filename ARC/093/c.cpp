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
constexpr ll MOD = 1000000007;
//constexpr ll MOD = 998244353;
constexpr int IINF = 1001001001;
constexpr ll INF = 1LL<<60;
template<class t,class u> void chmax(t&a,u b){if(a<b)a=b;}
template<class t,class u> void chmin(t&a,u b){if(b<a)a=b;}

using mint = modint1000000007;

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

class UnionFind {
    vector<ll> parent, maxi, mini;
    inline ll root(ll n){
        return (parent[n] < 0? n:parent[n] = root(parent[n]));
    }
public:
    UnionFind(ll n_ = 1): parent(n_, -1), maxi(n_), mini(n_){
        iota(maxi.begin(), maxi.end(), 0);
        iota(mini.begin(), mini.end(), 0);
    }

    inline bool same(ll x, ll y){
        return root(x) == root(y);
    }

    inline void unite(ll x, ll y){
        ll rx = root(x);
        ll ry = root(y);
        if(rx == ry) return;
        if(parent[rx] > parent[ry]) swap(rx, ry);
        parent[rx] += parent[ry];
        parent[ry] = rx;
        maxi[rx] = std::max(maxi[rx],maxi[ry]);
        mini[rx] = std::min(mini[rx],mini[ry]);
    }

    inline ll min(ll x){
        return mini[root(x)];
    }

    inline ll max(ll x){
        return maxi[root(x)];
    }

    inline ll size(ll x){
        return (-parent[root(x)]);
    }

    inline ll operator[](ll x){
        return root(x);
    }

    inline void print(){
        rep(i, 0, (ll)parent.size()) cout << root(i) << " ";
        cout << endl;
    }

    void clear(){
        rep(i, 0, (ll)parent.size()){
            parent[i] = -1;
        }
        iota(maxi.begin(), maxi.end(), 0);
        iota(mini.begin(), mini.end(), 0);
    }
};

// 辺の定義
struct Edge {
    long long u;
    long long v;
    long long cost;
};
bool comp_e(const Edge &e1, const Edge &e2) { return e1.cost < e2.cost; } // 辺を直接比較するための関数

/* Kruskal :クラスカル法で minimum spanning tree を求める構造体
    入力: 辺のvector, 頂点数V
    最小全域木の重みの総和: sum
    計算量: O(|E|log|V|)
*/
struct Kruskal {
    UnionFind uft;
    long long sum;  // 最小全域木の重みの総和
    vector<Edge> edges;
    vector<ll> use;
    int V;
    Kruskal(const vector<Edge> &edges_, int V_) : edges(edges_), V(V_) { init(); }
    void init() {
        sort(edges.begin(), edges.end(), comp_e); // 辺の重みでソート
        uft = UnionFind(V);
        use = vector<ll>(edges.size(),0);
        sum = 0;
        ll idx = 0;
        for (auto e : edges) {
            if (!uft.same(e.u, e.v)) { // 閉路にならなければ加える
                use[idx] = 1;
                uft.unite(e.u, e.v);
                sum += e.cost;
            }
            idx++;
        }
    }
};

int main() {
    ll n, m; cin >> n >> m;
    ll x; cin >> x;
    vector<vector<pll>> g(n);
    vector<Edge> edges(m);
    rep(i,0,m){
        ll u, v, w; cin >> u >> v >> w;
        u--;v--;
        g[u].push_back({v,w});
        g[v].push_back({u,w});
        edges[i] = {u,v,w};
    }
    vector<vector<ll>> maxe(n,vector<ll>(n,INF));
    rep(s,0,n){
        // sを始点とする各頂点への距離の最小値を格納した配列を返す
        priority_queue<pll, vector<pll>, greater<pll>> que;
        que.push(make_pair(0, s));
        maxe[s][s] = 0;
        while(!que.empty()){
            pll q = que.top(); que.pop();
            ll d = q.first, u = q.second;
            if(maxe[s][u] < d) continue;
            for(auto nq: g[u]){
                ll v = nq.first, cost = nq.second;
                if(maxe[s][v] > max(d,cost)){
                    maxe[s][v] = max(d,cost);
                    que.push({maxe[s][v], v});
                }
            }
        }
    }
    
    Kruskal kr(edges, n);

    mint ans = 0;
    if(x == kr.sum) ans += (mint)powMod(2,m)-powMod(2,m-n+1)*2;
    ll cnt = n-1;
    rep(i,0,m){
        Edge e = kr.edges[i];
        if(kr.use[i]) continue;
        if(kr.sum+e.cost-maxe[e.u][e.v] < x) cnt++;
    }
    rep(i,0,m){
        Edge e = kr.edges[i];
        if(kr.use[i]) continue;
        if(kr.sum+e.cost-maxe[e.u][e.v] == x){
            ans += powMod(2,m-cnt);
            cnt++;
        }
    }
    cout << ans.val() << endl;
    return 0;
}