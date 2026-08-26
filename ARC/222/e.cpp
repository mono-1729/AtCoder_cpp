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
    ll n, m; cin >> n >> m;
    vector<ll> a(n), cnt(1LL<<m);
    mint ans = 0;
    rep(i,0,n) cin >> a[i], cnt[a[i]]++;
    mint div2 = ((mint)1)/2;
    vector<mint> pow10(1LL<<m,1);
    rep(i,1,1LL<<m) pow10[i] = pow10[i-1]*10;
    rep(i,0,1LL<<m) ans += cnt[i]/2;
    ll b = 20;
    rep(i,0,b){
        vector<mint> v(1LL<<m);
        rep(j,0,1<<m) if(cnt[j] > i) v[j] = 1;
        auto res = conv(v,v);
        rep(j,1,1LL<<m) ans += res[j]*pow10[j]*div2;
    }
    {
        vector<ll> v;
        rep(i,0,1LL<<m) if(cnt[i] > b)v.push_back(i);
        ll nn = v.size();
        rep(i,0,nn)rep(j,i+1,nn){
            ans += (min(cnt[v[i]],cnt[v[j]])-b)*pow10[v[i]^v[j]];
        }
    }
    cout << ans.x << endl;
    return 0;
}