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
    ll n;cin>>n;
    string ns = to_string(n);
    ll m = ns.size();
    vector<mint> num(60,n%MOD);
    vector<ll> num2(60,m);

    rep(i,1,60)num2[i] = (num2[i-1]+num2[i-1])%(MOD-1);
    rep(i,1,60){
        num[i] = num[i-1] +num[i-1]*powMod(10,num2[i-1]);
    }
    mint ans = 0;
    rep(i,0,60){
        if(n & (1LL<<i)){
            ans = ans*powMod(10,num2[i]) + num[i];
        }
    }
    cout << ans.val() << endl;
    // rep(i,0,60){
    //     cout << num[i].val() << " ";
    // }
    // cout << endl;
    // rep(i,0,60){
    //     cout << num2[i] << " ";
    // }
    return 0;
}