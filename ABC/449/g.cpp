#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
constexpr int MOD = 998244353;

// ---------------- ModInt ----------------
template< int mod >
struct ModInt {
  int x;

  ModInt() : x(0) {}
  ModInt(int64_t y) : x(y >= 0 ? y % mod : (mod - (-y) % mod) % mod) {}

  ModInt &operator+=(const ModInt &p) {
    if((x += p.x) >= mod) x -= mod;
    return *this;
  }
  ModInt &operator-=(const ModInt &p) {
    if((x += mod - p.x) >= mod) x -= mod;
    return *this;
  }
  ModInt &operator*=(const ModInt &p) {
    x = (int)(1LL * x * p.x % mod);
    return *this;
  }
  ModInt &operator/=(const ModInt &p) {
    *this *= p.inverse();
    return *this;
  }

  ModInt operator-() const { return ModInt(-x); }
  ModInt operator+(const ModInt &p) const { return ModInt(*this) += p; }
  ModInt operator-(const ModInt &p) const { return ModInt(*this) -= p; }
  ModInt operator*(const ModInt &p) const { return ModInt(*this) *= p; }
  ModInt operator/(const ModInt &p) const { return ModInt(*this) /= p; }

  bool operator==(const ModInt &p) const { return x == p.x; }
  bool operator!=(const ModInt &p) const { return x != p.x; }

  ModInt inverse() const {
    int a = x, b = mod, u = 1, v = 0, t;
    while(b > 0) {
      t = a / b;
      swap(a -= t * b, b);
      swap(u -= t * v, v);
    }
    return ModInt(u);
  }

  ModInt pow(int64_t n) const {
    ModInt ret(1), mul(x);
    while(n > 0) {
      if(n & 1) ret *= mul;
      mul *= mul;
      n >>= 1;
    }
    return ret;
  }

  friend ostream &operator<<(ostream &os, const ModInt &p) {
    return os << p.x;
  }
};

using modint = ModInt<MOD>;

// ---------------- FormalPowerSeries ----------------
template< typename T >
struct FormalPowerSeries : vector<T> {
  using vector<T>::vector;
  using P = FormalPowerSeries;
  using MULT = function<P(P, P)>;

  static MULT &get_mult() {
    static MULT mult = nullptr;
    return mult;
  }

  static void set_fft(MULT f) {
    get_mult() = f;
  }

  void shrink() {
    while(this->size() && this->back() == T(0)) this->pop_back();
  }

  P operator+(const P &r) const { return P(*this) += r; }
  P operator+(const T &v) const { return P(*this) += v; }
  P operator-(const P &r) const { return P(*this) -= r; }
  P operator-(const T &v) const { return P(*this) -= v; }
  P operator*(const P &r) const { return P(*this) *= r; }
  P operator*(const T &v) const { return P(*this) *= v; }
  P operator/(const P &r) const { return P(*this) /= r; }
  P operator%(const P &r) const { return P(*this) %= r; }

  P &operator+=(const P &r) {
    if(r.size() > this->size()) this->resize(r.size());
    for(int i = 0; i < (int)r.size(); i++) (*this)[i] += r[i];
    return *this;
  }

  P &operator+=(const T &r) {
    if(this->empty()) this->resize(1);
    (*this)[0] += r;
    return *this;
  }

  P &operator-=(const P &r) {
    if(r.size() > this->size()) this->resize(r.size());
    for(int i = 0; i < (int)r.size(); i++) (*this)[i] -= r[i];
    shrink();
    return *this;
  }

  P &operator-=(const T &r) {
    if(this->empty()) this->resize(1);
    (*this)[0] -= r;
    shrink();
    return *this;
  }

  P &operator*=(const T &v) {
    for(auto &x : *this) x *= v;
    return *this;
  }

  P &operator*=(const P &r) {
    if(this->empty() || r.empty()) {
      this->clear();
      return *this;
    }
    assert(get_mult() != nullptr);
    return *this = get_mult()(*this, r);
  }

  P &operator%=(const P &r) {
    return *this -= *this / r * r;
  }

  P operator-() const {
    P ret(this->size());
    for(int i = 0; i < (int)this->size(); i++) ret[i] = -(*this)[i];
    return ret;
  }

  P &operator/=(const P &r) {
    if(this->size() < r.size()) {
      this->clear();
      return *this;
    }
    int n = (int)this->size() - (int)r.size() + 1;
    return *this = (rev().pre(n) * r.rev().inv(n)).pre(n).rev(n);
  }

  P pre(int sz) const {
    return P(begin(*this), begin(*this) + min((int)this->size(), sz));
  }

  P operator>>(int sz) const {
    if((int)this->size() <= sz) return {};
    P ret(*this);
    ret.erase(ret.begin(), ret.begin() + sz);
    return ret;
  }

  P operator<<(int sz) const {
    P ret(*this);
    ret.insert(ret.begin(), sz, T(0));
    return ret;
  }

  P rev(int deg = -1) const {
    P ret(*this);
    if(deg != -1) ret.resize(deg, T(0));
    reverse(begin(ret), end(ret));
    return ret;
  }

  P diff() const {
    int n = (int)this->size();
    P ret(max(0, n - 1));
    for(int i = 1; i < n; i++) ret[i - 1] = (*this)[i] * T(i);
    return ret;
  }

  P integral() const {
    int n = (int)this->size();
    P ret(n + 1);
    ret[0] = T(0);
    for(int i = 0; i < n; i++) ret[i + 1] = (*this)[i] / T(i + 1);
    return ret;
  }

  P inv(int deg = -1) const {
    assert((*this)[0] != T(0));
    int n = (int)this->size();
    if(deg == -1) deg = n;
    P ret({T(1) / (*this)[0]});
    for(int i = 1; i < deg; i <<= 1) {
      ret = (ret + ret - ret * ret * pre(i << 1)).pre(i << 1);
    }
    return ret.pre(deg);
  }

  P log(int deg = -1) const {
    assert((*this)[0] == T(1));
    int n = (int)this->size();
    if(deg == -1) deg = n;
    return (diff() * inv(deg)).pre(deg - 1).integral();
  }

  P exp(int deg = -1) const {
    assert((*this)[0] == T(0));
    int n = (int)this->size();
    if(deg == -1) deg = n;
    P ret({T(1)});
    for(int i = 1; i < deg; i <<= 1) {
      ret = (ret * (pre(i << 1) + T(1) - ret.log(i << 1))).pre(i << 1);
    }
    return ret.pre(deg);
  }

  P pow(int64_t k, int deg = -1) const {
    int n = (int)this->size();
    if(deg == -1) deg = n;
    for(int i = 0; i < n; i++) {
      if((*this)[i] != T(0)) {
        T revv = T(1) / (*this)[i];
        P C(*this * revv);
        P D(n - i);
        for(int j = i; j < n; j++) D[j - i] = C[j];
        D = (D.log() * k).exp() * (*this)[i].pow(k);
        P E(deg);
        if(1LL * i * k >= deg) return E;
        ll S = 1LL * i * k;
        for(int j = 0; j < (int)D.size() && j + S < deg; j++) E[j + S] = D[j];
        return E;
      }
    }
    return P(deg, T(0));
  }
};

using FPS = FormalPowerSeries<modint>;

// ---------------- NTT ----------------
void ntt(vector<modint> &a, bool invert) {
  int n = (int)a.size();

  for(int i = 1, j = 0; i < n; i++) {
    int bit = n >> 1;
    for(; j & bit; bit >>= 1) j ^= bit;
    j ^= bit;
    if(i < j) swap(a[i], a[j]);
  }

  for(int len = 2; len <= n; len <<= 1) {
    modint wlen = modint(3).pow((MOD - 1) / len);
    if(invert) wlen = wlen.inverse();

    for(int i = 0; i < n; i += len) {
      modint w = 1;
      for(int j = 0; j < len / 2; j++) {
        modint u = a[i + j];
        modint v = a[i + j + len / 2] * w;
        a[i + j] = u + v;
        a[i + j + len / 2] = u - v;
        w *= wlen;
      }
    }
  }

  if(invert) {
    modint inv_n = modint(n).inverse();
    for(auto &x : a) x *= inv_n;
  }
}

FPS multiply_fps(FPS a, FPS b) {
  if(a.empty() || b.empty()) return {};
  int need = (int)a.size() + (int)b.size() - 1;
  int n = 1;
  while(n < need) n <<= 1;

  vector<modint> fa(n), fb(n);
  for(int i = 0; i < (int)a.size(); i++) fa[i] = a[i];
  for(int i = 0; i < (int)b.size(); i++) fb[i] = b[i];

  ntt(fa, false);
  ntt(fb, false);
  for(int i = 0; i < n; i++) fa[i] *= fb[i];
  ntt(fa, true);

  FPS res(need);
  for(int i = 0; i < need; i++) res[i] = fa[i];
  return res;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  FPS::set_fft(multiply_fps);

  ll N, M;
  cin >> N >> M;

  FPS base(N + 1, modint(0));
  for (int i = 0; i <= 9 && i <= N; i++) base[i] = 1;

  FPS A = base.pow(M - 1, (int)N + 1);

  FPS B(N + 1, modint(1));
  A = A * B;

  modint ans = 0;
  for (ll i = N; i >= 0; i -= 9) {
    if (i < (ll)A.size()) ans += A[(int)i];
  }

  ll bad = N / 9;
  ans -= modint(bad);

  cout << ans << '\n';
  return 0;
}