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

template <typename T>
pair<vector<vector<int>>, int> CartesianTree(vector<T> &a) {
  int N = (int)a.size();
  vector<vector<int>> g(N);
  vector<int> p(N, -1), st;
  st.reserve(N);
  for (int i = 0; i < N; i++) {
    int prv = -1;
    while (!st.empty() && a[i] < a[st.back()]) {
      prv = st.back();
      st.pop_back();
    }
    if (prv != -1) p[prv] = i;
    if (!st.empty()) p[i] = st.back();
    st.push_back(i);
  }
  int root = -1;
  for (int i = 0; i < N; i++) {
    if (p[i] != -1)
      g[p[i]].push_back(i);
    else
      root = i;
  }
  return make_pair(g, root);
}

int main() {
    ll n, m, k; cin >> n >> m >> k;
    vector<string> s(n);
    rep(i,0,n) cin >> s[i];
    vector<ll> vec(m,0);
    vector<vector<ll>> sum(n+1,vector<ll>(m+3,0));
    rep(i,1,n+1)rep(j,0,m+3){
        // a+b <= k/i -1 -j
        // a,b >= 0
        if(k/i-j-1 >= 0) sum[i][j] = (k/i-j)*(k/i-j+1)/2;
    }
    rep(i,0,n)rep(j,0,m+3) sum[i+1][j] += sum[i][j];
    ll ans = 0;
    rep(i,0,n){
        rep(j,0,m){
            if(s[i][j] == '.') vec[j]++;
            else vec[j] = 0;
        }
        auto [g, root] = CartesianTree(vec);
        auto dfs = [&](auto dfs, ll v, ll l, ll r) -> void {
            ans += sum[vec[v]][0];
            ans -= sum[vec[v]][v-l+1];
            ans -= sum[vec[v]][r-v+1];
            ans += sum[vec[v]][r-l+2];
            for(auto nv: g[v]){
                if(nv < v) dfs(dfs,nv,l,v-1);
                else dfs(dfs,nv,v+1,r);
            }
        };
        dfs(dfs,root,0,m-1);
    }
    cout << ans << endl;
    return 0;
}