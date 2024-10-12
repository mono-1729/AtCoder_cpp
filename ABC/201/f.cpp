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

using S = long long;
S op(S x1, S x2) {
    return max(x1, x2);
} 
bool f(S x){
    return 1;
}
S e() {return 0;}

int main() {
    ll n; cin >> n;
    vector<ll> p(n), rev(n), sumc(n);
    rep(i,0,n) cin >> p[i], p[i]--;
    rep(i,0,n) rev[p[i]] = i;
    vector<ll> a(n), b(n), c(n);
    ll ans = INF, suma = 0;
    rep(i,0,n){
        cin >> a[i] >> b[i] >> c[i];
        chmin(b[i], a[i]);
        chmin(c[i], a[i]);
        suma += a[i];
    }
    rrep(i,n-1,1) sumc[i-1] = sumc[i] + a[i]-c[i];
    segtree<S,op,e> seg(n+1);
    rep(i,0,n){
        ll left = seg.get(0);
        ll mid = seg.prod(0, rev[i]+2);
        chmin(ans,suma-left-(a[i]-b[i])-sumc[i]);
        chmin(ans,suma-mid-a[i]-sumc[i]);
        seg.set(0,left+(a[i]-b[i]));
        seg.set(rev[i]+1,mid+a[i]);
    }
    cout << ans << endl;
    return 0;
}