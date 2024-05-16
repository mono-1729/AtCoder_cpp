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

ll powMod(ll x, ll n,ll mod) {
    if (n == 0) return 1 % mod;
    ll val = powMod(x, n / 2,mod);
    val *= val;
    val %= mod;
    if (n % 2 == 1) val *= x;
    return val % mod;
}
ll d = 32000;

void solve(){
    ll k;cin>>k;
    if(k%2==0) k/=2;
    k*=9;
    mint::set_mod(k);
    if(k%2==0 || k%5==0){
        cout<<-1<<endl;
        return;
    } 
    vector<mint>as(d+1);
    unordered_map<ll,ll>mp;
    as[0]=1;
    rep(i,0,d){
        as[i+1]=as[i]*10;
        mint h = as[i].inv();
        if(!mp.count(h.val())) mp[h.val()]=i;
    }
    mint x = as[d];
    ll s = 10%k;
    rep(i,0,d){
        if(mp.count(s)) {
            cout<<i*d+mp[s]+1<<endl;
            return;
        }
        s= (x*s).val();
    }
    cout<<-1<<endl;
    return;
}

int main() {
    ll t;cin>>t;
    rep(_,0,t)solve();
    return 0;
}