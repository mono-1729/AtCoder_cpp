#include <bits/stdc++.h>
#include <unordered_map>
#include <stdlib.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <atcoder/all>
using namespace atcoder;
using namespace boost::multiprecision;
using namespace std;
#define rep(i, a, n) for(int i = a; i < n; i++)
#define rrep(i, a, n) for(int i = a; i >= n; i--)
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

ll dp[6][7][6][7][37];
ll check[6][7][6][7][37];

int main() {
    int h, w, t; cin >> h >> w >> t;
    vector<vector<ll>> s(h, vector<ll>(w));
    unordered_map<int,ll> mp;
    vector<vector<ll>> sum(h+1, vector<ll>(w+1));
    rep(i,0,h)rep(j,0,w) cin >> s[i][j];
    rep(i,1,h+1)rep(j,1,w+1) sum[i][j]  = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + s[i-1][j-1];
    rep(i,0,h)rep(j,0,h+1)rep(k,0,w)rep(l,0,w+1)rep(n,0,37) dp[i][j][k][l][n] = INF;
    ll ans = INF;
    auto calcsum = [&](int u, int d, int l, int r) ->ll {
        return sum[d][r] - sum[u][r] - sum[d][l] + sum[u][l];
    };
    rep(u_,0,h)rep(d_,u_+1,h+1)rep(l_,0,w)rep(r_,l_,w+1){
        ll border = calcsum(u_,d_,l_,r_);
        rep(x,0,h)rep(j,0,h+1)rep(k,0,w)rep(l,0,w+1)rep(n,0,37){
            dp[x][j][k][l][n] = INF;
            check[x][j][k][l][n] = 0;
        }

        auto solve = [&](auto solve, int u, int d, int l, int r, int div) -> ll {
            if(check[u][d][l][r][div]) return dp[u][d][l][r][div];
            if((d-u) * (r-l) < div){
                check[u][d][l][r][div] = 1;
                return INF;
            }
            if(calcsum(u,d,l,r) < border){
                check[u][d][l][r][div] = 1;
                return INF;
            }
            if(div == 1){
                check[u][d][l][r][div] = 1;
                return dp[u][d][l][r][div] = calcsum(u,d,l,r);
            }
            check[u][d][l][r][div] = 1;
            ll res = INF;
            rep(mid,u+1,d)rep(ndiv,1,div){
                chmin(res,max(solve(solve,u,mid,l,r,ndiv),solve(solve,mid,d,l,r,div-ndiv)));
            }
            rep(mid,l+1,r)rep(ndiv,1,div){
                chmin(res,max(solve(solve,u,d,l,mid,ndiv),solve(solve,u,d,mid,r,div-ndiv)));
            }
            return dp[u][d][l][r][div] = res;
        };
        chmin(ans,solve(solve, 0, h, 0, w, t+1)-border);
    }
    cout << ans << endl;
    return 0;
}