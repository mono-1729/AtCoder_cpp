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
    ll n,s;cin>>n>>s;
    ll ans = INF;
    if(n == s) chmin(ans,n+1);
    rep(i,2,sqrt((double)n)+2){
        ll num = 0;
        ll tmp = n;
        while(tmp){
            num += tmp%i;
            tmp /= i;
        }
        if(num == s){
            cout<<i<<endl;
            return 0;
        }
    }
    rep(i,1,sqrt((double)n)+2){
        ll s1=i,s2 = s-i;
        if(s2 < 0)continue;
        if(n < s2)continue;
        if((n-s2)%s1 == 0 && (n-s2)/s1 > max(s1,s2)){
            chmin(ans,(n-s2)/s1);
        }
    }
    if(ans == INF)cout<<-1<<endl;
    else cout<<ans<<endl;
    return 0;
}