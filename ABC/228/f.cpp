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
    ll h,w,h1,w1,h2,w2;cin>>h>>w>>h1>>w1>>h2>>w2;
    chmin(h2,h1);chmin(w2,w1);
    vector<vector<ll>> a(h,vector<ll>(w)),sum(h+1,vector<ll>(w+1));
    rep(i,0,h)rep(j,0,w)cin>>a[i][j];
    rep(i,0,h)rep(j,0,w)sum[i+1][j+1]=a[i][j];
    rep(i,1,h+1)rep(j,0,w)sum[i][j+1]+=sum[i][j];
    rep(j,1,w+1)rep(i,0,h)sum[i+1][j]+=sum[i][j];
    auto calc = [&](ll u,ll l,ll d,ll r)->ll{
        return sum[d+1][r+1]-sum[d+1][l]-sum[u][r+1]+sum[u][l];
    };
    vector<vector<ll>> aoki(h,vector<ll>(w,0));
    rep(i,0,h)rep(j,0,w){
        if(i+h2<=h && j+w2<=w)aoki[i][j]=calc(i,j,i+h2-1,j+w2-1);
    }
    ll hnum = h1-h2+1,wnum = w1-w2+1;
    rep(j,0,w){
        deque<ll> q;
        rep(i,0,hnum){
            while(!q.empty() && q.back()<aoki[i][j])q.pop_back();
            q.push_back(aoki[i][j]);
        } 
        if(aoki[0][j]==q.front())q.pop_front();
        else aoki[0][j]=q.front();
        rep(i,0,h-hnum){
            while(!q.empty() && q.back()<aoki[i+hnum][j])q.pop_back();
            q.push_back(aoki[i+hnum][j]);
            if(aoki[i+1][j]==q.front())q.pop_front();
            else aoki[i+1][j]=q.front();
        }
    }
    rep(i,0,h){
        deque<ll> q;
        rep(j,0,wnum){
            while(!q.empty() && q.back()<aoki[i][j])q.pop_back();
            q.push_back(aoki[i][j]);
        } 
        if(q.front()==aoki[i][0])q.pop_front();
        else aoki[i][0]=q.front();
        rep(j,0,w-wnum){
            while(!q.empty() && q.back()<aoki[i][j+wnum])q.pop_back();
            q.push_back(aoki[i][j+wnum]);
            if(aoki[i][j+1]==q.front())q.pop_front();
            else aoki[i][j+1]=q.front();
        }
    }
    ll ans = 0;
    rep(i,0,h-h1+1)rep(j,0,w-w1+1){
        chmax(ans,calc(i,j,i+h1-1,j+w1-1)-aoki[i][j]);
    }
    cout<<ans<<endl;
    return 0;
}