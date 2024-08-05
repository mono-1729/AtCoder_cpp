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

int main() {
    ll n; cin >> n;
    vector<ll> p_(n), q_(n);
    rep(i,0,n) cin >> p_[i];
    rep(i,0,n) cin >> q_[i];
    vector<ll> p(n), q(n);
    rep(i,0,n) p[p_[i]-1] = i+1;
    rep(i,0,n) q[q_[i]-1] = i+1;
    vector<vector<int>> a(n, vector<int>(n));
    rep(i,0,n){
        rep(j,0,n){
            ll num = p[i]+q[j];
            if(num > n) a[i][j] = 1;
            else a[i][j] = 0;
        }
    }
    rep(i,0,n){
        rep(j,0,n){
            cout << a[i][j];
        }
        cout << endl;
    }
    // rep(i,0,n){
    //     rep(j,0,n){
    //         bool c = a[i] < a[j];
    //         if(c != p[i] < p[j]){
    //             cout << "NO" << endl;
    //             return 0;
    //         }
    //     }
    // }
    // vector<vector<int>> b(n, vector<int>(n));   
    // rep(i,0,n){
    //     rep(j,0,n){
    //         b[i][j] = a[j][i];
    //     }
    // }
    // rep(i,0,n){
    //     rep(j,0,n){
    //         bool c = b[i] < b[j];
    //         if(c != q[i] < q[j]){
    //             cout << "N2" << endl;
    //             return 0;
    //         }
    //     }
    //     cout << endl;
    // }
    return 0;
}