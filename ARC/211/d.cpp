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

int main() {
    ll n, m; cin >> n >> m;
    vector<vector<ll>> g(n);
    rep(i,0,m){
        ll u, v; cin >> u >> v;
        u--;v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    unordered_set<ll> st;
    vector<vector<ll>> ans(2,vector<ll>(n,-1)), check(2,vector<ll>(n,0));
    auto dfs = [&](auto dfs, ll v, ll p, ll num) -> void {
        for(auto nv: g[v]){
            if(p == nv ||  st.contains(v*n+nv)) continue;
            if(check[num][nv]) continue;
            check[num][nv] = 1;
            ans[num][nv] = v;
            st.insert(v*n+nv);
            dfs(dfs,nv,v,num);
        }
    };
    check[0][0] = check[1][1] = 1;
    ans[0][0] = ans[1][1] = -INF;
    dfs(dfs,0,-1,0);
    dfs(dfs,1,-1,1);
    rep(i,0,2){
        rep(j,0,n){
            if(ans[i][j] == -1){
                cout << "No" << endl;
                return 0;
            }
        }
    }
    cout << "Yes" << endl;
    cout << ans[1][0]+1 << endl << ans[0][1]+1 << endl;
    rep(i,2,n){
        cout << ans[0][i]+1 << " " << ans[1][i]+1 << endl;
    }
    return 0;
}