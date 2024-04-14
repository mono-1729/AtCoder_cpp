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

using mint = modint998244353;

int main() {
    ll n;cin>>n;
    vector<ll> a(n),b(n);
    rrep(i,n-1,0)cin>>a[i];
    rep(i,0,n)cin>>b[i];
    vector<ll> num(n);
    ll ans = 0;
    rep(k,0,5){
        vector<ll> x(n),y(n);
        vector<ll> sum(n);
        rep(i,0,n)x[i] = (~a[i]>>k &1);
        rep(i,0,n)y[i] = (~b[i]>>k &1);
        vector<ll> c = convolution(x,y);
        rep(i,0,c.size())sum[(i+1)%n]+=c[i];
        rep(i,0,n)num[i]+=(n-sum[i])<<k;
    }
    rep(i,0,n) chmax(ans, num[i]);
    //rep(i,0,n)cout<<num[i]<<endl;
    cout << ans << endl;
    return 0;
}