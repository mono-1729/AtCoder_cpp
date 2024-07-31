#include <bits/stdc++.h>
#include <unordered_map>
#include <stdlib.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <atcoder/all>
using namespace atcoder;
using namespace boost::multiprecision;
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(int i = a; i >= n; i--)
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
//constexpr ll MOD = 1000000007;
constexpr ll MOD = 998244353;
constexpr int IINF = 1001001001;
constexpr ll INF = 1LL<<60;
template<class t,class u> void chmax(t&a,u b){if(a<b)a=b;}
template<class t,class u> void chmin(t&a,u b){if(b<a)a=b;}

using mint = modint998244353;

ll gcd(ll a, ll b){
    if(a%b == 0){
      return b;
    }else{
      return gcd(b, a%b);
    }
}

ll lcm(ll a, ll b){
    return a*b / gcd(a, b);
}

ll powMod(ll x, ll n) {
    if (n == 0) return 1 % MOD;
    ll val = powMod(x, n / 2);
    val *= val;
    val %= MOD;
    if (n % 2 == 1) val *= x;
    return val % MOD;
}

struct Edge
{
	ll from;
	ll to;
	ll cost;
};

// ベルマンフォード法 (基本実装)
// 負閉路が存在する場合 true を返す
// distances は頂点数と同じサイズ, 全要素 INF で初期化しておく
bool BellmanFord(vector<Edge> &edges, vector<ll> &dist, int start){
    fill(dist.begin(), dist.end(), INF);
	dist[start] = 0;
    // 負の閉路がなければ、(頂点数-1)回の更新で最短路が決まる
	rep(i, 0, (int)dist.size()){
		bool changed = false;
		// 各辺について
		for (const auto& edge : edges){
			// to までの新しい距離
			const ll d = (dist[edge.from] + edge.cost);
			// d が現在の記録より小さければ更新
			if (d < dist[edge.to] && dist[edge.from] != INF){
				dist[edge.to] = d;
				changed = true;
			}
		}
		// どの頂点も更新されなかったら終了
		if (!changed){
			return false;
		}
	}
	// 負閉路が影響を与える範囲を計算
	// rep(i, 0, (int)dist.size()){
	// 	// 各辺について
	// 	for (const auto& edge : edges){
	// 		// to までの新しい距離
	// 		const ll d = (dist[edge.from] + edge.cost);
	// 		// d が現在の記録より小さければ更新
	// 		if (d < dist[edge.to]&& dist[edge.from] != INF){
	// 			dist[edge.to] = -INF;
	// 		}
	// 	}
	// }
	// 頂点回数分だけループしても更新が続くのは, 負閉路が存在するから
	return true;
}

ll cost[27][27][26];

int main() {
    int n; cin >> n;
    rep(i,0,n){
        string t; cin >> t;
        ll p; cin >> p;
        if(t.size() == 1) rep(i,0,27)rep(j,0,27) cost[i][j][t[0]-'a'] -= p;
        if(t.size() == 2) rep(i,0,27) cost[i][t[0]-'a'][t[1]-'a'] -= p;
        if(t.size() == 3) cost[t[0]-'a'][t[1]-'a'][t[2]-'a'] -= p;
    }
    vector<ll> dist(27*27);
    vector<Edge> edges(27*27*26);
    rep(i,0,27)rep(j,0,27)rep(k,0,26){
        edges.push_back({i*27+j,j*27+k,cost[i][j][k]});
    }
    if(BellmanFord(edges,dist,26*27 + 26)) cout << "Infinity" << endl;
    else{
        ll ans = INF;
        rep(i,0,27*27-1) chmin(ans,dist[i]);
        cout << -ans << endl;
    }
    
    return 0;
}