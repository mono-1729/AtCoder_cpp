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

template<class T> struct BiCoef {
    vector<T> fact_, inv_, finv_;
    constexpr BiCoef() {}
    constexpr BiCoef(int n) noexcept : fact_(n, 1), inv_(n, 1), finv_(n, 1) {
        init(n);
    }
    constexpr void init(int n) noexcept {
        fact_.assign(n, 1), inv_.assign(n, 1), finv_.assign(n, 1);
        for(int i = 2; i < n; i++){
            fact_[i] = fact_[i-1] * i;
            inv_[i] = -inv_[MOD%i] * (MOD/i);
            finv_[i] = finv_[i-1] * inv_[i];
        }
    }
    constexpr T com(int n, int k) const noexcept {
        if (n < k || n < 0 || k < 0) return 0;
        return fact_[n] * finv_[k] * finv_[n-k];
    }
    constexpr T fact(int n) const noexcept {
        if (n < 0) return 0;
        return fact_[n];
    }
    constexpr T inv(int n) const noexcept {
        if (n < 0) return 0;
        return inv_[n];
    }
    constexpr T finv(int n) const noexcept {
        if (n < 0) return 0;
        return finv_[n];
    }
};

// Polynomial Taylor Shift
// given: f(x), c
// find: coefficientss of f(x + c)
template<class mint> vector<mint> PolynomialTaylorShift(const vector<mint> &f, long long c) {
    int N = (int)f.size() - 1;
    BiCoef<mint> bc(N + 1);
    
    // convollution
    vector<mint> p(N + 1), q(N + 1);
    for (int i = 0; i <= N; ++i) {
        p[i] = f[i] * bc.fact(i);
        q[N - i] = mint(c).pow(i) * bc.finv(i);
    }
    vector<mint> pq = convolution(p, q);
    
    // find
    vector<mint> res(N + 1);
    for (int i = 0; i <= N; ++i) res[i] = pq[i + N] * bc.finv(i);
    return res;
}

int main() {
    ll p = 500005;
    ll n, m; cin >> n >> m;
    vector<mint> a(p);
    rep(i,0,n){
        ll x; cin >> x;
        a[x]++;
    }
    vector<mint> res = PolynomialTaylorShift(a, 1);
    mint ans = 0;
    rep(i,0,m){
        ll b; cin >> b;
        ans += res[b];
    }
    cout << ans.val() << endl;
    return 0;
}