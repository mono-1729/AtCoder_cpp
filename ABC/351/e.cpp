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
    vector<pll> xy(n);
    rep(i,0,n){
        ll x_,y_;cin>>x_>>y_;
        xy[i] = {x_+y_,x_-y_};
    }
    vector<ll> x0,y0,x1,y1;
    rep(i,0,n){
        auto [x,y] = xy[i];
        if(x%2==0){
            x0.push_back(x);
            y0.push_back(y);
        }else{
            x1.push_back(x);
            y1.push_back(y);
        }
    }
    sort(x0.begin(),x0.end());
    sort(y0.begin(),y0.end());
    sort(x1.begin(),x1.end());
    sort(y1.begin(),y1.end());
    ll num = 0,sum = 0;
    ll ans = 0;
    rep(i,0,x0.size()){
        ans+=num*x0[i]-sum;
        sum+=x0[i];
        num++;
    }
    num = 0;
    sum = 0;
    rep(i,0,y0.size()){
        ans+=num*y0[i]-sum;
        sum+=y0[i];
        num++;
    }
    num = 0;
    sum = 0;
    rep(i,0,x1.size()){
        ans+=num*x1[i]-sum;
        sum+=x1[i];
        num++;
    }
    num = 0;
    sum = 0;
    rep(i,0,y1.size()){
        ans+=num*y1[i]-sum;
        sum+=y1[i];
        num++;
    }
    cout<<ans/2<<endl;

    return 0;
}