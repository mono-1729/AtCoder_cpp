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

vector<int> fs, ls, depth, lg, stk;

vector<vector<int>> st;
int cur;
vector<vector<int>> graph;

void ett_dfs(int v, int p, int d){
    st[0][fs[v] = cur++] = v;
    depth[v] = d;
    for(int w : graph[v]){
        if(w == p) continue;
        ett_dfs(w,v,d+1);
        st[0][cur++] = v;
    }
    ls[v] = cur-1;
}

void AuxiliaryTree(vector<vector<int>> gh){
    graph = gh;
    int n = graph.size();
    fs.resize(n); ls.resize(n); depth.resize(n); lg.resize(3*n); stk.resize(2*n);
    st.resize(20);
    for(int i = 0; i < 20; i++) st[i].resize(3*n);
    cur = 0;
    ett_dfs(0,-1,0);
    lg[0] = lg[1] = 0;
    for(int i = 2; i <= cur; ++i) lg[i] = lg[i >> 1] + 1;

    for(int i = 0, b = 1; i < lg[cur]; ++i, b <<= 1) {
        for(int j = 0; j < (cur - (b<<1) + 1); ++j) {
            st[i+1][j] = (depth[st[i][j]] <= depth[st[i][j+b]] ? st[i][j] : st[i][j+b]);
        }
    }
}

bool cmp_at(int x, int y) {
    return fs[x] < fs[y];
}

inline int lca(int u, int v) {
    int x = fs[u], y = fs[v];
    if(x > y) swap(x, y);
    int l = lg[y - x + 1];
    return (depth[st[l][x]] <= depth[st[l][y - (1 << l) + 1]] ? st[l][x] : st[l][y - (1 << l) + 1]);
}

// 頂点vsを含むAuxiliary Treeを構築する
// 結果をg0に入れる
// 根頂点を返す
inline int auxiliary_tree(vector<int> &vs, vector<vector<int>> &g0) {
    sort(vs.begin(), vs.end(), cmp_at);
    int k = vs.size();
    for(int i=0; i<k-1; ++i) {
        vs.push_back(lca(vs[i], vs[i+1]));
    }
    sort(vs.begin(), vs.end(), cmp_at);
    int prv = -1;
    int cur = 0;
    for(int i=0; i<vs.size(); ++i) {
        int v = vs[i];
        if(prv == v) continue;
        while(cur > 0 && ls[stk[cur-1]] < fs[v]) --cur;
        if(cur > 0) {
            g0[stk[cur-1]].push_back(v);
        }
        g0[v].clear();
        stk[cur++] = v;
        prv = v;
    }
    return stk[0];
}

int main() {
    int n; cin >> n;
    vector<int> a(n);
    rep(i,0,n) cin >> a[i], a[i]--;
    vector<vector<int>> g(n);
    rep(i,0,n-1){
        int u, v; cin >> u >> v;
        u--;v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    AuxiliaryTree(g);
    vector<vector<int>> g0(n);
    vector<int> use;
    vector<vector<int>> pos(n);
    rep(i,0,n) pos[a[i]].push_back(i);
    mint ans = 0;
    auto solve = [&](auto solve, int v, int p, int col) -> mint {
        use.push_back(v);
        if(a[v] == col){
            mint res = 1;
            for(auto nv: g0[v]){
                if(nv == p) continue;
                res *= solve(solve, nv, v, col)+1;
            }
            ans += res;
            return res;
        }else{
            mint res = 1;
            mint cnt = 0;
            for(auto nv: g0[v]){
                if(nv == p) continue;
                mint x = solve(solve, nv, v, col);
                res *= x+1;
                cnt += x;
            }
            ans += res - cnt - 1;
            return res - 1;
        }
    };
    rep(i,0,n){
        if(pos[i].size() == 0) continue;
        int par = auxiliary_tree(pos[i], g0);
        solve(solve, par, -1, i);
        for(auto x : use) g0[x].clear();
        use.clear();
    }
    cout << ans.val() << endl;
    return 0;
}