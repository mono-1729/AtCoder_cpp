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

struct Mo {
  int width;
  vector<int> left, right, order;

  Mo(int N, int Q) : order(Q) {
    width = max<int>(1, 1.0 * N / max<double>(1.0, sqrt(Q * 2.0 / 3.0)));
    iota(begin(order), end(order), 0);
  }

  void insert(int l, int r) { /* [l, r) */
    left.emplace_back(l);
    right.emplace_back(r);
  }

  template <typename AL, typename AR, typename DL, typename DR, typename REM>
  void run(const AL &add_left, const AR &add_right, const DL &delete_left,
           const DR &delete_right, const REM &rem) {
    assert(left.size() == order.size());
    sort(begin(order), end(order), [&](int a, int b) {
      int ablock = left[a] / width, bblock = left[b] / width;
      if (ablock != bblock) return ablock < bblock;
      if (ablock & 1) return right[a] < right[b];
      return right[a] > right[b];
    });
    int nl = 0, nr = 0;
    for (auto idx : order) {
      while (nl > left[idx]) add_left(--nl);
      while (nr < right[idx]) add_right(nr++);
      while (nl < left[idx]) delete_left(nl++);
      while (nr > right[idx]) delete_right(--nr);
      rem(idx);
    }
  }
};

using S = pll;
S op(S x1, S x2) {
    return {x1.first+x2.first, x1.second+x2.second};
} 
S e() {return {0,0};}

int main() {
    ll n; cin >> n;
    vector<ll> a(n), b(n);
    rep(i,0,n) cin >> a[i];
    rep(i,0,n) cin >> b[i];
    vector<pll> avec(n), bvec(n);
    rep(i,0,n) avec[i] = {a[i], i};
    rep(i,0,n) bvec[i] = {b[i], i};
    sort(avec.begin(), avec.end());
    sort(bvec.begin(), bvec.end());
    vector<ll> aid(n), bid(n);
    rep(i,0,n) aid[avec[i].second] = i;
    rep(i,0,n) bid[bvec[i].second] = i;
    vector<ll> atob(n), btoa(n);
    rep(i,0,n){
        atob[i] = lower_bound(bvec.begin(), bvec.end(), make_pair(a[i], 0LL))-bvec.begin();
        btoa[i] = lower_bound(avec.begin(), avec.end(), make_pair(b[i], 0LL))-avec.begin();
    }
    ll k; cin >> k;
    Mo mo(n, k);
    for(ll i = 0; i < k; i++) {
        ll x, y; cin >> x >> y;
        mo.insert(x, y);
    }
    vector<ll> ans(k);
    segtree<S,op,e> sega(n), segb(n);
    ll sum = 0;

    auto add_left = [&](int i) {
        // cout << "al: " << i << endl; 
        auto resl = segb.prod(0,atob[i]);
        auto resr = segb.prod(atob[i],n);
        sum -= a[i]*resl.first - resl.second;
        sum -= -a[i]*resr.first + resr.second;
        sega.set(aid[i], {0,0});
    };
    auto add_right = [&](int i) {
        // cout << "ar: " << i << endl;
        auto resl = sega.prod(0,btoa[i]);
        auto resr = sega.prod(btoa[i],n);
        sum += b[i]*resl.first - resl.second;
        sum += -b[i]*resr.first + resr.second;
        segb.set(bid[i], {1,b[i]});
    };
    auto delete_left = [&](int i) {
        // cout << "dl: " << i << endl;
        auto resl = segb.prod(0,atob[i]);
        auto resr = segb.prod(atob[i],n);
        sum += a[i]*resl.first - resl.second;
        sum += -a[i]*resr.first + resr.second;
        sega.set(aid[i], {1,a[i]});
    };
    auto delete_right = [&](int i) {
        // cout << "dr: " << i << endl;
        auto resl = sega.prod(0,btoa[i]);
        auto resr = sega.prod(btoa[i],n);
        sum -= b[i]*resl.first - resl.second;
        sum -= -b[i]*resr.first + resr.second;
        segb.set(bid[i], {0,0});
    };
    auto rem = [&](int q) {
        // cout << "rem" << endl;
        ans[q] = sum;
    };
    mo.run(add_left, add_right, delete_left, delete_right, rem);
    for(auto &p: ans) cout << p << endl;
}