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
bool is_ok(ll mid,vector<int>& a,vector<int>& f,ll k,ll n){
	ll sum=0;
	rep(i,0,n){
		if (mid==0) sum+=a[i];
		else {
			if ( 1LL*a[i]*f[i]>mid) sum+=a[i]-mid/f[i];
		}
	}
	//cout<<mid<<"  "<<sum<<endl;
	return sum<=k;
}
ll binary_search(ll ng, ll ok,vector<int>& a,vector<int>& f, ll k,ll n){
    while (abs(ok - ng) > 1){
        ll mid = (ok + ng) / 2 ;
        if (is_ok(mid,a,f,k,n)) ok = mid;
        else ng = mid;
	}
    return ok;
}
int main()
{
	ll n,k;
	cin>>n>>k;
	vector<int>a(n,0);
	vector<int>f(n,0);
	rep(i,0,n)cin>>a[i];
	rep(i,0,n)cin>>f[i];
	sort(a.begin(),a.end());
	sort(f.rbegin(),f.rend());
	ll num=0;
	rep(i,0,n)chmax(num,1LL*a[i]*f[i]);
	cout<<binary_search(-1,num,a,f,k,n)<< endl;
	return 0;
}