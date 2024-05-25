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
    ll n,k;cin>>n>>k;
    if(2*k-1>n){
        cout<<-1<<endl;
        return 0;
    }
    vector<ll> a(n),b(n),c(n);
    rep(i,0,n) c[i]=k+2*n+i;
    rep(i,0,(n+1)/2){
        a[i]=k+i*2;
        b[i]=k+n+(n+1)/2-1-i;
    }
    rep(i,(n+1)/2,n){
        a[i]=k+(i-(n+1)/2)*2+1;
        b[i]=k+2*n-1-(i-(n+1)/2);
    }
    rep(i,0,n)cout<<a[i]<<" "<<b[i]<<" "<<c[i]<<endl;
    return 0;
}