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

int main() {
    ll n, k; cin >> n >> k;
    vector<ll> a(n), b(n);
    vector<vector<ll>> dp(60,vector<ll>(n));
    vector<mint> ans(n);
    rep(i,0,n) cin >> a[i], a[i]--;
    rep(i,0,n) cin >> b[i];
    dp[0] = a;
    rep(i,1,60)rep(j,0,n) dp[i][j] = dp[i-1][dp[i-1][j]];
    auto dfs = [&](auto& dfs, vector<mint> vec, ll kk) -> void {
        if(kk == 0){
            rep(i,0,n) ans[i] += vec[i];
            return;
        }
        if(kk%2){
            vector<mint> nvec = vec;
            vector<ll> na(n);
            rep(i,0,n) na[i] = a[a[i]];
            rep(i,0,n) nvec[a[i]] += vec[i];
            swap(a,na);
            dfs(dfs,nvec,kk/2);
        }else{
            vector<mint> nvec(n,0);
            vector<ll> na(n);
            rep(i,0,n) na[i] = a[a[i]];
            rep(i,0,n) ans[i] += vec[i];
            rep(i,0,n) nvec[a[i]] += vec[i], nvec[a[a[i]]] += vec[i];
            swap(a,na);
            dfs(dfs,nvec,(kk-1)/2);
        }
    };
    vector<mint> tmp(n);
    rep(i,0,n) tmp[i] = b[i];
    dfs(dfs,tmp,k);
    rep(i,0,n) cout << ((ans[i]-b[i])/k).val() << " ";
    cout << endl;
    return 0;
}