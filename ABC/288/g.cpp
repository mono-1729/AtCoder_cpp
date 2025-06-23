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
    ll n; cin >> n;
    vector<ll> pow3(n+1,1);
    rep(i,0,n) pow3[i+1] = pow3[i]*3;
    vector<ll> a(pow3[n]);
    rep(i,0,pow3[n]) cin >> a[i];
    rep(i,0,n){
        rep(bit,0,pow3[n]){
            if((bit/pow3[i])%3 == 0){
                ll bit1 = bit+pow3[i];
                ll bit2 = bit1+pow3[i];
                ll n0 = a[bit1]-a[bit2];
                ll n1 = a[bit]+a[bit2]-a[bit1];
                ll n2 = a[bit1]-a[bit];
                a[bit] = n0;
                a[bit1] = n1;
                a[bit2] = n2;
            }
        }
    }
    for(auto x: a) cout << x << " ";
    cout << endl;
    return 0;
}