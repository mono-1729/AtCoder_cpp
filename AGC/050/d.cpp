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
using mint = modint998244353;

int main() {
    ll n, m; cin >> n >> m;
    // dp[i][j][k][l] := 残りi人, j周目, k人目のターン, l番目の人の確率
    vector dp(n+1, vector(m, vector(n, vector<mint>(n, 0))));
    vector check(n+1, vector(m, vector(n, vector<ll>(n, 0))));
    vector<mint> inv(n+1, 0);
    // cout << n+1 << " " << m << " " << n << " " << n << endl;
    rep(i,1,n+1) inv[i] = mint(i).inv();
    auto solve = [&](auto& solve, ll i, ll j, ll k, ll l) -> mint {
        // cout << i << " " << j << " " << k << " " << l << endl;
        if(j == m) return 0;
        if(check[i][j][k][l]) return dp[i][j][k][l];
        check[i][j][k][l] = 1;
        if(n-i == m) return dp[i][j][k][l] = 0;
        mint okp = (m-(n-i))*inv[m-j], ngp = 1-okp;
        if(k == l){
            ll nj = (k == i-1 ? j+1: j), nk = (k == i-1 ? 0: k+1);
            return dp[i][j][k][l] = okp+ngp*solve(solve,i,nj,nk,l);
        }else{
            ll nj = (k == i-1 ? j+1: j), nl = (k < l ? l-1 : l);
            ll nk1 = (k == i-1 ? 0: k), nk2 = (k == i-1 ? 0: k+1);
            return dp[i][j][k][l] = okp*solve(solve,i-1,nj,nk1,nl)+ngp*solve(solve,i,nj,nk2,l);
        }
    };
    rep(i,0,n) cout << solve(solve, n, 0, 0, i).val() << endl;
    return 0;
}