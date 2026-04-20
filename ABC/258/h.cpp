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

template< class T >
struct Matrix {
    vector< vector< T > > A;

    Matrix() {}

    Matrix(size_t n, size_t m) : A(n, vector< T >(m, 0)) {}

    Matrix(size_t n) : A(n, vector< T >(n, 0)) {};

    size_t height() const {
        return (A.size());
    }

    size_t width() const {
        return (A[0].size());
    }

    inline const vector< T > &operator[](ll k) const {
        return (A.at(k));
    }

    inline vector< T > &operator[](ll k) {
        return (A.at(k));
    }

    static Matrix I(size_t n) {
        Matrix mat(n);
        for(ll i = 0; i < n; i++) mat[i][i] = 1;
        return (mat);
    }

    Matrix &operator+=(const Matrix &B) {
        size_t n = height(), m = width();
        assert(n == B.height() && m == B.width());
        for(ll i = 0; i < n; i++)for(ll j = 0; j < m; j++)(*this)[i][j] += B[i][j];
        return (*this);
    }

    Matrix &operator-=(const Matrix &B) {
        size_t n = height(), m = width();
        assert(n == B.height() && m == B.width());
        for(ll i = 0; i < n; i++)for(ll j = 0; j < m; j++)(*this)[i][j] -= B[i][j];
        return (*this);
    }

    Matrix &operator*=(const Matrix &B) {
        size_t n = height(), m = B.width(), p = width();
        assert(p == B.height());
        vector< vector< T > > C(n, vector< T >(m, 0));
        for(ll i = 0; i < n; i++)for(ll j = 0; j < m; j++)for(ll k = 0; k < p; k++)C[i][j] = (C[i][j] + (*this)[i][k] * B[k][j]);
        A.swap(C);
        return (*this);
    }

    Matrix &operator^=(long long k) {
        Matrix B = Matrix::I(height());
        while(k > 0) {
            if(k & 1) B *= *this;
            *this *= *this;
            k >>= 1LL;
        }
        A.swap(B.A);
        return (*this);
    }

    Matrix operator+(const Matrix &B) const {
        return (Matrix(*this) += B);
    }

    Matrix operator-(const Matrix &B) const {
        return (Matrix(*this) -= B);
    }

    Matrix operator*(const Matrix &B) const {
        return (Matrix(*this) *= B);
    }

    Matrix operator^(const long long k) const {
        return (Matrix(*this) ^= k);
    }

    friend ostream &operator<<(ostream &os, Matrix &p) {
        size_t n = p.height(), m = p.width();
        for(ll i = 0; i < n; i++) {
            os << "[";
            for(ll j = 0; j < m; j++) {
                os << p[i][j] << (j + 1 == m ? "]\n" : ",");
            }
        }
        return (os);
    }

    // 行列式
    T determinant() {
        Matrix B(*this);
        assert(width() == height());
        T ret = 1;
        for(ll i = 0; i < width(); i++) {
            ll idx = -1;
            for(ll j = i; j < width(); j++) {
                if(B[j][i] != 0) idx = j;
            }
            if(idx == -1) return (0);
            if(i != idx) {
                ret *= -1;
                swap(B[i], B[idx]);
            }
            ret *= B[i][i];
            T vv = B[i][i];
            for(ll j = 0; j < width(); j++) {
                B[i][j] /= vv;
            }
            for(ll j = i + 1; j < width(); j++) {
                T a = B[j][i];
                for(ll k = 0; k < width(); k++) {
                    B[j][k] -= B[i][k] * a;
                }
            }
        }
        return (ret);
    }
    ll rank() {
        vector<vector<T>> B = A;
        ll n = B.size();
        ll m = B[0].size();
        rep(i,0,n){
            ll id = i;
            rep(j,i+1,n) if(B[id] < B[j]) id = j;
            swap(B[i], B[id]);
            ll r = -1;
            rep(j,i,m) if(B[i][j]){
                r = j;
                break;
            }
            if(r == -1) return i;
            rep(j,0,n){
                if(i == j) continue;
                if(B[j][r]){
                    rep(k,i,m) B[j][k] ^= B[i][k];
                }
            }
        }
        return n;
    }
};

int main() {
    ll n, s; cin >> n >> s;
    vector<ll> a(n);
    rep(i,0,n) cin >> a[i];
    Matrix<mint> p(1,2), no(2,2), yes(2,2);
    p[0] = {1,0};
    no[0] = {0,1}, no[1] = {1,0};
    yes[0] = {1,1}, yes[1] = {1,0};
    vector<Matrix<mint>> dp(60);
    dp[0] = yes;
    rep(i,1,60) dp[i] = dp[i-1]*dp[i-1];
    ll pre = 1;
    rep(i,0,n){
        Matrix<mint> x = Matrix<mint>::I(2);
        ll cnt = a[i]-pre;
        rep(j,0,60) if(cnt>>j&1) x *= dp[j];
        p *= x;
        p *= no;
        pre = a[i]+1;
    }
    Matrix<mint> x = Matrix<mint>::I(2);
    ll cnt = s-pre;
    rep(j,0,60) if(cnt>>j&1) x *= dp[j];
    p *= x;
    cout << p[0][0].val() << endl;
    return 0;
}