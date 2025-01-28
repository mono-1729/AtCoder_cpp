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


namespace interna1 {
// 内部実装
__int128_t __gcd(__int128_t a, __int128_t b) {
    if (a % b == 0)
        return b;
    return __gcd(b, a % b);
}
// こっちを呼ぶ。絶対値の GCD を返す。片方が 0 ならもう一方の絶対値。
__int128_t gcd(__int128_t a, __int128_t b) {
    if (b == 0)
        return (a >= 0 ? a : -a);
    return interna1::__gcd((a >= 0 ? a : -a), (b >= 0 ? b : -b));
}
// 約分
inline void simplify(__int128_t &num, __int128_t &den) {
    __int128_t d = interna1::gcd(num, den);
    num /= (den >= 0 ? d : -d);
    den /= (den >= 0 ? d : -d);
}
}; // namespace interna1




int main() {
    ll n; cin >> n;
    vector<ll> a(n);
    rep(i,0,n) cin >> a[i];
    rep(i,0,n-1)rep(j,0,n-1){
        if(a[i]*a[j+1] != a[i+1]*a[j]){
            cout << "No" << endl;
            return 0;
        }
    }
    cout << "Yes" << endl;
    return 0;
}