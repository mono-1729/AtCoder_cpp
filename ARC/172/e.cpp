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
constexpr ll MOD = 1000000000;
//constexpr ll MOD = 998244353;
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

int main() {
    ll q; cin >> q;
    vector<ll> pow10(10,1);
    rep(i,0,10)pow10[i+1] = pow10[i]*10;
    while(q--){
        ll x; cin >> x;
        ll num;
        rep(i,1,100){
            if(powMod(i,i,100) == x%100) num = i;
        }
        rep(i,3,10){
            rep(j,0,10){
                if(powMod(num+pow10[i-1]*j,num+pow10[i-1]*j,pow10[i]) == x%pow10[i]){
                    num += pow10[i-1]*j;
                    break;
                }
            }
        }
        cout << num << endl;
    }
    return 0;
}