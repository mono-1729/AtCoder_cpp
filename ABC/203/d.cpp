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

bool is_ok(int mid, int n, vector<vector<int>>& a,int k){
	vector<vector<int>>grid(n+1,vector<int>(n+1.0));
	rep(i,0,n+1){
		rep(j,0,n+1){
			if(a[i][j]>mid) grid[i][j]=1;
		}
	}
	rep(i,0,n+1){
		rep(j,0,n) grid[i][j+1]+=grid[i][j];
	}
	rep(j,0,n+1){
		rep(i,0,n) grid[i+1][j]+=grid[i][j];
	}
	rep(i,k,n+1){
		rep(j,k,n+1){
			if (grid[i][j]-grid[i-k][j]-grid[i][j-k]+grid[i-k][j-k]<=(k*k)/2) return true;
		}
	}
	return false;
}
int binary_search(int left, int right, int n, vector<vector<int>>& a,int k){
	while (abs(right - left) > 1){
		int mid = (right + left) / 2 ;
		if (is_ok(mid, n, a,k)) right = mid;
		else left = mid;
	}
	return right;
}

int main(){
	int n,k;cin>>n>>k;
	vector<vector<int>>a(n+1,vector<int>(n+1,0)); 
	rep(i,0,n){
		rep(j,0,n) cin>>a[i+1][j+1];
	}
	cout<<binary_search(-1,1000000000,n,a,k)<<endl;
	return 0;
}