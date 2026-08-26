#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <stdlib.h>
#include <atcoder/all>
using namespace atcoder;
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
#define inr(l, x, r) (l <= x && x < r)
#define ll long long
#define ld long double
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
    if(b == 0) return a;
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
    ll l, k, n; cin >> l >> k >> n;
    vector<double> a(n);
    rep(i,0,n) cin >> a[i];
    rep(i,0,n) a.push_back(a[i]+l);
    vector<ll> num(n,0);
    vector<mint> pow2(n+1,1);
    rep(i,0,n) pow2[i+1] = pow2[i]*2;
    mint ans = 0;
    rep(i,0,n){
        ll r = lower_bound(all(a), a[i]+k-0.5)-a.begin();
        num[r-i-1]++;
    }
    mint n0 = 1, n1 = 0, x = 1;
    rep(i,0,n){
        ans += x*num[i]*pow2[n-i-1];
        mint nn0 = n0+n1, nn1 = n1+n0;
        x = x*2+n1;
        swap(n0,nn0);
        swap(n1,nn1);
        // cout << ans.val() << endl;
        // cout << n0.val() << " " << n1.val() << " " << x.val() << endl;
    }

    // rep(i,0,n-1) ans *= 2;
    cout << ans.val() << endl;
    return 0;
}