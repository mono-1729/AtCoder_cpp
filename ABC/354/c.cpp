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
    vector<tuple<ll,ll,ll>> ac(n);
    rep(i, 0, n){
        ll a, c;cin>>a>>c;
        ac[i] = {a,c,i+1};
    }
    sort(ac.begin(), ac.end(), [](auto a, auto b){
        return get<0>(a) > get<0>(b);
    });
    ll idx = 0;
    vector<ll> use(n+1,1);
    use[0]=0;
    ll minc = INF;
    while(idx < n){
        ll mc = INF;
        if(get<1>(ac[idx]) > minc) use[get<2>(ac[idx])] = 0;
        else chmin(mc, get<1>(ac[idx]));
        idx++;
 
        while(idx < n && get<0>(ac[idx]) == get<0>(ac[idx-1])){
            if(get<1>(ac[idx]) > minc) use[get<2>(ac[idx])] = 0;
            else chmin(mc, get<1>(ac[idx]));
            idx++;
        }
        chmin(minc, mc);
    }
    ll sum = 0;
    rep(i,0,n+1)if(use[i] == 1)sum++;
    cout<<sum<<endl;
    rep(i, 0, n+1){
        if(use[i] == 1){
            cout<<i<<" ";
        }
    }
    cout<<endl;
    return 0;
}