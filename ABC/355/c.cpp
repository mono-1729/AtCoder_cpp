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
    ll n,t;cin>>n>>t;
    vector<ll> row(n,0),col(n,0);
    ll naname1 = 0, naname2 = 0;
    rep(i,1,t+1){
        ll a;cin>>a;
        a--;
        row[a/n]++;
        col[a%n]++;
        if(a/n == a%n) naname1++;
        if(a/n == n-1-a%n) naname2++;
        if(row[a/n] == n || col[a%n] == n){
            cout << i << endl;
            return 0;
        }
        if(naname1 == n || naname2 == n){
            cout << i << endl;
            return 0;
        }
    }
    cout << -1 << endl;
    return 0;
}