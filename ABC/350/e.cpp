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
    cout<<fixed<<setprecision(15);
    ll n,a,x,y_;cin>>n>>a>>x>>y_;
    double y = 1.2*y_ ;
    unordered_map<ll,ll> check;
    unordered_map<ll,double> ans;
    check[0]=1;ans[0]=0;
    auto solve = [&](auto& solve, ll num)->double{
        if(check[num]) return ans[num];
        double m1 =solve(solve,num/a)+x;
        double m2 = y;
        rep(i,2,7)m2+=solve(solve,num/i)*0.2;
        check[num]=1;
        return ans[num] = min(m1,m2);
    };
    cout<<solve(solve, n)<<endl;
    
    return 0;
}