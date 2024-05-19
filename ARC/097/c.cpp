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
    ll n;cin>>n;
    vector<char> c(2*n);
    vector<ll> a(2*n);
    rep(i,0,2*n){
        cin>>c[i]>>a[i];
        a[i]--;
    }
    vector<vector<ll>> dp(n+1, vector<ll>(n+1, INF));
    vector<vector<ll>> wleft(n, vector<ll>(n+1, 0)),bleft(n, vector<ll>(n+1, 0));
    rep(i,0,2*n){
        if(c[i] == 'W'){
            rep(j,0,i){
                if(c[j] == 'B')wleft[a[i]][a[j]]++;
                else if(a[i]<a[j]) wleft[a[i]][n]++;
            }
        }else{
            rep(j,0,i){
                if(c[j] == 'W')bleft[a[i]][a[j]]++;
                else if(a[i]<a[j]) bleft[a[i]][n]++;
            }
        }
    }
    rep(i,0,n){
        rrep(j,n-1,0){
            wleft[i][j] += wleft[i][j+1];
            bleft[i][j] += bleft[i][j+1];
        }
    }
    dp[0][0] = 0;
    rep(i,0,n+1)rep(j,0,n+1){
        if(i < n)chmin(dp[i+1][j], dp[i][j] + wleft[i][j]);
        if(j < n)chmin(dp[i][j+1], dp[i][j] + bleft[j][i]);
    }
    cout<<dp[n][n]<<endl;
    // rep(i,0,n+1){
    //     rep(j,0,n+1){
    //         cout<<dp[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    return 0;
}