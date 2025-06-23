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
vector<ll> vec1 = {1, 7 ,97 ,997 ,9973 ,99991 ,999983 ,9999991 ,99999989 ,999999937 ,9999999967 ,99999999977 ,999999999989 ,9999999999971 ,99999999999973 ,999999999999989 ,9999999999999937 ,99999999999999997};
vector<ll> vec2 = {1, 5 ,89 ,991 ,9967 ,99989 ,999979 ,9999973 ,99999971 ,999999929 ,9999999943 ,99999999947 ,999999999961 ,9999999999863 ,99999999999971 ,999999999999947 ,9999999999999917 ,99999999999999977};
vector<ll> vec3 = {1, 3 ,83 ,983 ,9949 ,99971 ,999961 ,9999971 ,99999959 ,999999893 ,9999999929 ,99999999943 ,999999999959 ,9999999999799 ,99999999999959 ,999999999999883 ,9999999999999887 ,99999999999999961};


int main() {
    ll t; cin >> t;
    while(t--) {
        ll a1, a2, a3; cin >> a1 >> a2 >> a3;
        if(a1+a2 < a3){
            cout << "No" << endl;
            continue;
        }
        if(max(a1, a2) > a3){
            cout << "No" << endl;
            continue;
        }
        if(max(a1, a2) == a3){
            cout << "Yes" << endl;
            cout << 1;
            rep(i,0,a1-1) cout << 0;
            cout << " ";
            cout << 1;
            rep(i,0,a2-1) cout << 0;
            cout << endl;
            continue;
        }
        cout << "Yes" << endl;
        ll m = a1 + a2 - a3;
        cout << vec1[m]*vec2[a1-m] << " " << vec1[m]*vec3[a2-m] << endl;
    }
    return 0;
}