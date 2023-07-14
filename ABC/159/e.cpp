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
ll powMod(ll x, ll n) {
	if (n == 0) return 1 % MOD;
	ll val = powMod(x, n / 2);
	val *= val;
	if (n % 2 == 1) val *= x;
	return val % MOD;
}

int main()
{
	int h,w,k;
	cin>>h>>w>>k;
	vector<string>s(h,"");
	int ans=100000;
	rep(i,0,h) cin>>s[i];
	rep(bit,0,pow(2,h-1)){
		int num[10]={0};
		int sum=0;
		rep(i,0,h-1) if (bit & (1<<i)) sum++;
		bool flg=false;
		rep(j,0,w){
			int num2[10]={0};
			int index=0;
			rep(i,0,h){
				if (s[i][j]=='1') num2[index]++;
				if (num2[index]>k) flg=true;
				if (bit & (1<<i)) index++;
			}
			if (flg) break;
			rep(i,0,10){
				num[i]+=num2[i];
				if (num[i]>k) {
					rep(x,0,10) num[x]=num2[x];
					rep(x,0,10) num2[x]=0;
					sum++;
					break;
				}
			}
		}
		//cout<<flg<<" "<<bit<<" "<<sum<<endl;
		if(!flg) chmin(ans,sum);
	}
	cout<<ans<<endl;
	return 0;
}