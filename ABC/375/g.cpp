#include <bits/stdc++.h>
#include <unordered_map>
#include <stdlib.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <atcoder/all>
using namespace atcoder;
using namespace boost::multiprecision;
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
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

class LowLink {
	typedef std::vector<std::vector<ll>> Edge;

	/**
	 * 訪問したことがある頂点かどうか.
	 */
	vector<bool> visited;
	/**
	 * 順序.
	 */
	vector<ll> order;
	/**
	 * 配列low. low[親] < low[子]なら、ブリッジとなる。
	 */
	vector<ll> low;

public:
	/**
	 * 与えられる木。隣接リスト形式でコストは含まれない.親は-1とする。
	 */
	Edge E;
	/**
	 * 関節点　その点を取り除くと全体が不連結になる点.
	 */
	vector<ll> articulation_points;
	/**
	 * 橋。pair<int, int>でfirst < secondで橋となる両端を入れる.
	 */
	vector<pair<ll, ll>> bridge;

private:

	void dfs(ll now, ll parent, ll& count) {
		visited[now] = true;
		order[now] = count;
		low[now] = order[now];
		count++;
		bool is_art = false;/* 関節点であるかどうか */
		ll son_count = 0;
		for (auto next : E[now]) {
			if (!visited[next]) {
				son_count++;
				dfs(next, now, count);
				if (next != parent)
					low[now] = min(low[now], low[next]);
				//関節点か イコールがつくのは、ひとまとまりのグループ内のlow[]は関節点のlow[]と同じ値だから。端はもうこれ以上伸びないので、関節点にカウントしない
				if (parent != -1 && order[now] <= low[next])
					is_art = true;
				//橋か
				if (order[now] < low[next])
					bridge.push_back(make_pair(min(now, next), max(now, next)));
			}
			else {
				//すでに行ったことある頂点=後退辺
				if (next != parent)
					low[now] = min(low[now], order[next]);
			}

		}
		//根は2つ以上の子があるなら、関節点
		if (parent == -1 && son_count >= 2)
			is_art = true;
		if (is_art)
			articulation_points.push_back(now);
	}

public:
	/**
	 * 渡すのは隣接リスト形式のグラフ。辺の長さは受け付けない.
	 *
	 * \param e
	 */
	LowLink(const Edge& e) {
		E = e;
		visited.assign(E.size(), 0);
		order.assign(E.size(), 0);
		low.assign(E.size(), 0);
	}
	/**
	 * 計算の際に呼び出す。各連結成分ごとにDFSしている。.
	 *
	 */
	void build() {
		ll count = 0;
		for (ll i = 0; i < E.size(); i++) {
			if (!visited[i])
				dfs(i, -1, count);
		}
	}
};

int main() {
    ll n, m; cin >> n >> m;
    vector<vector<pll>> g(n);
    vector<vector<ll>> g2(n);
    vector<ll> a(m), b(m), c(m);
    rep(i, 0, m){
        cin >> a[i] >> b[i] >> c[i];
        a[i]--; b[i]--;
        g[a[i]].push_back({b[i], c[i]});
        g[b[i]].push_back({a[i], c[i]});
    }
    vector<ll> dist0(n, INF), dist1(n, INF);
    auto dijkstra = [&](ll s, vector<ll>& dist){
        priority_queue<pll, vector<pll>, greater<pll>> pq;
        pq.push({0, s});
        dist[s] = 0;
        while(!pq.empty()){
            auto [d, now] = pq.top(); pq.pop();
            if(dist[now] < d) continue;
            for(auto [next, cost] : g[now]){
                if(dist[next] > dist[now] + cost){
                    dist[next] = dist[now] + cost;
                    pq.push({dist[next], next});
                }
            }
        }
    };
    dijkstra(0, dist0);
    dijkstra(n-1, dist1);
    unordered_map<ll, ll> mp;
    rep(i,0,m){
        if(dist0[a[i]] + dist1[b[i]] + c[i] == dist0[n-1] || dist0[b[i]] + dist1[a[i]] + c[i] == dist0[n-1]){
            g2[a[i]].push_back(b[i]);
            g2[b[i]].push_back(a[i]);
        }
    }
    LowLink lowlink(g2);
    lowlink.build();
    auto br = lowlink.bridge;
    for(auto [x, y] : br){
        mp[x*n+y] = 1;
        mp[y*n+x] = 1;
    }
    rep(i,0,m){
        if(mp[a[i]*n+b[i]] == 1) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
    return 0;
}