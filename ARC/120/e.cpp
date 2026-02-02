#include <bits/stdc++.h>
#include <stdlib.h>
#include <atcoder/all>
using namespace atcoder;
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
#define inr(l, x, r) (l <= x && x < r)
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

ll powMod(ll x, ll n, ll mod) {
    if (n == 0) return 1 % mod;
    ll val = powMod(x, n / 2, mod);
    val *= val;
    val %= mod;
    if (n % 2 == 1) val *= x;
    return val % mod;
}

int main() {
    ll n; cin >> n;
    vector<ll> a(n+1);
    rep(i,0,n) cin >> a[i];
    a.push_back(a[n-1]);
    ll ng = 0, ok = IINF;
    auto solve = [&](ll mid) -> ll {
        ll l = 0, r = mid;
        rep(i,1,n){
            ll nl = INF, nr = -INF;
            if(r >= (a[i]-a[i-1])/2) chmin(nl,(a[i]-a[i-1])/2);
            if(l+(a[i]-a[i-1])/2 <= mid) chmin(nl, l+(a[i]-a[i-1])/2);
            chmax(nr,r-(a[i]-a[i-1])/2);
            chmax(nr,mid-l-(a[i]-a[i-1])/2);
            if(nl == INF || nr < 0) return 0;
            l = nl, r = nr;
        }
        return 1;
    };
    while(ok-ng > 1){
        ll mid = (ng+ok)/2;
        if(solve(mid)) ok = mid;
        else ng = mid;
    }
    cout << ok << endl;
    return 0;
}