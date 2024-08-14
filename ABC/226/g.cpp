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
    ll t; cin >> t;
    while(t--){
        vector<ll> a(6,0), b(6,0);
        rep(i,1,6) cin >> b[i];
        rep(i,1,6) cin >> a[i];
        ll num;
        num = min(a[5], b[5]);
        a[5] -= num; b[5] -= num;
        num = min(a[4], b[4]);
        a[4] -= num; b[4] -= num;
        num = min(a[5], b[4]);
        a[5] -= num; b[4] -= num; a[1] += num; 
        num = min(a[3], b[3]);
        a[3] -= num; b[3] -= num;
        num = min(a[5], b[3]);
        a[5] -= num; b[3] -= num; a[2] += num;
        num = min(a[4], b[3]);
        a[4] -= num; b[3] -= num; a[1] += num;
        num = min(a[5], b[2]);
        a[5] -= num; b[2] -= num; a[3] += num;
        num = min(a[4], b[2]);
        a[4] -= num; b[2] -= num; a[2] += num;
        num = min(a[3], b[2]);
        a[3] -= num; b[2] -= num; a[1] += num;
        num = min(a[2], b[2]);
        a[2] -= num; b[2] -= num;
        num = min(a[5], b[1]);
        a[5] -= num; b[1] -= num; a[4] += num;
        num = min(a[4], b[1]);
        a[4] -= num; b[1] -= num; a[3] += num;
        num = min(a[3], b[1]);
        a[3] -= num; b[1] -= num; a[2] += num;
        num = min(a[2], b[1]);
        a[2] -= num; b[1] -= num; a[1] += num;
        num = min(a[1], b[1]);
        a[1] -= num; b[1] -= num;
        if(b[1]+b[2]+b[3]+b[4]+b[5] == 0) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
    return 0;
}