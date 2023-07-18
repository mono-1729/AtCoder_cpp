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
constexpr ll INF = 1LL<<40;
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
	int n;cin>>n;
	ll left=-INF,right=INF;
	ll add=0;
	rep(i,0,n){
		int a,t;cin>>a>>t;
		if (t==1){
			left += a;
            right += a;
            add += a;
		}
		if (t==2){
			chmax(left,a);
			chmax(right,a);
		}
		if (t==3){
			chmin(left,a);
			chmin(right,a);
		}
	}
	int q;cin>>q;
	rep(i,0,q){
		int x;cin>>x;
		cout<<clamp(x + add, left, right) <<endl;
	}
	return 0;
}