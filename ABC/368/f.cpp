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
    vector<ll> a(n);
    rep(i,0,n) cin >> a[i];
    vector<ll> grundy(100005);
    grundy[1] = 0;
    ll ans = 0;
    rep(i,2,100005){
        unordered_set<ll> s, t;
        rep(j,1,sqrt((double)i)+1){
            if(i%j == 0){
                if(j != i)s.insert(grundy[j]);
                if(i/j != i)s.insert(grundy[i/j]);
            }
        }
        ll g = 0;
        while(s.count(g)){
            g++;
        }
        grundy[i] = g;
    }
    rep(i,0,n){
        ans ^= grundy[a[i]];
    }
    if(ans){
        cout << "Anna" << endl;
    }else{
        cout << "Bruno" << endl;
    }
    return 0;
}