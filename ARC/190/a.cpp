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

#define N 1000005

class SegmentTree {
  const ll inf = 1e18;
  int n, n0;
  ll max_v[4*N], smax_v[4*N], max_c[4*N];
  ll min_v[4*N], smin_v[4*N], min_c[4*N];
  ll sum[4*N];
  ll len[4*N], ladd[4*N], lval[4*N];

  void update_node_max(int k, ll x) {
    sum[k] += (x - max_v[k]) * max_c[k];

    if(max_v[k] == min_v[k]) {
      max_v[k] = min_v[k] = x;
    } else if(max_v[k] == smin_v[k]) {
      max_v[k] = smin_v[k] = x;
    } else {
      max_v[k] = x;
    }

    if(lval[k] != inf && x < lval[k]) {
      lval[k] = x;
    }
  }
  void update_node_min(int k, ll x) {
    sum[k] += (x - min_v[k]) * min_c[k];

    if(max_v[k] == min_v[k]) {
      max_v[k] = min_v[k] = x;
    } else if(smax_v[k] == min_v[k]) {
      min_v[k] = smax_v[k] = x;
    } else {
      min_v[k] = x;
    }

    if(lval[k] != inf && lval[k] < x) {
      lval[k] = x;
    }
  }

  void push(int k) {

    if(n0-1 <= k) return;

    if(lval[k] != inf) {
      updateall(2*k+1, lval[k]);
      updateall(2*k+2, lval[k]);
      lval[k] = inf;
      return;
    }

    if(ladd[k] != 0) {
      addall(2*k+1, ladd[k]);
      addall(2*k+2, ladd[k]);
      ladd[k] = 0;
    }

    if(max_v[k] < max_v[2*k+1]) {
      update_node_max(2*k+1, max_v[k]);
    }
    if(min_v[2*k+1] < min_v[k]) {
      update_node_min(2*k+1, min_v[k]);
    }

    if(max_v[k] < max_v[2*k+2]) {
      update_node_max(2*k+2, max_v[k]);
    }
    if(min_v[2*k+2] < min_v[k]) {
      update_node_min(2*k+2, min_v[k]);
    }
  }

  void update(int k) {
    sum[k] = sum[2*k+1] + sum[2*k+2];

    if(max_v[2*k+1] < max_v[2*k+2]) {
      max_v[k] = max_v[2*k+2];
      max_c[k] = max_c[2*k+2];
      smax_v[k] = max(max_v[2*k+1], smax_v[2*k+2]);
    } else if(max_v[2*k+1] > max_v[2*k+2]) {
      max_v[k] = max_v[2*k+1];
      max_c[k] = max_c[2*k+1];
      smax_v[k] = max(smax_v[2*k+1], max_v[2*k+2]);
    } else {
      max_v[k] = max_v[2*k+1];
      max_c[k] = max_c[2*k+1] + max_c[2*k+2];
      smax_v[k] = max(smax_v[2*k+1], smax_v[2*k+2]);
    }

    if(min_v[2*k+1] < min_v[2*k+2]) {
      min_v[k] = min_v[2*k+1];
      min_c[k] = min_c[2*k+1];
      smin_v[k] = min(smin_v[2*k+1], min_v[2*k+2]);
    } else if(min_v[2*k+1] > min_v[2*k+2]) {
      min_v[k] = min_v[2*k+2];
      min_c[k] = min_c[2*k+2];
      smin_v[k] = min(min_v[2*k+1], smin_v[2*k+2]);
    } else {
      min_v[k] = min_v[2*k+1];
      min_c[k] = min_c[2*k+1] + min_c[2*k+2];
      smin_v[k] = min(smin_v[2*k+1], smin_v[2*k+2]);
    }
  }

  void _update_min(ll x, int a, int b, int k, int l, int r) {
    if(b <= l || r <= a || max_v[k] <= x) {
      return;
    }
    if(a <= l && r <= b && smax_v[k] < x) {
      update_node_max(k, x);
      return;
    }

    push(k);
    _update_min(x, a, b, 2*k+1, l, (l+r)/2);
    _update_min(x, a, b, 2*k+2, (l+r)/2, r);
    update(k);
  }

  void _update_max(ll x, int a, int b, int k, int l, int r) {
    if(b <= l || r <= a || x <= min_v[k]) {
      return;
    }
    if(a <= l && r <= b && x < smin_v[k]) {
      update_node_min(k, x);
      return;
    }

    push(k);
    _update_max(x, a, b, 2*k+1, l, (l+r)/2);
    _update_max(x, a, b, 2*k+2, (l+r)/2, r);
    update(k);
  }

  void addall(int k, ll x) {
    max_v[k] += x;
    if(smax_v[k] != -inf) smax_v[k] += x;
    min_v[k] += x;
    if(smin_v[k] != inf) smin_v[k] += x;

    sum[k] += len[k] * x;
    if(lval[k] != inf) {
      lval[k] += x;
    } else {
      ladd[k] += x;
    }
  }

  void updateall(int k, ll x) {
    max_v[k] = x; smax_v[k] = -inf;
    min_v[k] = x; smin_v[k] = inf;
    max_c[k] = min_c[k] = len[k];

    sum[k] = x * len[k];
    lval[k] = x; ladd[k] = 0;
  }

  void _add_val(ll x, int a, int b, int k, int l, int r) {
    if(b <= l || r <= a) {
      return;
    }
    if(a <= l && r <= b) {
      addall(k, x);
      return;
    }

    push(k);
    _add_val(x, a, b, 2*k+1, l, (l+r)/2);
    _add_val(x, a, b, 2*k+2, (l+r)/2, r);
    update(k);
  }

  void _update_val(ll x, int a, int b, int k, int l, int r) {
    if(b <= l || r <= a) {
      return;
    }
    if(a <= l && r <= b) {
      updateall(k, x);
      return;
    }

    push(k);
    _update_val(x, a, b, 2*k+1, l, (l+r)/2);
    _update_val(x, a, b, 2*k+2, (l+r)/2, r);
    update(k);
  }

  ll _query_max(int a, int b, int k, int l, int r) {
    if(b <= l || r <= a) {
      return -inf;
    }
    if(a <= l && r <= b) {
      return max_v[k];
    }
    push(k);
    ll lv = _query_max(a, b, 2*k+1, l, (l+r)/2);
    ll rv = _query_max(a, b, 2*k+2, (l+r)/2, r);
    return max(lv, rv);
  }

  ll _query_min(int a, int b, int k, int l, int r) {
    if(b <= l || r <= a) {
      return inf;
    }
    if(a <= l && r <= b) {
      return min_v[k];
    }
    push(k);
    ll lv = _query_min(a, b, 2*k+1, l, (l+r)/2);
    ll rv = _query_min(a, b, 2*k+2, (l+r)/2, r);
    return min(lv, rv);
  }

  ll _query_sum(int a, int b, int k, int l, int r) {
    if(b <= l || r <= a) {
      return 0;
    }
    if(a <= l && r <= b) {
      return sum[k];
    }
    push(k);
    ll lv = _query_sum(a, b, 2*k+1, l, (l+r)/2);
    ll rv = _query_sum(a, b, 2*k+2, (l+r)/2, r);
    return lv + rv;
  }

public:
  SegmentTree(int n) {
    SegmentTree(n, nullptr);
  }

  SegmentTree(int n, ll *a) : n(n) {
    n0 = 1;
    while(n0 < n) n0 <<= 1;

    for(int i=0; i<2*n0; ++i) ladd[i] = 0, lval[i] = inf;
    len[0] = n0;
    for(int i=0; i<n0-1; ++i) len[2*i+1] = len[2*i+2] = (len[i] >> 1);

    for(int i=0; i<n; ++i) {
      max_v[n0-1+i] = min_v[n0-1+i] = sum[n0-1+i] = (a != nullptr ? a[i] : 0);
      smax_v[n0-1+i] = -inf;
      smin_v[n0-1+i] = inf;
      max_c[n0-1+i] = min_c[n0-1+i] = 1;
    }

    for(int i=n; i<n0; ++i) {
      max_v[n0-1+i] = smax_v[n0-1+i] = -inf;
      min_v[n0-1+i] = smin_v[n0-1+i] = inf;
      max_c[n0-1+i] = min_c[n0-1+i] = 0;
    }
    for(int i=n0-2; i>=0; i--) {
      update(i);
    }
  }

  // range minimize query
  void update_min(int a, int b, ll x) {
    _update_min(x, a, b, 0, 0, n0);
  }

  // range maximize query
  void update_max(int a, int b, ll x) {
    _update_max(x, a, b, 0, 0, n0);
  }

  // range add query
  void add_val(int a, int b, ll x) {
    _add_val(x, a, b, 0, 0, n0);
  }

  // range update query
  void update_val(int a, int b, ll x) {
    _update_val(x, a, b, 0, 0, n0);
  }

  // range minimum query
  ll query_max(int a, int b) {
    return _query_max(a, b, 0, 0, n0);
  }

  // range maximum query
  ll query_min(int a, int b) {
    return _query_min(a, b, 0, 0, n0);
  }

  // range sum query
  ll query_sum(int a, int b) {
    return _query_sum(a, b, 0, 0, n0);
  }
};

ll v[1000003];

int main() {
    ll n, m; cin >> n >> m;
    set<pll> st;
    map<pll,ll> mp;
    vector<ll> lvec(m), rvec(m);
    ll ans = 3;
    vector<pll> ansvec;
    ll rmin = 1000003, lmax = 0;
    ll rid = -1, lid = -1;
    rep(i,0,m){
        cin >> lvec[i] >> rvec[i];
        lvec[i]--;
        if(rmin > rvec[i]){
            rmin = rvec[i];
            rid = i;
        }
        if(lmax < lvec[i]){
            lmax = lvec[i];
            lid = i;
        }
        ll l = lvec[i], r = rvec[i];
        if(st.find({l, r}) != st.end() && ans == 3){
            ans = 2;
            ansvec = {}};
            
        }
        st.insert({l, r});
        if(l == 0 && r == n && ans > 1){
            ansvec = {{i,1}};
        }
    }
    if(rmin <= lmax && ans == 3){
        ans = 2;
        ansvec = {{lvec[rid], rvec[rid]}, {lvec[lid], rvec[lid]}};
    }
    SegmentTree seg(n,v);
    rep(i,0,m){
        seg.update_max(lvec[i]+1,1000003,rvec[i]);
    }
    rep(i,0,m){
        ll rma = seg.query_max(lvec[i],lvec[i]+1);
        if(rma <= rvec[i]) chmin(ans, 2LL);
    }
    if(ans > n){
        cout << -1 << endl;
        return 0;
    }
    
    return 0;
}