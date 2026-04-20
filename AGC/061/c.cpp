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
using SS = mint;
using S = ll;
SS op(SS a, SS b) {
    return a+b;
} 
SS e() {return 0;}
S op1(S a, S b) {
    return min(a,b);
} 
S e1() {return INF;}
S op2(S a, S b) {
    return max(a,b);
} 
S e2() {return 0;}


int main() {
    ll n; cin >> n;
    segtree<SS,op,e> seg(2*n+1);
    segtree<S,op1,e1> segmi(2*n);
    segtree<S,op2,e2> segma(2*n);
    vector<ll> a(n), b(n);
    rep(i,0,n){
        cin >> a[i] >> b[i];
        a[i]--, b[i]--;
        segmi.set(a[i],a[i]);
        segmi.set(b[i],a[i]);
        segma.set(a[i],b[i]);
        segma.set(b[i],b[i]);
    }
    vector<mint> pow2(n+1,1), inv2(n+1,((mint)2).inv());
    rep(i,0,n) pow2[i+1] = pow2[i]*2;
    rep(i,1,n) inv2[i+1] = inv2[i]*inv2[1];
    seg.set(0,pow2[n]);
    rep(i,0,n){
        ll mi = segmi.prod(a[i], b[i]);
        ll ma = segma.prod(a[i], b[i]);
        seg.set(ma+1, seg.get(ma+1)-seg.prod(0,a[i]+1)*inv2[b[i]-a[i]]);
    }
    cout << seg.all_prod().val() << endl;
    // rep(i,0,2*n+1) cout << seg.get(i).val() << " ";
    cout << endl;
    return 0;
}