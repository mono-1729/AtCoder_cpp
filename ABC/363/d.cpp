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

long long TEN(int x) { return x == 0 ? 1 : TEN(x - 1) * 10; }

int main() {
  long long N;
  cin >> N;
  if (N == 1) {
    cout << 0 << endl;
    return 0;
  }
  N--;
  for (int d = 1;; d++) {
    int x = (d + 1) / 2;
    if (N <= 9 * TEN(x - 1)) {
      string S = to_string(TEN(x - 1) + N - 1);
      S.resize(d, ' ');
      for (int i = x; i < d; i++) S[i] = S[d - 1 - i];
      cout << S << endl;
      return 0;
    } else {
      N -= 9 * TEN(x - 1);
    }
  }
}