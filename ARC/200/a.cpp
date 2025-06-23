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
        vector<ll> a(n), b(n);
        rep(i,0,n) cin >> a[i];
        rep(i,0,n) cin >> b[i];
        ll f = 1;
        rep(i,1,n){
            if(a[0]*b[i]!= a[i]*b[0]){
                f = 0;
                cout << "Yes" << endl;
                vector<ll> ans(n,0);
                ans[0] = a[i]+b[i];
                ans[i] = a[0]+b[0];
                if(a[0]*b[i] > a[i]*b[0]) ans[i] *= -1;
                else ans[0] *= -1;

                for(auto x: ans) cout << x << " ";
                cout << endl;
            }
        }
        if(f) cout << "No" << endl;
    }
    return 0;
}