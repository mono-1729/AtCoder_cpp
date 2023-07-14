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
	int n,m;
	cin>>n>>m;
	vector<string>s(n,"");
	rep(i,0,n)cin>>s[i];
	vector<int>dist(n,1000000000);
	vector<int>dist2(n,1000000000);
	dist[0]=0;
	dist2[n-1]=0;
	rep(i,0,n){
		rep(j,0,m){
			if (s[i][j]=='1'){
				chmin(dist[i+m+1],dist[i]+1);
			}
		}
	}
	rrep(i,n-1,0){
		rep(j,0,m){
			if (s[i][j]=='1'){
				chmin(dist2[i],dist2[i+m+1]+1);
			}
		}
	}
	rep(i,1,n-1){
		int ans=1000000000;
		rep(j,max(0,i-m),i) {
			rep(k,i-j,m){
                //cout<<i<<" "<<j<<" "<<k<<endl;
				if (s[j][k]=='1')chmin(ans,dist[j]+dist2[j+k+1]+1);
			}
		}
		if (ans==1000000000)cout<<-1<<endl;
		else cout<<ans<<endl;
	}
	return 0;
}