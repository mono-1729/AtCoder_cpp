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

ll powMod(ll x, ll n,ll mod) {
    if (n == 0) return 1 % mod;
    ll val = powMod(x, n / 2,mod);
    val *= val;
    val %= mod;
    if (n % 2 == 1) val *= x;
    return val % mod;
}


int main() {
    ll n,m;cin>>n>>m;
    vector<ll> p(n+1, 1);
    vector<ll> np(n+1, 1);
    rep(i, 1, n+1){
        np[i] = np[i-1]*n%m;
    }
    rrep(i,n-1,1){
        p[i] = p[i+1]*i%m;
    }
    ll ans = 0;
    rep(i, 1, n){
        ans += ((p[n-i]*(((i+1)*i/2)%m))%m)*np[n-i-1];
        ans%=m;
    }
    cout<<(ans*n)%m<<endl;
    return 0;
}