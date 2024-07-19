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
};

int main() {
    ll n, x_, y_; cin >> n >> x_ >> y_;
    mint x = mint(x_)/100, y = mint(y_)/100;
    string c; cin >> c;
    c = c + c;
    Matrix<mint> a(24,24), dp(24,1);
    dp[0][0] = 1;
    rep(i,0,24){
        mint sum = 1;
        rep(j,i,i+24){
            if(c[j] == 'T'){
                a[(j+1)%24][i] = sum * x;
                sum *= (1-x);
            }
            if(c[j] == 'A'){
                a[(j+1)%24][i] = sum * y;
                sum *= (1-y);
            }
        }
        sum = 1-sum;
        sum = sum.inv();
        rep(j,0,24) a[j][i] *= sum;
    }
    dp = (a^n)*dp;
    mint ans = 0;
    rep(i,0,24){
        if(c[i+23] == 'A') ans += dp[i][0];
    }
    cout << ans.val() << endl;
    return 0;
}