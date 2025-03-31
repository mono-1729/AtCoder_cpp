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


#define all(x) begin(x), end(x)
#define sz(x) int((x).size())
using vi = vector<int>;

#ifdef LOCAL
auto& operator<<(auto&, pair<auto, auto>);
auto operator<<(auto& o, auto x) -> decltype(x.end(), o) {
  o << "{";
  for (int i = 0; auto y : x) o << ", " + !i++ * 2 << y;
  return o << "}";
}
auto& operator<<(auto& o, pair<auto, auto> x) {
  return o << "(" << x.first << ", " << x.second << ")"; }
void __print(auto... x) { ((cerr << " " << x), ...) << endl; }
#define debug(x...) cerr << "[" #x "]:", __print(x)
#else
#define debug(...) 2137
#endif

template<int M, int R>
struct Mod {
  static const int MOD = M, ROOT = R;
  int x;
  Mod(ll y = 0) : x(y % M) { x += (x < 0) * M; }
  Mod& operator+=(Mod o) {
    if ((x += o.x) >= M) x -= M;
    return *this; }
  Mod& operator-=(Mod o) {
    if ((x -= o.x) < 0) x += M;
    return *this; }
  Mod& operator*=(Mod o) {
    x = 1ll * x * o.x % M;
    return *this; }
  Mod& operator/=(Mod o) { return *this *= o.inv(); }
  friend Mod operator+(Mod a, Mod b) { return a += b; }
  friend Mod operator-(Mod a, Mod b) { return a -= b; }
  friend Mod operator*(Mod a, Mod b) { return a *= b; }
  friend Mod operator/(Mod a, Mod b) { return a /= b; }
  auto operator<=>(const Mod&) const = default;
  Mod pow(ll n) const {
    Mod a = x, b = 1;
    for (; n; n /= 2, a *= a) if (n & 1) b *= a;
    return b;
  }
  Mod inv() const { assert(x != 0); return pow(M - 2); }
};
using mint = Mod<998244353, 3>;

void FST(vector<mint>& a, bool inv) {
  for (int n = sz(a), step = 1; step < n; step *= 2) {
    for (int i = 0; i < n; i += 2 * step) rep(j,i,i+step) {
      mint &u = a[j], &v = a[j + step]; tie(u, v) =
        // inv ? pair(v - u, u) : pair(v, u + v); // AND /// include-line
        // inv ? pair(v, u - v) : pair(u + v, u); // OR /// include-line
        pair(u + v, u - v);                    // XOR
    }
  }
  if (inv) { // XOR only
    mint i = mint(sz(a)).inv();
    for (mint& x : a) x *= i;
  }
}
vector<mint> conv(vector<mint> a, vector<mint> b) {
  FST(a, 0); FST(b, 0);
  rep(i, 0, sz(a)) a[i] *= b[i];
  FST(a, 1); return a;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n;
  cin >> n;
  vector<mint> a(1 << n), b(1 << n);
  rep(i, 0, 1 << n) cin >> a[i].x;
  rep(i, 0, 1 << n) cin >> b[i].x;
  auto c = conv(move(a), move(b));
  rep(i, 0, 1 << n) cout << c[i].x << " \n"[i == (1 << n) - 1];
}
