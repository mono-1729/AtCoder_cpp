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


__int128 powM(__int128 x, __int128 n, __int128 mod) {
    if (n == 0) return 1 % mod;
    __int128 val = powM(x, n / 2, mod);
    val *= val;
    val %= mod;
    if (n % 2 == 1) val *= x;
    return val % mod;
}



// montgomery modint (MOD < 2^62, MOD is odd)
struct MontgomeryModInt64 {
    using mint = MontgomeryModInt64;
    using u64 = uint64_t;
    using u128 = __uint128_t;
    
    // static menber
    static u64 MOD;
    static u64 INV_MOD;  // INV_MOD * MOD ≡ 1 (mod 2^64)
    static u64 T128;  // 2^128 (mod MOD)
    
    // inner value
    u64 val;
    
    // constructor
    MontgomeryModInt64() : val(0) { }
    MontgomeryModInt64(long long v) : val(reduce((u128(v) + MOD) * T128)) { }
    u64 get() const {
        u64 res = reduce(val);
        return res >= MOD ? res - MOD : res;
    }
    
    // mod getter and setter
    static u64 get_mod() { return MOD; }
    static void set_mod(u64 mod) {
        assert(mod < (1LL << 62));
        assert((mod & 1));
        MOD = mod;
        T128 = -u128(mod) % mod;
        INV_MOD = get_inv_mod();
    }
    static u64 get_inv_mod() {
        u64 res = MOD;
        for (int i = 0; i < 5; ++i) res *= 2 - MOD * res;
        return res;
    }
    static u64 reduce(const u128 &v) {
        return (v + u128(u64(v) * u64(-INV_MOD)) * MOD) >> 64;
    }
    
    // arithmetic operators
    mint operator - () const { return mint() - mint(*this); }
    mint operator + (const mint &r) const { return mint(*this) += r; }
    mint operator - (const mint &r) const { return mint(*this) -= r; }
    mint operator * (const mint &r) const { return mint(*this) *= r; }
    mint operator / (const mint &r) const { return mint(*this) /= r; }
    mint& operator += (const mint &r) {
        if ((val += r.val) >= 2 * MOD) val -= 2 * MOD;
        return *this;
    }
    mint& operator -= (const mint &r) {
        if ((val += 2 * MOD - r.val) >= 2 * MOD) val -= 2 * MOD;
        return *this;
    }
    mint& operator *= (const mint &r) {
        val = reduce(u128(val) * r.val);
        return *this;
    }
    mint& operator /= (const mint &r) {
        *this *= r.inv();
        return *this;
    }
    mint inv() const { return pow(MOD - 2); }
    mint pow(u128 n) const {
        mint res(1), mul(*this);
        while (n > 0) {
            if (n & 1) res *= mul;
            mul *= mul;
            n >>= 1;
        }
        return res;
    }

    // other operators
    bool operator == (const mint &r) const {
        return (val >= MOD ? val - MOD : val) == (r.val >= MOD ? r.val - MOD : r.val);
    }
    bool operator != (const mint &r) const {
        return (val >= MOD ? val - MOD : val) != (r.val >= MOD ? r.val - MOD : r.val);
    }
    friend istream& operator >> (istream &is, mint &x) {
        long long t;
        is >> t;
        x = mint(t);
        return is;
    }
    friend ostream& operator << (ostream &os, const mint &x) {
        return os << x.get();
    }
    friend mint modpow(const mint &r, long long n) {
        return r.pow(n);
    }
    friend mint modinv(const mint &r) {
        return r.inv();
    }
};

typename MontgomeryModInt64::u64
MontgomeryModInt64::MOD, MontgomeryModInt64::INV_MOD, MontgomeryModInt64::T128;

// Miller-Rabin
bool MillerRabin(long long N, vector<long long> A) {
    using mint = MontgomeryModInt64;
    mint::set_mod(N);
    
    long long s = 0, d = N - 1;
    while (d % 2 == 0) {
        ++s;
        d >>= 1;
    }
    for (auto a : A) {
        if (N <= a) return true;
        mint x = mint(a).pow(d);
        if (x != 1) {
            long long t;
            for (t = 0; t < s; ++t) {
                if (x == N - 1) break;
                x *= x;
            }
            if (t == s) return false;
        }
    }
    return true;
}

bool is_prime(long long N) {
    if (N <= 1) return false;
    else if (N == 2) return true;
    else if (N % 2 == 0) return false;
    else if (N < 4759123141LL)
        return MillerRabin(N, {2, 7, 61});
    else
        return MillerRabin(N, {2, 325, 9375, 28178, 450775, 9780504, 1795265022});
}

__int128 powX(__int128 x, __int128 n, __int128 mod) {
    if (n == 0) return 1 % mod;
    __int128 val = powX(x, n / 2, mod);
    val *= val;
    val %= mod;
    if (n % 2 == 1) val *= x;
    return val % mod;
}

ll PrimitiveRoot(__int128 m) {
  __int128 divs[30] = {};
  divs[0] = 2;
  int cnt = 1;
  __int128 x = (m - 1) / 2;
  while (x % 2 == 0) x /= 2;
  for (__int128 i = 3; i * i <= x; i += 2) {
    if (x % i == 0) {
      divs[cnt++] = i;
      while (x % i == 0) {
        x /= i;
      }
    }
  }
  if (x > 1) {
    divs[cnt++] = x;
  }
  for (__int128 g = 2;; g++) {
    bool ok = true;
    for (int i = 0; i < cnt; i++) {
      if (powX(g, (m - 1) / divs[i], m) == 1) {
        ok = false;
        break;
      }
    }
    if (ok) return g;
  }
}

int main() {
    ll t; cin >> t;
    random_device seed_gen;
    mt19937 engine(seed_gen());
    while(t--){
        ll n; cin >> n;
        while(true){
            ll k = engine()%1000000+1;
            if(is_prime(k*n+1)){
                ll x = PrimitiveRoot(k*n+1);
                cout << (ll)powM(x, k, k*n+1) << " " << k*n+1 << endl;
                break;
            }
        }
    }
    return 0;
}