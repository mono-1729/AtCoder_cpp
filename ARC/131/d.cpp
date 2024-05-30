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
    ll n,m,d;cin>>n>>m>>d;
    vector<ll> x(m+1),s_(m),l,r,s;
    rep(i,0,m+1)cin >> x[i];
    rep(i,0,m) cin >> s_[i];
    ll a = -(n*d/2);
    rrep(i,m-1,1){
        l.push_back(-x[i+1]);
        r.push_back(-x[i]);
        s.push_back(s_[i]);
    }
    l.push_back(-x[1]);
    r.push_back(x[1]+1);
    s.push_back(s_[0]);
    rep(i,1,m){
        l.push_back(x[i]+1);
        r.push_back(x[i+1]+1);
        s.push_back(s_[i]);
    }
    vector<ll> imos(d+1);
    rep(i,0,2*m){
        if(r[i]-a>=n*d)imos[0] +=n*s[i];
        else if(r[i]-a>=1){
            imos[0] += (r[i]-a+d)/d*s[i];
            imos[(r[i]-a)%d]-=s[i];
        }
        if(l[i]-a>=n*d)imos[0] -=n*s[i];
        else if(l[i]-a>=1){
            imos[0] -= (l[i]-a+d)/d*s[i];
            imos[(l[i]-a)%d]+=s[i];
        }
    }
    ll v = 0, ans = 0;
    rep(i,0,d){
        v+=imos[i];
        chmax(ans,v);
        // cout<<i<<" "<<v<<endl;
    }
    cout<<ans<<endl;
    return 0;
}