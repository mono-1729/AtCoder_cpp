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

template< typename T >
struct SparseTable {
  vector< vector< T > > st;
  vector< int > lookup;

  SparseTable(const vector< T > &v) {
    int b = 0;
    while((1 << b) <= v.size()) ++b;
    st.assign(b, vector< T >(1 << b));
    for(int i = 0; i < v.size(); i++) {
      st[0][i] = v[i];
    }
    for(int i = 1; i < b; i++) {
      for(int j = 0; j + (1 << i) <= (1 << b); j++) {
        st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
      }
    }
    lookup.resize(v.size() + 1);
    for(int i = 2; i < lookup.size(); i++) {
      lookup[i] = lookup[i >> 1] + 1;
    }
  }

  inline T rmq(int l, int r) {
    int b = lookup[r - l];
    return min(st[b][l], st[b][r - (1 << b)]);
  }
};


struct SuffixArray {
  vector< int > SA;
  const string s;

  SuffixArray(const string &str) : s(str) {
    SA.resize(s.size());
    iota(begin(SA), end(SA), 0);
    sort(begin(SA), end(SA), [&](int a, int b) {
      return s[a] == s[b] ? a > b : s[a] < s[b];
    });
    vector< int > classes(s.size()), c(s.begin(), s.end()), cnt(s.size());
    for(int len = 1; len < s.size(); len <<= 1) {
      for(int i = 0; i < s.size(); i++) {
        if(i > 0 && c[SA[i - 1]] == c[SA[i]] && SA[i - 1] + len < s.size() && c[SA[i - 1] + len / 2] == c[SA[i] + len / 2]) {
          classes[SA[i]] = classes[SA[i - 1]];
        } else {
          classes[SA[i]] = i;
        }
      }
      iota(begin(cnt), end(cnt), 0);
      copy(begin(SA), end(SA), begin(c));
      for(int i = 0; i < s.size(); i++) {
        int s1 = c[i] - len;
        if(s1 >= 0) SA[cnt[classes[s1]]++] = s1;
      }
      classes.swap(c);
    }
  }

  int operator[](int k) const {
    return SA[k];
  }

  size_t size() const {
    return s.size();
  }

  bool lt_substr(const string &t, int si = 0, int ti = 0) {
    int sn = (int) s.size(), tn = (int) t.size();
    while(si < sn && ti < tn) {
      if(s[si] < t[ti]) return true;
      if(s[si] > t[ti]) return false;
      ++si, ++ti;
    }
    return si >= sn && ti < tn;
  }

  int lower_bound(const string &t) {
    int low = -1, high = (int) SA.size();
    while(high - low > 1) {
      int mid = (low + high) / 2;
      if(lt_substr(t, SA[mid])) low = mid;
      else high = mid;
    }
    return high;
  }

  pair< int, int > lower_upper_bound(string &t) {
    int idx = lower_bound(t);
    int low = idx - 1, high = (int) SA.size();
    t.back()++;
    while(high - low > 1) {
      int mid = (low + high) / 2;
      if(lt_substr(t, SA[mid])) low = mid;
      else high = mid;
    }
    t.back()--;
    return {idx, high};
  }

  void output() {
    for(int i = 0; i < size(); i++) {
      cout << i << ": " << s.substr(SA[i]) << endl;
    }
  }
};

struct LongestCommonPrefixArray {
  const SuffixArray &SA;
  vector< int > LCP, rank;

  LongestCommonPrefixArray(const SuffixArray &SA) : SA(SA), LCP(SA.size()) {
    rank.resize(SA.size());
    for(int i = 0; i < SA.size(); i++) {
      rank[SA[i]] = i;
    }
    for(int i = 0, h = 0; i < SA.size(); i++) {
      if(rank[i] + 1 < SA.size()) {
        for(int j = SA[rank[i] + 1]; max(i, j) + h < SA.size() && SA.s[i + h] == SA.s[j + h]; ++h);
        LCP[rank[i] + 1] = h;
        if(h > 0) --h;
      }
    }
  }

  int operator[](int k) const {
    return LCP[k];
  }

  size_t size() const {
    return LCP.size();
  }

  void output() {
    for(int i = 0; i < size(); i++) {
      cout << i << ": " << LCP[i] << " " << SA.s.substr(SA[i]) << endl;
    }
  }
};

// Segment Tree Beats
// - l<=i<r について、 A_i の値を min(A_i, x) に更新
// - l<=i<r について、 A_i の値を max(A_i, x) に更新
// - l<=i<r の中の A_i の最大値を求める
// - l<=i<r の中の A_i の最小値を求める
// - l<=i<r の A_i の和を求める
// - l<=i<r について、 A_i の値に x を加える
// - l<=i<r について、 A_i の値を x に更新

#define N 1000005

class SegmentTreeBeats {
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
  SegmentTreeBeats(int n) {
    SegmentTreeBeats(n, nullptr);
  }

  SegmentTreeBeats(int n, ll *a) : n(n) {
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

ll vx[1000005];

using S = long long;
S op(S x1, S x2) {
    return min(x1,x2);
} 
ll border;
bool f(S x){
    return x >= border;
}
S e() {return INF;}

int main() {
    string s; cin >> s;
    ll m = s.size();
    ll n; cin >> n;
    vector<string> t(n);
    vector<ll> st_id(n);
    vector<ll> sz(1000005,-1);
    rep(i,0,n){
        st_id[i] = s.size();
        cin >> t[i];
        s += t[i];
        sz[st_id[i]] = t[i].size();
    }
    SuffixArray sa(s);
    LongestCommonPrefixArray lcp(sa);
    vector<S> vec(s.size());
    rep(i,0,s.size()) vec[i] = lcp[i];
    segtree<S,op,e> seg(vec);
    rep(i,0,N) vx[i] = INF;
    SegmentTreeBeats stb(s.size(),vx);
    rep(i,0,s.size()){
        if(sz[sa[i]] >= 0){
            border = sz[sa[i]];
            ll l = seg.min_left<f>(i+1);
            ll r = seg.max_right<f>(i+1);
            stb.update_min(l-1,r,sz[sa[i]]);
            cerr << i << " " << l << " " << r << endl;
        }
    }

    vector<ll> right(m, INF);
    rep(i,0,s.size()){
        if(sa[i] < m) right[sa[i]] = stb.query_min(i,i+1);
        if(sa[i] < m) cerr << i << " " << right[sa[i]] << endl;
    }
    ll ans = 0;
    ll r = INF;
    rep(i,0,m){
        chmin(r, i+right[i]);
        if(r == i+1){
            r = INF;
            ans++;
        }
    }

    cout << ans << endl;
    return 0;
}