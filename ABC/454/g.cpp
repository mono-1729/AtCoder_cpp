#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <stdlib.h>
#include <atcoder/all>
using namespace atcoder;
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
#define inr(l, x, r) (l <= x && x < r)
#define ll long long
#define ld long double
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
    if(b == 0) return a;
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

    void run(ll par) {
        dfs(par, -1, true);
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

int main() {
    ll n, seed, m, f; cin >> n >> seed >> m >> f;
    vector<ll> q(m), d(m), c(n);
    rep(i,1,m) cin >> q[i], q[i]--;
    rep(i,0,m) cin >> d[i], d[i]--;
    vector<vector<ll>> g(n);
    {
        ll state = seed;
        ll b = 1LL<<31;
        rep(i,1,n){
            if(i < m) g[q[i]].push_back(i);
            else{
                g[state%i].push_back(i);
                state = (state * 1103515245 + 12345) % b;
            }
        }
        rep(i,0,n){
            if(i < m) c[i] = d[i];
            else{
                c[i] = state%f;
                state = (state * 1103515245 + 12345) % b;
            }
        }
    }
    vector<ll> cnt(n), cnt2(n+1);
    cnt2[0] = n;
    ll ma = 0;
    vector<ll> a1(n), a2(n);

    auto add = [&](ll v) {
        cnt2[cnt[c[v]]]--;
        cnt[c[v]]++;
        cnt2[cnt[c[v]]]++;
        if(ma < cnt[c[v]]) ma++;
    };

    auto del = [&](ll v) {
        cnt2[cnt[c[v]]]--;
        cnt[c[v]]--;
        cnt2[cnt[c[v]]]++;
        if(ma == cnt[c[v]]+1 && cnt2[ma] == 0) ma--;
    };

    auto query = [&](ll v) {
        a1[v] = ma;
        a2[v] = cnt2[ma];
    };

    DSUOnTree dsu(g, add, del, query);
    dsu.run(0);

    mint ans = 0;
    rep(i,1,n+1) ans += (a1[i-1]^i) * (a2[i-1]^i);
    cout << ans.val() << endl;

    return 0;
}