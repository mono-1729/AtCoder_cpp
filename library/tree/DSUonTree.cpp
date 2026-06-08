template<class ADD, class DEL, class QUERY>
struct DSUOnTree {
    ll n;
    vector<vector<ll>> g;
    vector<ll> sz, heavy, tin, tout, euler;
    ADD add;
    DEL del;
    QUERY query;

    DSUOnTree(vector<vector<ll>> g, ADD add, DEL del, QUERY query)
        : n(g.size()), g(g), sz(n), heavy(n, -1), tin(n), tout(n),
          add(add), del(del), query(query) {
        euler.reserve(n);
        dfs_sz(0, -1);
    }

    void dfs_sz(ll v, ll p) {
        sz[v] = 1;
        tin[v] = euler.size();
        euler.push_back(v);

        for (ll to : g[v]) {
            if (to == p) continue;
            dfs_sz(to, v);
            sz[v] += sz[to];
            if (heavy[v] == -1 || sz[to] > sz[heavy[v]]) {
                heavy[v] = to;
            }
        }

        tout[v] = euler.size();
    }

    void run() {
        dfs(0, -1, true);
    }

    void dfs(ll v, ll p, bool keep) {
        for (ll to : g[v]) {
            if (to != p && to != heavy[v]) {
                dfs(to, v, false);
            }
        }

        if (heavy[v] != -1) {
            dfs(heavy[v], v, true);
        }

        for (ll to : g[v]) {
            if (to == p || to == heavy[v]) continue;
            for (ll i = tin[to]; i < tout[to]; i++) {
                add(euler[i]);
            }
        }

        add(v);
        query(v);

        if (!keep) {
            for (ll i = tin[v]; i < tout[v]; i++) {
                del(euler[i]);
            }
        }
    }
};

int main(){
    int n;
    cin >> n;

    vector<int> color(n);
    for (int i = 0; i < n; i++) cin >> color[i];

    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<int> ans(n);

    unordered_map<int, int> cnt;
    int distinct = 0;

    auto add = [&](int v) {
        int c = color[v];
        if (cnt[c] == 0) distinct++;
        cnt[c]++;
    };

    auto del = [&](int v) {
        int c = color[v];
        cnt[c]--;
        if (cnt[c] == 0) distinct--;
    };

    auto query = [&](int v) {
        ans[v] = distinct;
    };

    DSUOnTree dsu(g, add, del, query);
    dsu.run(0);

    for (int i = 0; i < n; i++) {
        cout << ans[i] << '\n';
    }  
}