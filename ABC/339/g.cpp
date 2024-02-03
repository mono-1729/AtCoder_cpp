#include <bits/stdc++.h>
#include <unordered_map>
#include <stdlib.h>
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
template <ll MOD> class modint {
    ll val;
    static vector<modint<MOD>> factorial_vec;
public:
    ll get() const { return (ll)val; }
    // コンストラクタ
    modint(ll x = 0){
        val = x % MOD;
        if(val < 0) x += MOD;
    }

    // 入出力ストリーム
    friend constexpr istream &operator>>(istream &is, modint<MOD> &x){
        ll y; is >> y;
        x = y;
        return is;
    }
    friend constexpr ostream &operator<<(ostream &os, const modint<MOD> &x){
        return os << x.val;
    }

    // 算術演算子
    modint<MOD> operator -(){return modint<MOD>(-val);}
    modint<MOD> operator +(const modint<MOD> &r) const { return modint<MOD>(*this) += r; }
    modint<MOD> operator -(const modint<MOD> &r) const { return modint<MOD>(*this) -= r; }
    modint<MOD> operator *(const modint<MOD> &r) const { return modint<MOD>(*this) *= r; }
    modint<MOD> operator /(const modint<MOD> &r) const { return modint<MOD>(*this) /= r; }

    // 代入演算子
    modint<MOD> &operator +=(const modint<MOD> &r){
        val += r.val;
        if(val >= MOD) val -= MOD;
        return *this;
    }
    modint<MOD> &operator -=(const modint<MOD> &r){
        if(val < r.val) val += MOD;
        val -= r.val;
        return *this;
    }
    modint<MOD> &operator *=(const modint<MOD> &r){
        val = val*r.val%MOD;
        if(val < 0) val += MOD;
        return *this;
    }
    modint<MOD> &operator /=(const modint<MOD> &r){
        *this *= inv(r);
        return *this;
    }

    //等価比較演算子
    bool operator ==(const modint<MOD>& r){return this -> val == r.val;}
    bool operator !=(const modint<MOD>& r){return this -> val != r.val;}
    bool operator <(const modint<MOD>& r){return this -> val < r.val;}
    bool operator <=(const modint<MOD>& r){return this -> val <= r.val;}
    bool operator >(const modint<MOD>& r){return this -> val > r.val;}
    bool operator >=(const modint<MOD>& r){return this -> val >= r.val;}

    // 累乗
    static modint<MOD> modpow(modint<MOD> num, ll exp){
        if(!exp) return modint<MOD>(1); // 0乗
        modint<MOD> ret(1);
        modint<MOD> tmp = num;
        while(exp){
            if(exp&1) ret *= tmp;
            tmp *= tmp;
            exp >>= 1;
        }
        return ret;
    }

    // 逆元
    static modint<MOD> inv(modint<MOD> num){
        return modpow(num, MOD-2);
    }

    // 階乗
    static modint<MOD> factorial(ll n){
        modint<MOD> ret(1);
        if(n == 0) return ret;
        if((ll)factorial_vec.size() >= n) return factorial_vec[n-1];
        ret = factorial(n-1)*n;
        factorial_vec.push_back(ret);
        return ret;
    }

    // コンビネーション
    static modint<MOD> combination(ll n, ll r){
        return factorial(n) / factorial(r) / factorial(n-r);
    }

};

using mint = modint<MOD>;
template <ll MOD> vector<modint<MOD>> modint<MOD>::factorial_vec;

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

template <typename Key, typename Val>
struct HashMap {
  using u32 = uint32_t;
  using u64 = uint64_t;

  u32 cap, s;
  vector<Key> keys;
  vector<Val> vals;
  vector<bool> flag;
  u64 r;
  u32 shift;
  Val DefaultValue;

  static u64 rng() {
    u64 m = chrono::duration_cast<chrono::nanoseconds>(
                chrono::high_resolution_clock::now().time_since_epoch())
                .count();
    m ^= m >> 16;
    m ^= m << 32;
    return m;
  }

  void reallocate() {
    cap <<= 1;
    vector<Key> k(cap);
    vector<Val> v(cap);
    vector<bool> f(cap);
    u32 sh = shift - 1;
    for (int i = 0; i < (int)flag.size(); i++) {
      if (flag[i]) {
        u32 hash = (u64(keys[i]) * r) >> sh;
        while (f[hash]) hash = (hash + 1) & (cap - 1);
        k[hash] = keys[i];
        v[hash] = vals[i];
        f[hash] = 1;
      }
    }
    keys.swap(k);
    vals.swap(v);
    flag.swap(f);
    --shift;
  }

  explicit HashMap()
      : cap(8),
        s(0),
        keys(cap),
        vals(cap),
        flag(cap),
        r(rng()),
        shift(64 - __lg(cap)),
        DefaultValue(Val()) {}

  Val& operator[](const Key& i) {
    u32 hash = (u64(i) * r) >> shift;
    while (true) {
      if (!flag[hash]) {
        if (s + s / 4 >= cap) {
          reallocate();
          return (*this)[i];
        }
        keys[hash] = i;
        flag[hash] = 1;
        ++s;
        return vals[hash] = DefaultValue;
      }
      if (keys[hash] == i) return vals[hash];
      hash = (hash + 1) & (cap - 1);
    }
  }

  // exist -> return pointer of Val
  // not exist -> return nullptr
  const Val* find(const Key& i) const {
    u32 hash = (u64(i) * r) >> shift;
    while (true) {
      if (!flag[hash]) return nullptr;
      if (keys[hash] == i) return &(vals[hash]);
      hash = (hash + 1) & (cap - 1);
    }
  }

  // return vector< pair<const Key&, val& > >
  vector<pair<Key, Val>> enumerate() const {
    vector<pair<Key, Val>> ret;
    for (u32 i = 0; i < cap; ++i)
      if (flag[i]) ret.emplace_back(keys[i], vals[i]);
    return ret;
  }

  int size() const { return s; }

  // set default_value
  void set_default(const Val& val) { DefaultValue = val; }
};

/**
 * @brief Hash Map(可変長版)
 * @docs docs/data-structure/hash-map.md
 */

template <typename S, typename T>
struct DynamicFenwickTree {
  S N;
  HashMap<S, T> data;
  explicit DynamicFenwickTree() = default;
  explicit DynamicFenwickTree(S size) { N = size + 1; }

  void add(S k, T x) {
    for (++k; k < N; k += k & -k) data[k] += x;
  }

  // [0, k)
  T sum(S k) const {
    if (k < 0) return 0;
    T ret = T();
    for (; k > 0; k -= k & -k) {
      const T* p = data.find(k);
      ret += p ? *p : T();
    }
    return ret;
  }

  // [a, b)
  T sum(S a, S b) const { return sum(b) - sum(a); }

  T operator[](S k) const { return sum(k + 1) - sum(k); }

  S lower_bound(T w) {
    if (w <= 0) return 0;
    S x = 0;
    for (S k = 1 << __lg(N); k; k >>= 1) {
      if (x + k <= N - 1 && data[x + k] < w) {
        w -= data[x + k];
        x += k;
      }
    }
    return x;
  }
};

/**
 * @brief 動的Binary Indexed Tree
 * @docs docs/data-structure/dynamic-binary-indexed-tree.md
 */

template <typename T>
struct DynamicFenwickTree2D {
  using BIT = DynamicFenwickTree<int, T>;
  int N, M;
  vector<BIT*> bit;
  DynamicFenwickTree2D() = default;
  DynamicFenwickTree2D(int n, int m) : N(n + 1), M(m) {
    for (int _ = 0; _ < N; ++_) bit.push_back(new BIT(M));
  }
  
  void add(int i, int j, const T& x) {
    for (++i; i < N; i += i & -i) (*bit[i]).add(j, x);
  }

  // i = [0, n), j = [0, m)
  T sum(int n, int m) const {
    if (n < 0 || m < 0) return T();
    T ret = T();
    for (; n; n -= n & -n) ret += (*bit[n]).sum(m);
    return ret;
  }

  // i = [nl, nr), j = [ml, mr)
  T sum(int nl, int ml, int nr, int mr) const {
    T ret = T();
    while (nl != nr) {
      if (nl < nr) {
        ret += (*bit[nr]).sum(ml, mr);
        nr -= nr & -nr;
      } else {
        ret -= (*bit[nl]).sum(ml, mr);
        nl -= nl & -nl;
      }
    }
    return ret;
  }
};

/*
 * @brief 動的二次元Binary Indexed Tree
 */

int main() {
    ll n;cin>>n;
    vector<ll> a(n),b(n);
    rep(i,0,n){
        cin>>a[i];
        b[i]=a[i];
    }
    sort(b.begin(),b.end());
    b.erase(unique(b.begin(),b.end()),b.end());
    DynamicFenwickTree2D<ll> bit(n,b.size());
    rep(i,0,n){
        ll idx=lower_bound(b.begin(),b.end(),a[i])-b.begin();
        bit.add(i,idx,a[i]);
    }
    ll ans=0;
    ll q;cin>>q;
    rep(i,0,q){
        ll x,y,z;cin>>x>>y>>z;
        x^=ans;y^=ans;z^=ans;
        ll idx=upper_bound(b.begin(),b.end(),z)-b.begin();
        ans=bit.sum(x-1,0,y,idx);
        cout<<ans<<endl;
    }
    return 0;
}