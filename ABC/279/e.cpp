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
	vector<int> a(m,0);
	rep(i,0,m)cin>>a[i];
	vector<int>bdict(n,0);
	vector<int>bpre(n,0);
	vector<int>baft(n,0);
	rep(i,0,n){
		bdict[i]=i;
		bpre[i]=i;
		baft[i]=i;
	}
	rep(i,0,m){
		int tmp=baft[a[i]-1];
		baft[a[i]-1]=baft[a[i]];
		baft[a[i]]=tmp;
	}
	rep(i,0,n){
		bdict[baft[i]]=i+1;
	}
	rep(i,0,m){
		int x,y;
		x=bpre[a[i]-1];y=bpre[a[i]];
		if(x==0) cout<<bdict[y]<<endl;
		else if (y==0) cout<<bdict[x]<<endl;
		else cout<<bdict[0]<<endl;
		int tmp=bpre[a[i]-1];
		bpre[a[i]-1]=bpre[a[i]];
		bpre[a[i]]=tmp;
	}
	return 0;
}