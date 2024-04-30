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

using mint = modint;

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
ll d = 32000;

int solve(){
    ll p,a,b,s,g;cin>>p>>a>>b>>s>>g;
    mint::set_mod(p);
    if(a==0){
        if(s==g) return 0;
        else if(b==g) return 1;
        else return -1;
    }
    vector<mint> as(d+1),bs(d+1);
    unordered_map<ll,ll> mp;
    as[0]=1,bs[0]=0;
    rep(i,0,d){
        as[i+1]=as[i]*a;
        bs[i+1]=bs[i]*a+b;
        mint h = (g-bs[i])/as[i];
        if(!mp.count(h.val())) mp[h.val()]=i;
    }

    mint x = as[d],y = bs[d];
    rep(i,0,d){
        if(mp.count(s)) return i*d+mp[s];
        s= (x*s+y).val();
    }
    return -1;

}

int main() {
    ll t;cin>>t;
    rep(_,0,t) cout<<solve()<<endl;
    return 0;
}