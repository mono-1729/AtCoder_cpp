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
    ll t;cin>>t;
    mint div2 = powMod(2,MOD-2);
    rep(_,0,t){
        ll a1,a2,a3;cin>>a1>>a2>>a3;
        if(a1<a2)swap(a1,a2);
        mint p1 = powMod(10,a1);
        mint p1m = powMod(10,a1-1);
        mint p2 = powMod(10,a2);
        mint p2m = powMod(10,a2-1);
        if(max(a1,a2) == a3){
            mint ans = (p1-p1m)*(p2-p2m);
            ans-=(p2-p2m)*(p2+p2m-1)*div2;
            if(a1 == a2)ans+=(p1m)*(p1m-1)*div2;
            cout<<ans.val()<<endl;
        }
        else if(max(a1,a2)+1 == a3){
            mint ans = (p2-p2m)*(p2+p2m-1)*div2;
            if(a1 == a2)ans-=(p1m)*(p1m-1)*div2;
            cout<<ans.val()<<endl;
        }
        else{
            cout<<0<<endl;
        }
    }
    return 0;
}