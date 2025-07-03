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
        ll m, k; cin >> m >> k;
        if(k%2 == 1){
            cout << "Yes" << endl;
            cout << k/2+1 << endl;
            rep(i,0,k/2+1) cout << i << " ";
            cout << endl;
        }else if(k == m){
            cout << "Yes" << endl;
            cout << m << endl;
            rep(i,0,m) cout << i << " ";
            cout << endl;
        }else if(k >= 6){
            cout << "Yes" << endl;
            cout << k/2 << endl;
            cout << 0 << " ";
            rep(i,2,k/2+1) cout << i << " ";
            cout << endl;
        }else if(k == 4 && m%4 == 0){
            cout << "Yes" << endl;
            cout << 3 << endl;
            cout << 0 << " " << m/2 << " " << m/4 << endl;
        }else if(k == 2 && m%2 == 0){
            cout << "Yes" << endl;
            cout << 2 << endl;
            cout << 0 << " " << m/2 << endl;
        }else cout << "No" << endl;
    }
    return 0;
}