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

ll solve(ll a, ll b){
    vector<ll> evennum = {2,1,0,1}, oddnum = {1,2,1,0};
    ll evenrow = (a/4)*4,oddrow = (a/4)*4;
    rep(i,0,a%4){
        evenrow+=evennum[i];
        oddrow+=oddnum[i];
    }
    return ((b+1)/2)*evenrow + (b/2)*oddrow;

}

int main() {
    ll a,b,c,d;cin>>a>>b>>c>>d;
    a+=(ll)1e9;
    b+=(ll)1e9;
    c+=(ll)1e9;
    d+=(ll)1e9;
    ll ans = 0;
    ans+=solve(c,d);
    ans-=solve(a,d);
    ans-=solve(c,b);
    ans+=solve(a,b);
    cout<<ans<<endl;
    //cout<<solve(3,3)<<endl;
    return 0;
}