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
    ll n, x;cin >> n >> x;
    vector<tuple<ll,ll,ll>> minus = {{0,-1,-1}}, plus = {{0,-1,-1}};
    vector<ll> y(n), z(n);
    rep(i,0,n) cin >> y[i];
    rep(i,0,n) cin >> z[i];
    if(x < 0){
        rep(i,0,n){
            y[i]*=-1;
            z[i]*=-1;
        }
        x*=-1;
    }
    plus.push_back({x,2,-1});
    rep(i,0,n){
        if(y[i] > 0) plus.push_back({y[i],1,i});
        else minus.push_back({-y[i],1,i});
        if(z[i] > 0) plus.push_back({z[i],0,i});
        else minus.push_back({-z[i],0,i});
    }
    sort(plus.begin(),plus.end());
    sort(minus.begin(),minus.end());
    vector<vector<ll>> key_minus(n,vector<ll>(minus.size(),0)), key_plus(n,vector<ll>(plus.size(),0));
    rep(i,0,plus.size()){
        if(get<1>(plus[i])==0){
            ll idx = get<2>(plus[i]);
            rep(j,i,plus.size())key_plus[idx][j] = 1;
        }
    }
    rep(i,0,minus.size()){
        if(get<1>(minus[i])==0){
            ll idx = get<2>(minus[i]);
            rep(j,i,minus.size())key_minus[idx][j] = 1;
        }
    }
    vector<vector<vector<ll>>> dp(plus.size(), vector<vector<ll>>(minus.size(),vector<ll>(2,INF)));
    dp[0][0][0] = 0;
    rep(i,0,plus.size()){
        rep(j,0,minus.size()){
            if(i>0){
                ll pos,type,idx;tie(pos,type,idx) = plus[i];
                ll prepos = get<0>(plus[i-1]);
                ll lpos = get<0>(minus[j]);
                if(type == 1){
                    if(key_plus[idx][i] == 1 || key_minus[idx][j] == 1){
                        chmin(dp[i][j][0],dp[i-1][j][0]+pos-prepos);
                        chmin(dp[i][j][0],dp[i-1][j][1]+pos+lpos);
                    }
                }
                else{
                    chmin(dp[i][j][0],dp[i-1][j][0]+pos-prepos);
                    chmin(dp[i][j][0],dp[i-1][j][1]+pos+lpos);
                }
            }
            if(j>0){
                ll pos,type,idx;tie(pos,type,idx) = minus[j];
                ll prepos = get<0>(minus[j-1]);
                ll rpos = get<0>(plus[i]);
                if(type == 1){
                    if(key_plus[idx][i] == 1 || key_minus[idx][j] == 1){
                        chmin(dp[i][j][1],dp[i][j-1][1]+pos-prepos);
                        chmin(dp[i][j][1],dp[i][j-1][0]+pos+rpos);
                    }
                }
                else{
                    chmin(dp[i][j][1],dp[i][j-1][1]+pos-prepos);
                    chmin(dp[i][j][1],dp[i][j-1][0]+pos+rpos);
                }
            }
        }
    }
    ll ans = INF;
    rep(i,0,plus.size()){
        if(get<1>(plus[i])==2){
            rep(j,0,minus.size())chmin(ans,dp[i][j][0]);
        }
    }
    if(ans == INF) cout << -1 << endl;
    else cout << ans << endl;
    // rep(i,0,plus.size()){
    //     rep(j,0,minus.size()){
    //         cout<<min(dp[i][j][0],dp[i][j][1])<<" ";
    //     }
    //     cout << endl;
    // }
    return 0;
}