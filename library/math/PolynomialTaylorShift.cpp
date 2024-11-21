#include <bits/stdc++.h>
#include "atcoder/convolution.hpp"
#include "atcoder/modint.hpp"
using namespace std;
using namespace atcoder;
using mint = modint998244353;

// Binomial coefficient
const int MOD = 998244353;
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
    long long N, c;
    cin >> N >> c;
    vector<mint> a(N);
    for (int i = 0; i < N; ++i) {
        long long v;
        cin >> v;
        a[i] = v;
    }
    
    vector<mint> res = PolynomialTaylorShift(a, c);
    for (int i = 0; i < N; ++i) cout << res[i].val() << " ";
    cout << endl;
}