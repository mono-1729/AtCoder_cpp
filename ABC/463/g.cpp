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

struct Mo {
  int n;
  vector< pair< int, int > > lr;

  explicit Mo(int n) : n(n) {}

  void add(int l, int r) { /* [l, r) */
    lr.emplace_back(l, r);
  }

  template< typename AL, typename AR, typename EL, typename ER, typename O >
  void build(const AL &add_left, const AR &add_right, const EL &erase_left, const ER &erase_right, const O &out) {
    int q = (int) lr.size();
    int bs = n / min< int >(n, sqrt((double)q));
    vector< int > ord(q);
    iota(begin(ord), end(ord), 0);
    sort(begin(ord), end(ord), [&](int a, int b) {
      int ablock = lr[a].first / bs, bblock = lr[b].first / bs;
      if(ablock != bblock) return ablock < bblock;
      return (ablock & 1) ? lr[a].second > lr[b].second : lr[a].second < lr[b].second;
    });
    int l = 0, r = 0;
    for(auto idx : ord) {
      while(l > lr[idx].first) add_left(r,--l);
      while(r < lr[idx].second) add_right(++r,l);
      while(l < lr[idx].first) erase_left(r,++l);
      while(r > lr[idx].second) erase_right(--r,l);
      out(idx);
    }
  }

//   template< typename A, typename E, typename O >
//   void build(const A &add, const E &erase, const O &out) {
//     build(add, add, erase, erase, out);
//   }
};

ll maxnum=200005;
vector<ll> fac(maxnum), inv(maxnum), finv(maxnum);
void init_fac(){
    fac[0] = fac[1] = 1;
    inv[1] = 1;
    finv[0] = finv[1] = 1;
    rep(i, 2, maxnum){
        fac[i] = fac[i-1]*i%MOD;
        inv[i] = MOD-MOD/i*inv[MOD%i]%MOD;
        finv[i] = finv[i-1]*inv[i]%MOD;
    }
}
ll nCr(ll n, ll r){
    if(n < 0 or n-r < 0 or r < 0) return 0;
    return fac[n]*(finv[n-r]*finv[r]%MOD)%MOD;
}
ll nHr(ll n, ll r){
    return nCr(n+r-1, r);
}

int main() {
    init_fac();
    ll t; cin >> t;
    vector<mint> ans(t);
    Mo mo(200005);
    vector<pll> p(t);
    vector<ll> id;
    rep(i,0,t){
        ll n, x; cin >> n >> x;
        p[i] = {n,x};
        if(abs(x) >= n) ans[i] = abs(x);
        else{
            mo.add((n+x)/2,n);
            id.push_back(i);
        }
    }
    mint num1 = 1, num2 = 0;
    vector<mint> div2(200005,1), pow2(200005,1);
    rep(i,1,200005) div2[i] = div2[i-1]/2, pow2[i] = pow2[i-1]*2;
    auto add_n = [&](int i, int j) {
        num2 = 2*num2+num1-nCr(i-1,j)*(j+1);
        num1 = 2*num1-nCr(i-1,j);
    };
    auto erase_n = [&](int i, int j) {
        num1 = (num1+nCr(i,j))*div2[1];
        num2 = (num2-num1+nCr(i,j)*(j+1))*div2[1];
    };
    auto add_r= [&](int i, int j) {
        num1 += nCr(i,j);
        num2 += nCr(i,j)*j;
    };
    auto erase_r = [&](int i, int j) {
        num1 -= nCr(i,j+1);
        num2 -= nCr(i,j+1)*(j+1);
    };
    auto out = [&](int q) {
        auto [n,x] = p[id[q]];
        mint psum = pow2[n]*n*div2[1];
        ans[id[q]] = (num1*(x+n)-num2*2+(psum-num2)*2-(pow2[n]-num1)*(x+n))*div2[n];
    };
    mo.build(erase_r,add_n,add_r,erase_n,out);
    for(auto x: ans) cout << x.val() << endl;
    return 0;
}