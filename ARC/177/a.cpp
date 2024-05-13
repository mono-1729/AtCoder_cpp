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
    ll a,b,c,d,e,f;cin>>a>>b>>c>>d>>e>>f;
    ll n;cin>>n;
    vector<ll> x(n);
    rep(i,0,n)cin>>x[i];
    rep(i,0,n){
        ll tmp;
        ll num = x[i];
        tmp = min(f*500,(num/500)*500);
        num -= tmp;
        f -= tmp/500;
        tmp = min(e*100,(num/100)*100);
        num -= tmp;
        e -= tmp/100;
        tmp = min(d*50,(num/50)*50);
        num -= tmp;
        d -= tmp/50;
        tmp = min(c*10,(num/10)*10);
        num -= tmp;
        c -= tmp/10;
        tmp = min(b*5,(num/5)*5);
        num -= tmp;
        b -= tmp/5;
        tmp = min(a*1,(num/1)*1);
        num -= tmp;
        a -= tmp/1;
        if(num != 0){
            cout<<"No"<<endl;
            return 0;
        }
    }
    cout<<"Yes"<<endl;
    return 0;
}