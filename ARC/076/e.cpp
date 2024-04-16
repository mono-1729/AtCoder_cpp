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
ll r,c,n;

bool f(pll x,pll y){
    if(x.first==0){
        return (y.first!=0 || y.second<x.second);
    }
    if(x.second==0){
        if((y.first!=0 && y.second!=0) || (y.second==0 && x.first<y.first))return true;
        else return false;
    }
    if(x.first==r){
        if((y.second==c && y.first!=0) || (y.first==r && x.second<y.second)) return true;
        else return false;
    }
    if(x.second==c){
        return (y.second==c && y.first!=0 && x.first>y.first);
    }  
}

int main() {
    cin>>r>>c>>n;
    vector<pll> vec;
    map<pll,ll> mp;
    rep(i,0,n){
        ll x1,y1,x2,y2;cin>>x1>>y1>>x2>>y2;
        if((x1!=0 && x1!=r && y1!=0 && y1!=c) || (x2!=0 && x2!=r && y2!=0 && y2!=c)) continue;
        if(f({x2,y2},{x1,y1})){
            swap(x1,x2);
            swap(y1,y2);
        }
        mp[{x1,y1}]=i;
        mp[{x2,y2}]=i;
        vec.push_back({x1,y1});
        vec.push_back({x2,y2});
    }
    sort(vec.begin(),vec.end(),f);
    stack<ll> st;
    for(auto p:vec){
        if(st.empty() || mp[p]!=st.top()) st.push(mp[p]);
        else st.pop();
    }
    if(st.empty())cout<<"YES"<<endl;
    else cout<<"NO"<<endl;
    return 0;
}