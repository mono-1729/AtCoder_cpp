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
    ll a,b,c,d,e,f; cin >> a >> b >> c >> d >> e >> f;
    ll g,h,i,j,k,l; cin >> g >> h >> i >> j >> k >> l;
    ll x = min(max(a,d),max(g,j))-max(min(a,d),min(g,j));
    ll y = min(max(b,e),max(h,k))-max(min(b,e),min(h,k));
    ll z = min(max(c,f),max(i,l))-max(min(c,f),min(i,l));
    if(x > 0 && y > 0 && z > 0) cout << "Yes" << endl;
    else cout << "No" << endl;
    return 0;
}