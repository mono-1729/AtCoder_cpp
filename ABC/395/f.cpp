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
#define all(x) (x).begin(), (x).end()
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
    ll n, x; cin >> n >> x;
    vector<ll> u(n), d(n);
    ll sum = 0;
    rep(i,0,n) cin >> u[i] >> d[i], sum+= u[i]+d[i];
    ll ok = 0, ng = 3e9+1;
    rep(i,0,n) chmin(ng, u[i]+d[i]+1);
    while(abs(ok-ng) > 1){
        ll mid = (ok+ng)/2;
        ll l = 0, r = mid;
        ll f = 1;
        rep(i,0,n){
            ll nl = max(l-x, mid-d[i]);
            ll nr = min(r+x, u[i]);
            chmax(nl,0);
            chmin(nr,mid);
            if(nl > nr) f = 0;
            swap(nl, l);
            swap(nr, r);
        }
        if(f) ok = mid;
        else ng = mid;
    }
    cout << sum-ok*n << endl;
    return 0;
}