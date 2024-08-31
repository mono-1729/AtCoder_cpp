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
    ll n; cin >> n;
    vector<ll> a(n), b(n,0), c(n,0);
    rep(i,0,n) cin >> a[i];
    rep(i,0,n){
        if(a[i] >= 0) c[i] = a[i];
        else b[i] = a[i];
        if(i == 0) continue;
        ll maxi = max(0LL, b[i-1]-b[i]);
        chmax(maxi, c[i] - c[i-1]);
        b[i] += maxi;
        c[i] -= maxi;
    }
    auto calc = [&](ll plus) -> ll {
        ll res = 0;
        rep(i,0,n) res += abs(b[i]+plus);
        rep(i,0,n) res += abs(c[i]-plus);
        return res;
    };
    ll l = -3e13, r = 3e13;
    while(r-l >= 6){
        ll mid1 = (l*2+r)/3, mid2 = (l+r*2)/3;
        if(calc(mid1) > calc(mid2)) l = mid1;
        else r = mid2;
    }
    ll ans = 5e18;
    rep(num,l,r+1) chmin(ans, calc(num));
    cout << ans << endl;
    return 0;
}