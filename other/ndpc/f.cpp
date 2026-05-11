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
    ll t; cin >> t;
    while(t--){
        ll n; cin >> n;
        vector<ll> p(n), a(n);
        rep(i,0,n) cin >> p[i], p[i]--;
        rep(i,0,n) cin >> a[i];
        vector<ll> ans(n+1,INF);
        ans[0] = 0;
        auto [g,root] = CartesianTree(p);
        auto dfs = [&](auto& dfs, ll v) -> vector<ll> {
            if(g[v].size() == 0){
                chmin(ans[1],a[v]);
                return {0,a[v]};
            }else if(g[v].size() == 1){
                vector<ll> vec = dfs(dfs,g[v][0]);
                ll m = vec.size();
                vector<ll> nv(m+1,INF);
                rep(i,0,m){
                    chmin(nv[i],vec[i]);
                    chmin(nv[i+1],vec[i]+a[v]);
                    chmin(ans[i+1],nv[i+1]);
                }
                return nv;
            }else{
                vector<ll> vec1 = dfs(dfs,g[v][0]), vec2 = dfs(dfs,g[v][1]);
                ll m = vec1.size(), mm = vec2.size();
                vector<ll> nv(m+mm,INF);
                rep(i,0,m) chmin(nv[i],vec1[i]);
                rep(i,0,mm) chmin(nv[i],vec2[i]);
                rep(i,0,m)rep(j,0,mm){
                    chmin(nv[i+j+1],vec1[i]+vec2[j]+a[v]);
                }
                rep(sum,0,m+mm){
                    // cout << sum << " " << ans.size() << " " << nv.size() << endl;
                    chmin(ans[sum],nv[sum]);
                }
                return nv;
            }
        };
        dfs(dfs,root);
        rep(i,1,n+1) cout << ans[i] << " ";
        cout << endl;
    }
    return 0;
}
