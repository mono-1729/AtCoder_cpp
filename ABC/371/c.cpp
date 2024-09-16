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
    vector<ll> vec;
    rep(i,0,n) vec.push_back(i);
    vector<vector<ll>> g1(n,vector<ll>(n,0)), g2(n,vector<ll>(n,0));
    ll m1, m2;
    cin >> m1;
    ll ans = INF;
    rep(i,0,m1){
        ll u, v; cin >> u >> v;
        u--;v--;
        g1[u][v] = 1;
        g1[v][u] = 1;
    }
    cin >> m2;
    rep(i,0,m2){
        ll u, v; cin >> u >> v;
        u--;v--;
        g2[u][v] = 1;
        g2[v][u] = 1;
    }
    vector<vector<int>> a(n,vector<int>(n));
    rep(i,0,n)rep(j,i+1,n) cin >> a[i][j];
    do{
        ll num = 0;
        rep(i,0,n)rep(j,i+1,n){
            if(g2[i][j] != g1[vec[i]][vec[j]]) num += a[i][j];
        }
        chmin(ans,num);
    }while(next_permutation(vec.begin(), vec.end()));
    cout << ans << endl;
    return 0;
}