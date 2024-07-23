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
    if(__popcount(n) == 1){
        cout << "No" << endl;
        return 0;
    }
    cout << "Yes" << endl;
    if(n == 3){
        cout << "1 2" << endl << "2 3" << endl << "3 4" << endl << "4 5" << endl << "5 6" << endl;
        return 0;
    }
    ll num;
    rrep(i,20,0)if(n>>i & 1){
        num = (1 << i) -1;
        break;
    }
    rep(i,1,num){
        cout << i << " " << i+1 << endl;
        cout << n+i << " " << n+i+1 << endl; 
    }
    cout << num << " " << n+1 << endl;
    if(n == num) return 0;
    cout << n+num+1 << " " << num+2 << endl;
    cout << num+2 << " " << 1 << endl;
    cout << 1 << " " << num+1 << endl;
    cout << num+1 << " " << n+num+2 << endl;
    rep(i,num+3,n+1){
        int l = (i%4 == 0 || i%4 == 3)? num+1:num+2;
        int r = ((i-num-1)/2)*2;
        cout << l << " " << i << endl;
        cout << r << " " << i+n << endl;
    }
    return 0;
}