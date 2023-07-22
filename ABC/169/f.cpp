#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;
#define rep(i, a, n) for(int i = a; i < n; i++)
#define rrep(i, a, n) for(int i = a; i >= n; i--)
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
constexpr ll MOD = 998244353;
constexpr int IINF = 1001001001;
constexpr ll INF = 1LL<<60;
template<class t,class u> void chmax(t&a,u b){if(a<b)a=b;}
template<class t,class u> void chmin(t&a,u b){if(b<a)a=b;}

int gcd(int a, int b){
	if(a%b == 0){
	  return b;
	}else{
	  return gcd(b, a%b);
	}
}

int lcm(int a, int b){
	return a*b / gcd(a, b);
}

ll powMod(ll x, ll n) {
	if (n == 0) return 1 % MOD;
	ll val = powMod(x, n / 2);
	val *= val;
	if (n % 2 == 1) val *= x;
	return val % MOD;
}

int main() {
	int n,s;cin>>n>>s;
	vector<int>a(n);
	rep(i,0,n) cin>>a[i];
	vector<vector<ll>>dp(n+1,vector<ll>(s+1));
	ll num=powMod(2,MOD-2);
	dp[0][0]=1;
	rep(i,0,n){
		rep(j,0,s+1){
			dp[i+1][j]=(dp[i+1][j]+dp[i][j])%MOD;
			if (j+a[i]<=s) dp[i+1][j+a[i]]=(dp[i+1][j+a[i]]+num*dp[i][j])%MOD;
		}
	}
	cout<<(powMod(2,n)*dp[n][s])%MOD<<endl;
	return 0;
}