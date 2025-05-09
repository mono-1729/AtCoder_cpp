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
        vector<ll> a(n+2);
        rep(i,1,n+1) cin >> a[i];
        a[0] = n+1;
        a[n+1] = n+2;
        ll num0 = INF, num1 = 0, num2 = INF;
        rep(i,1,n+1){
            ll x0 = INF, x1 = INF, x2 = INF; 
            chmin(x1, num1+(a[i] == a[i-1] ? 0 : 1));
            if(i > 1) chmin(x1, num0+(a[i] == a[i-2] ? 0 : 1));
            chmin(x2, num1+1+(a[i+1] == a[i-1] ? 0 : 1));
            if(i > 1) chmin(x2, num0+1+(a[i+1] == a[i-2] ? 0 : 1));
            chmin(x0, num2+(a[i] == a[i-1] ? 0 : 1));
            swap(x0, num0);
            swap(x1, num1);
            swap(x2, num2);
            // cout << num0 << " " << num1 << " " << num2 << endl;
        }
        cout << min(num1,num0) << endl;
    }
    return 0;
}