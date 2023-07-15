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


int main()
{
	int n,m;
	cin>>n>>m;
	int num=n;
	vector<pii>ac(m);
	ll ans=0;
	rep(i,0,m) cin>>ac[i].second>>ac[i].first;
	sort(ac.begin(),ac.end());
	rep(i,0,m){
		int g=gcd(num,ac[i].second);
		if (g!=num){
			ans+=1LL*(num-g)*ac[i].first;
			num=g;
		}
	}
	if (num==1) cout<<ans<<endl;
	else cout<<-1<<endl;
	//cout<<num<<endl;
	return 0;
}