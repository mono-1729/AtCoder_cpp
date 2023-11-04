#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, n) for(int i = a; i < n; i++)
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
constexpr ll mod = 1000000007;
constexpr ll MOD = 998244353;
constexpr int IINF = 1001001001;
constexpr ll INF = 1LL<<60;
template<class t,class u> void chmax(t&a,u b){if(a<b)a=b;}
template<class t,class u> void chmin(t&a,u b){if(b<a)a=b;}
int main() {
	ll n,m;cin>>n>>m;
	vector<vector<ll>> d(n,vector<ll>(n,INF));
	rep(i,0,m){
		ll a,b,c;cin>>a>>b>>c;
		chmin(d[a][b],c);
		chmin(d[b][a],c);
	}
	rep(k,0,n)rep(i,0,n)rep(j,0,n){
		d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
	}
	return 0;
}