#include <bits/stdc++.h>
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
ll powMod(ll x, ll n) {
	if (n == 0) return 1 % MOD;
	ll val = powMod(x, n / 2);
	val *= val;
	if (n % 2 == 1) val *= x;
	return val % MOD;
}

int main()
{
	int n,m;
	cin>>n>>m;
	vector<vector<int>> dp(m+1,vector<int>(pow(2,n),pow(10,9)));
	dp[0][0]=0;
	rep(i,0,m){
		int a,b;
		cin>>a>>b;
		int c=0;
		rep(j,0,b){
			int tmp;
			cin>>tmp;
			c+=1<<(tmp-1);
		}
		rep(j,0,pow(2,n)){
			chmin(dp[i+1][j],dp[i][j]);
			chmin(dp[i+1][j|c],dp[i][j]+a);
		}
	}
	if(dp[m][pow(2,n)-1]==pow(10,9))cout<<-1<<endl;
	else cout<<dp[m][pow(2,n)-1]<<endl;
	return 0;
}