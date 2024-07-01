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
    int n; cin >> n;
    vector<ll> a(n);
    rep(i,0,n) cin >> a[i];
    vector<ll> bdist(n,0),b(n);
    ll bdsum = 0;
    rep(i,1,n){
        bdist[i] = a[i] + bdist[i-1];
        bdsum += bdist[i];
    }
    // cout << a[0] << " " << bdist[n-1] << " " << bdsum%n << " " << endl;
    if(a[0] != -bdist[n-1] || bdsum%n != 0){
        cout << -1 << endl;
        return 0;
    }
    b[0] = -bdsum/n;
    rep(i,1,n)b[i] = b[0] + bdist[i];
    vector<ll> x(n);
    x[0] = 0;
    ll minx = 0, xsum = 0;
    rep(i,1,n){
        x[i] = x[i-1]+b[i-1];
        chmin(minx,x[i]);
        xsum += x[i];
    }
    cout << xsum - minx*n << endl;
    return 0;
}