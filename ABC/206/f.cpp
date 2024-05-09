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

void solve(){
    ll n;cin>>n;
    vector<ll> lvec(n),rvec(n);
    rep(i,0,n)cin>>lvec[i]>>rvec[i];
    vector<vector<ll>> dp(101,vector<ll>(101,-1));
    auto calc = [&](auto& calc,ll l,ll r){
        if(dp[l][r]!=-1)return dp[l][r];
        if(l==r)return dp[l][r]=0;
        vector<ll> g(101,0);
        rep(i,0,n){
            if(l<=lvec[i]&&rvec[i]<=r)g[calc(calc,l,lvec[i])^calc(calc,rvec[i],r)]=1;
        }
        rep(i,0,101)if(g[i]==0)return dp[l][r]=i;
    };
    if(calc(calc,0,100)==0)cout<<"Bob"<<endl;
    else cout<<"Alice"<<endl;
    
}

int main() {
    ll t;cin>>t;
    rep(_,0,t)solve();
    return 0;
}