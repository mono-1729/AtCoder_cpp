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

ll powMod(ll x, ll n) {
    if (n == 0) return 1 % MOD;
    ll val = powMod(x, n / 2);
    val *= val;
    val %= MOD;
    if (n % 2 == 1) val *= x;
    return val % MOD;
}

int main() {
    ll t; cin >> t;
    while(t--){
        ll n; cin >> n;
        ll c1 = 0, c2 = 0, c3 = 0;
        rep(i,0,n){
            ll a, b, c; cin >> a >> b >> c;
            if(a+c <= b){
                c1 += a, c2 += c;
            }else{
                ll num1 = max(0LL, b-c), num2 = max(0LL, b-a);
                c1 += num1;
                c2 += num2;
                c3 += b-num1-num2;
            }
        }
        if(c1 > c2) swap(c1, c2);
        ll num = min(c2-c1, c3);
        c1 += num;
        c3 -= num;
        cout << c1+c3/2 << endl;
    }
    return 0;
}