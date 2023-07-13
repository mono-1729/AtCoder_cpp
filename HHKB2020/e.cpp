#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, n) for(int i = a; i < n; i++)
#define rrep(i, a, n) for(int i = a; i >= n; i--)
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
constexpr ll MOD = 1000000007;
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
	int h,w;
	cin>>h;cin>>w;
	char s[h][w];
	ll num[h][w]={};
	ll count=0;
	ll ans=0;
	rep(i,0,h){
		rep(j,0,w){
			cin>>s[i][j];
			if(s[i][j]=='.'){
				count++;
			}
		}
	}
	rep(i,0,h){
		int start=-1;
		rep(j,0,w){
			if(s[i][j]=='.'){
				if (start==-1){
					start=j;
				}
			}else{
				if (start!=-1){
					rep(k,start,j)num[i][k]+=j-start;
					start=-1;
				}
			}
		}
		if(start!=-1)rep(k,start,w)num[i][k]+=w-start;
	}
	rep(j,0,w){
		int start=-1;
		rep(i,0,h){
			if(s[i][j]=='.'){
				if (start==-1){
					start=i;
				}
			}else{
				if (start!=-1){
					rep(k,start,i)num[k][j]+=i-start;
					start=-1;
				}
			}
		}
		if(start!=-1)rep(k,start,h)num[k][j]+=h-start;
	}
	rep(i,0,h){
		rep(j,0,w){
			if (num[i][j]>0){
				ans+=(powMod(2,num[i][j]-1)-1)*powMod(2,count-num[i][j]+1);
				ans%=MOD;
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}