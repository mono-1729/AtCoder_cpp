#include <bits/stdc++.h>
#include <stdlib.h>
#include <atcoder/all>
using namespace atcoder;
using namespace std;

// https://nyaannyaan.github.io/library/math/two-sat.hpp.html

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

// using mint = modint998244353;

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

namespace TwoSatImpl {
namespace internal {

template <class E>
struct csr {
  vector<ll> start;
  vector<E> elist;
  csr(ll n, const vector<pair<ll, E>>& edges)
      : start(n + 1), elist(edges.size()) {
    for (auto e : edges) {
      start[e.first + 1]++;
    }
    for (ll i = 1; i <= n; i++) {
      start[i] += start[i - 1];
    }
    auto counter = start;
    for (auto e : edges) {
      elist[counter[e.first]++] = e.second;
    }
  }
};

struct scc_graph {
 public:
  scc_graph(ll n) : _n(n) {}

  ll num_vertices() { return _n; }

  void add_edge(ll from, ll to) { edges.push_back({from, {to}}); }

  pair<ll, vector<ll>> scc_ids() {
    auto g = csr<edge>(_n, edges);
    ll now_ord = 0, group_num = 0;
    vector<ll> visited, low(_n), ord(_n, -1), ids(_n);
    visited.reserve(_n);
    auto dfs = [&](auto self, ll v) -> void {
      low[v] = ord[v] = now_ord++;
      visited.push_back(v);
      for (ll i = g.start[v]; i < g.start[v + 1]; i++) {
        auto to = g.elist[i].to;
        if (ord[to] == -1) {
          self(self, to);
          low[v] = min(low[v], low[to]);
        } else {
          low[v] = min(low[v], ord[to]);
        }
      }
      if (low[v] == ord[v]) {
        while (true) {
          ll u = visited.back();
          visited.pop_back();
          ord[u] = _n;
          ids[u] = group_num;
          if (u == v) break;
        }
        group_num++;
      }
    };
    for (ll i = 0; i < _n; i++) {
      if (ord[i] == -1) dfs(dfs, i);
    }
    for (auto& x : ids) {
      x = group_num - 1 - x;
    }
    return {group_num, ids};
  }

  vector<vector<ll>> scc() {
    auto ids = scc_ids();
    ll group_num = ids.first;
    vector<ll> counts(group_num);
    for (auto x : ids.second) counts[x]++;
    vector<vector<ll>> groups(ids.first);
    for (ll i = 0; i < group_num; i++) {
      groups[i].reserve(counts[i]);
    }
    for (ll i = 0; i < _n; i++) {
      groups[ids.second[i]].push_back(i);
    }
    return groups;
  }

  void add_node_size(ll m) { _n += m; }
  ll size() { return _n; }

 private:
  ll _n;
  struct edge {
    ll to;
  };
  vector<pair<ll, edge>> edges;
};

}  // namespace internal

struct TwoSat {
 public:
  TwoSat() : _n(0), built(false), scc(0) {}
  TwoSat(ll n) : _n(n), built(false), scc(2 * n) {}

  ll add_var() {
    scc.add_node_size(2);
    return _n++;
  }

  // (not i) は ~i で渡す
  void add_clause(ll i, ll j) {
    i = max(2 * i, -1 - 2 * i);
    j = max(2 * j, -1 - 2 * j);
    assert(0 <= i && i < 2 * _n);
    assert(0 <= j && j < 2 * _n);
    scc.add_edge(i, j ^ 1);
    scc.add_edge(j, i ^ 1);
  }
  void if_then(ll i, ll j) { add_clause(~i, j); }
  void set_val(ll i) { add_clause(i, i); }

  // (not i) は ~i で渡す
  void at_most_one(const vector<ll>& nodes) {
    if ((ll)nodes.size() <= 1) return;
    ll cur = ~nodes[0];
    for (ll i = 2; i < (ll)nodes.size(); i++) {
      ll nxt = add_var(), n_i = ~nodes[i];
      add_clause(cur, n_i);
      add_clause(cur, nxt);
      add_clause(n_i, nxt);
      cur = ~nxt;
    }
    add_clause(cur, ~nodes[1]);
  }

  bool satisfiable() {
    _answer.resize(_n);
    built = true;
    auto id = scc.scc_ids().second;
    for (ll i = 0; i < _n; i++) {
      if (id[2 * i] == id[2 * i + 1]) {
        _answer.clear();
        return false;
      }
      _answer[i] = id[2 * i] < id[2 * i + 1];
    }
    return true;
  }
  vector<bool> answer() {
    if (!built) satisfiable();
    return _answer;
  }

 private:
  ll _n;
  vector<bool> _answer;
  bool built;
  internal::scc_graph scc;
};

}  // namespace TwoSatImpl

using TwoSatImpl::TwoSat;

// 0ならば素数, 0でないなら最⼩の素因数
// 素因数分解や素因数の数も求めることが可能
ll max_num=1505;
vector<ll> erat(max_num);
vector<ll> prime;
void init_e(){
    rep(i, 2, sqrt((double)max_num-1)){
        if(erat[i] == 0){
            for(ll j = i*i; j <= max_num-1; j += i){
                if(erat[j] == 0) erat[j] = i;
            }
        }
    }
    rep(i,2,max_num){
        if(erat[i] == 0) prime.push_back(i);
    }
}

int main() {
    init_e();
    ll n; cin >> n;
    vector<ll> a(n), b(n);
    rep(i,0,n) cin >> a[i] >> b[i];
    unordered_map<ll,vector<ll>> mp;
    ll cnt = 0;
    rep(i,0,n){
        {
            for(auto p: prime){
                if(p*p > a[i]) break;
                if(a[i]%p == 0) mp[p].push_back(i), cnt++;
                while(a[i]%p == 0) a[i] /= p;
            }
            if(a[i] > 1) mp[a[i]].push_back(i), cnt++;
        }
        {
            for(auto p: prime){
                if(p*p > b[i]) break;
                if(b[i]%p == 0) mp[p].push_back(i+n), cnt++;
                while(b[i]%p == 0) b[i] /= p;
            }
            if(b[i] > 1) mp[b[i]].push_back(i+n), cnt++;
        }
    }
    TwoSat ts(n+cnt);
    rep(i,0,n) ts.add_clause(i,~i);
    ll now = n;
    for(auto [id, vec] : mp){
        rep(i,0,vec.size()-1){
            ts.if_then(now+i, now+i+1);
        }
        rep(i,0,vec.size()){
            ll x = vec[i] >= n ? ~(vec[i]-n) : vec[i];
            ts.if_then(x,now+i);
            if(i > 0) ts.if_then(x,~(now+i-1));
        }
        now += vec.size();
    }
    vector<bool> ans = ts.answer();
    if(ans.empty()) cout << "No" << endl;
    else cout << "Yes" << endl;
    return 0;
}

int main() {
    
    return 0;
}