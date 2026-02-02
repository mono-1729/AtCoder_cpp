#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;

// https://tjkendev.github.io/procon-library/cpp/graph/auxiliary_tree.html

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
            g0[v].push_back(stk[cur-1]);
        }
        // 有向
        // if(cur > 0) {
        //     g0[stk[cur-1]].push_back(v);
        // }
        // g0[v].clear();
        stk[cur++] = v;
        prv = v;
    }
    return stk[0];
}