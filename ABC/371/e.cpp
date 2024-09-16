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

int main() {
    ll n; cin >> n;
    vector<ll> a(n);
    vector<vector<ll>> g(n, {-1});
    rep(i,0,n) cin >> a[i], a[i]--;
    rep(i,0,n) g[a[i]].push_back(i);
    rep(i,0,n) g[i].push_back(n);
    ll ans = n * (n+1) * (n) / 2;
    rep(i,0,n){
        rep(j,0,g[i].size()-1){
            ll x = g[i][j+1] - g[i][j] - 1;
            ans -= x * (x+1) / 2;
        }
    }
    cout << ans << endl;

    return 0;
}