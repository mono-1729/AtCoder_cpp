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
    vector<ll> a(n),cnt(n,-1),ord(n,-1);
    rep(i,0,n){
        cin>>a[i];
        a[i]--;
    }
    auto dfs = [&](auto dfs, ll v, ll num)->pll{
        ord[v] = num;
        ll next = a[v];
        if(cnt[next]!=-1){
            cnt[v] = cnt[next]+1;
            ord[v] = -1;
            return {cnt[v],-1};
        }else if(ord[next] != -1){
            cnt[v] = ord[v]-ord[next]+1;
            ord[v] = -1;
            return {cnt[v],ord[next]};
        }
        pll res = dfs(dfs,next,num+1);
        if(res.second==-1){
            cnt[v] = res.first+1;
            ord[v] = -1;
            return {cnt[v],-1};
        }else{
            cnt[v] = res.first;
            if(res.second == ord[v]) res.second = -1;
            ord[v] = -1;
            return res;
        }
    };
    rep(i,0,n){
        if(cnt[i]==-1) dfs(dfs,i,0);
    }
    ll ans = 0;
    rep(i,0,n) ans += cnt[i];
    cout<<ans<<endl;
    return 0;
}