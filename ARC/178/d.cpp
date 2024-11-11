#pragma GCC optimize ("O3,inline,omit-frame-pointer,no-asynchronous-unwind-tables,fast-math")
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

ll powMod(ll x, ll n) {
    if (n == 0) return 1 % MOD;
    ll val = powMod(x, n / 2);
    val *= val;
    val %= MOD;
    if (n % 2 == 1) val *= x;
    return val % MOD;
}

int main() {
    ll n, m; cin >> n >> m;
    vector<ll> a(m), in(n,0), rev(n,-1);
    rep(i,0,m) cin >> a[i], in[a[i]] = 1, rev[a[i]] = i;
    vector<vector<mint>> dp(m+1,vector<mint>(m+1,0));
    vector<vector<mint>> sumr(m+1, vector<mint>(m+2,0)), suml(m+1, vector<mint>(m+2,0));
    if(in[0]) dp[rev[0]][m-rev[0]-1] = 1, sumr[rev[0]][m-rev[0]] = 1, suml[m-rev[0]-1][rev[0]+1] = 1;
    else rep(i,0,m+1) dp[i][m-i] = 1, sumr[i][m-i+1] = 1, suml[m-i][i+1] = 1;
    rep(i,0,m+1)rep(j,0,m+1) sumr[i][j+1] += sumr[i][j];
    rep(i,0,m+1)rep(j,0,m+1) suml[i][j+1] += suml[i][j];
    rep(i,1,n){
        vector<vector<mint>> ndp(m+1,vector<mint>(m+1, 0));
        vector<vector<mint>> nsumr(m+1, vector<mint>(m+2,0)), nsuml(m+1, vector<mint>(m+2,0));
        if(in[i]){
            rep(l,0,m+1)rep(r,0,m-l+1) ndp[min(l,rev[i])][min(r,m-rev[i]-1)] += dp[l][r];
            rep(l,0,m+1)rep(r,0,m-l+1) nsumr[l][r+1] += ndp[l][r], nsuml[r][l+1] += ndp[l][r];
        }else{ 
            rep(l,0,m+1)rep(r,0,m-l+1){
                ndp[l][r] += sumr[l][m+1] - sumr[l][r];
                ndp[l][r] += suml[r][m+1] - suml[r][l];
                nsumr[l][r+1] += ndp[l][r];
                nsuml[r][l+1] += ndp[l][r];
            }
        }
        swap(dp, ndp);
        rep(j,0,m+1)rep(k,0,m-max(j-1,0LL)+1) nsumr[j][k+1] += nsumr[j][k];
        rep(j,0,m+1)rep(k,0,m-max(j-1,0LL)+1) nsuml[j][k+1] += nsuml[j][k];
        swap(sumr, nsumr);
        swap(suml, nsuml);
    }  
    cout << dp[0][0].val() << endl;

    return 0;
}