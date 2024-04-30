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
    ll n,m;cin>>n>>m;
    string s,t;cin>>s>>t;
    ll ans = 0;
    {
        ll n1=0,n2=0;
        rep(i,0,n+m-1){
            if(s[i] == s[i+1])n1++;
            if(t[i] == t[i+1])n2++;
        }
        ans=max(n1,n2);
    }
    auto solve = [&]()->void{
        vector<ll> s1,t1,s0,t0;
        rep(i,0,n+m){
            if(s[i] == '1')s1.push_back(i);
            else s0.push_back(i);
            if(t[i] == '1')t1.push_back(i);
            else t0.push_back(i);
        }
        if(s1.size()==0 ||s1.size()==n+m)return;
        ll num = n+m-1;
        ll now = -10;
        if(s1[0] == 0 && t1[0] == 0)num++;
        rep(i,0,s1.size()){
            ll x = clamp(now+1,min(s1[i],t1[i]),max(s1[i],t1[i]));
            if(x!=now+1){
                num-=2;
                now = max(s1[i],t1[i]);
            }
            else now = x;
        }
        if(now==n+m-1) num++;
        chmax(ans,num);

        num = n+m-1;
        now = -10;
        if(s0[0] == 0 && t0[0] == 0)num++;
        rep(i,0,s0.size()){
            ll x = clamp(now+1,min(s0[i],t0[i]),max(s0[i],t0[i]));
            if(x!=now+1){
                num-=2;
                now = max(s0[i],t0[i]);
            }
            else now = x;
        }
        if(now==n+m-1) num++;
        chmax(ans,num);
    };
    solve();
    cout<<ans<<endl;
    return 0;
}