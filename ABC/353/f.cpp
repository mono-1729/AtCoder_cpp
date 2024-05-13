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

ll k;
ll calc_dist(pll s,ll snum, pll t, ll tnum){
    ll a = abs(s.first-t.first);
    ll b = abs(s.second-t.second);
    if(k==1) return snum+tnum+a+b;
    if(k==2){
        return snum+tnum+min(a,b)*2+abs(a-b)/2*3;
    }
    return snum+tnum+max(a,b)*2;
}

int main() {
    cin>>k;
    ll sx, sy, tx, ty;cin>>sx>>sy>>tx>>ty;
    vector<pair<pll, ll>> v, w;
    ll ans = abs(sx-tx)+abs(sy-ty);
    if((sx/k)%2+(sy/k)%2 ==1){
        v.push_back({{sx/k, sy/k}, 0});
    }else{
        v.push_back({{sx/k-1, sy/k}, sx%k+1});
        v.push_back({{sx/k+1, sy/k}, k-sx%k});
        v.push_back({{sx/k, sy/k-1}, sy%k+1});
        v.push_back({{sx/k, sy/k+1}, k-sy%k});
    }
    if((tx/k)%2+(ty/k)%2 ==1){
        w.push_back({{tx/k, ty/k}, 0});
    }else{
        w.push_back({{tx/k-1, ty/k}, tx%k+1});
        w.push_back({{tx/k+1, ty/k}, k-tx%k});
        w.push_back({{tx/k, ty/k-1}, ty%k+1});
        w.push_back({{tx/k, ty/k+1}, k-ty%k});
    }

    for(auto a: v)for(auto b: w){
        ll dist = calc_dist(a.first, a.second, b.first, b.second);
        chmin(ans, dist);
    }
    cout<<ans<<endl;
    return 0;
}