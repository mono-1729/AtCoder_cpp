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

/**
 * @brief Slope-Trick
 *
 * @see https://maspypy.com/slope-trick-1-%E8%A7%A3%E8%AA%AC%E7%B7%A8
 */
template <typename T>
struct SlopeTrick {
  const T INF = numeric_limits<T>::max() / 3;

  T min_f;
  priority_queue<T, vector<T>, less<> > L;
  priority_queue<T, vector<T>, greater<> > R;
  T add_l, add_r;

 private:
  void push_R(const T &a) { R.push(a - add_r); }

  T top_R() const {
    if (R.empty())
      return INF;
    else
      return R.top() + add_r;
  }

  T pop_R() {
    T val = top_R();
    if (not R.empty()) R.pop();
    return val;
  }

  void push_L(const T &a) { L.push(a - add_l); }

  T top_L() const {
    if (L.empty())
      return -INF;
    else
      return L.top() + add_l;
  }

  T pop_L() {
    T val = top_L();
    if (not L.empty()) L.pop();
    return val;
  }

  size_t size() { return L.size() + R.size(); }

 public:
  SlopeTrick() : min_f(0), add_l(0), add_r(0) {}

  struct Query {
    T lx, rx, min_f;
  };

  // return min f(x)
  Query query() const { return (Query){top_L(), top_R(), min_f}; }

  // f(x) += a
  void add_all(const T &a) { min_f += a; }

  // add \_
  // f(x) += max(a - x, 0)
  void add_a_minus_x(const T &a) {
    min_f += max(T(0), a - top_R());
    push_R(a);
    push_L(pop_R());
  }

  // add _/
  // f(x) += max(x - a, 0)
  void add_x_minus_a(const T &a) {
    min_f += max(T(0), top_L() - a);
    push_L(a);
    push_R(pop_L());
  }

  // add \/
  // f(x) += abs(x - a)
  void add_abs(const T &a) {
    add_a_minus_x(a);
    add_x_minus_a(a);
  }

  // \/ -> \_
  // f_{new} (x) = min f(y) (y <= x)
  void clear_right() {
    while (not R.empty()) R.pop();
  }

  // \/ -> _/
  // f_{new} (x) = min f(y) (y >= x)
  void clear_left() {
    while (not L.empty()) L.pop();
  }

  // \/ -> \_/
  // f_{new} (x) = min f(y) (x-b <= y <= x-a)
  void shift(const T &a, const T &b) {
    assert(a <= b);
    add_l += a;
    add_r += b;
  }

  // \/. -> .\/
  // f_{new} (x) = f(x - a)
  void shift(const T &a) { shift(a, a); }

  // L, R を破壊する
  T get(const T &x) {
    T ret = min_f;
    while (not L.empty()) {
      ret += max(T(0), pop_L() - x);
    }
    while (not R.empty()) {
      ret += max(T(0), x - pop_R());
    }
    return ret;
  }

  void merge(SlopeTrick &st) {
    if (st.size() > size()) {
      swap(st.L, L);
      swap(st.R, R);
      swap(st.add_l, add_l);
      swap(st.add_r, add_r);
      swap(st.min_f, min_f);
    }
    while (not st.R.empty()) {
      add_x_minus_a(st.pop_R());
    }
    while (not st.L.empty()) {
      add_a_minus_x(st.pop_L());
    }
    min_f += st.min_f;
  }
};



int main() {
    ll n; cin >> n;
    queue<pair<SlopeTrick<ll>,ll>> q;
    rep(i,0,1<<n){
        ll l, r; cin >> l >> r;
        l--, r--;
        SlopeTrick<ll> p;
        p.add_a_minus_x(l);
        p.add_x_minus_a(r);
        q.push({p, r});
    }
    auto merge = [](SlopeTrick<ll> &a, SlopeTrick<ll> &b, ll r){
        a.merge(b);
        a.clear_right();
        a.add_x_minus_a(r);
    };
    while(q.size() > 1){
        auto [a,r1] = q.front(); q.pop();
        auto [b,r2] = q.front(); q.pop();
        merge(a, b, max(r1, r2));
        q.push({a,max(r1, r2)});
    }
    cout << q.front().first.query().min_f << endl;
    return 0;
}