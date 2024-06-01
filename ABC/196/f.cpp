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
    string s,t;cin>>s>>t;
    ll n = s.size(),m = t.size();
    vector<int> svec(n),tvec(m),srvec(n),trvec(m);
    rep(i,0,n)svec[i] = s[i]-'0',srvec[i]=1-svec[i];
    rep(i,0,m)tvec[m-i-1] = t[i]-'0',trvec[m-i-1]=1-tvec[m-i-1];
    vector<int> x1 = convolution(svec,trvec), x2 = convolution(tvec,srvec);
    ll ans = INF;
    rep(i, m-1, n)chmin(ans,x1[i]+x2[i]);
    cout << ans << endl;
    return 0;
}