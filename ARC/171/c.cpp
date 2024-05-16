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
    vector<vector<ll>> g(n);
    rep(i,0,n-1){
        ll a,b;cin>>a>>b;
        a--;b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<vector<mint>> dp(n,{1});
    auto merge = [&](ll v, ll w) -> void {
		ll n = dp[v].size();
		ll m = dp[w].size();
		vector<mint> ret(n+1);
		for (int i=0; i<n; i++){
			for (int j=0; j<m; j++){
				// use
				ret[i+1] += dp[v][i] * (i+1) * dp[w][j] * (j+1);
				// no use
				ret[i] += dp[v][i] * dp[w][j];
			}
		}
		dp[v] = ret;
	};

    auto dfs = [&](auto dfs, ll v, ll p)->void{
        for(auto nv:g[v]){
            if(nv==p) continue;
            dfs(dfs,nv,v);
            merge(v,nv);
        }
    };
    dfs(dfs,0,-1);
    mint ans = 0;
    for(auto x:dp[0]) ans+=x;
    cout<<ans.val()<<endl;
    return 0;
}