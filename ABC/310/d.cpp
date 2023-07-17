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
int n,t,m;
vector<ll>ab(10,0);
int ans=0;
vector<ll>team(11,0);

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
int solve(int num){
	if (num==n){
		if (team[t-1]!=0 && team[t]==0) ans++;
		return 0;
	}
	int index=0;
	bool flg=true;
	while (index<t && flg){
		if (team[index]==0) flg=false;
		if ((team[index] & ab[num])==0){
			team[index]+=1LL<<num;
			solve(num+1);
			team[index]-=1LL<<num;
		}
		index++;
	}
	return 0;
}

int main() {
	cin>>n>>t>>m;
	rep(i,0,m) {
		int a,b;
		cin>>a>>b;
		a--;b--;
		ab[a]+=1LL<<b;
		ab[b]+=1LL<<a;
	}
	solve(0);
	cout<<ans<<endl;
	return 0;
}